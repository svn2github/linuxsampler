/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2010 Andreas Persson                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,                *
 *   MA  02110-1301  USA                                                   *
 ***************************************************************************/

#include "LookupTable.h"
#include <cstdio>
#include <set>
#include "../../common/global_private.h"

namespace sfz {

    struct LookupTable::DimDef {
        const int Definition::* lo;
        const int Definition::* hi;
        const uint8_t Query::* qarg;
        int min;
        int max;
        const char* str;
    };

    // List of all dimensions handled by the lookup table, except
    // control change. Only uint8_t types are currently supported.
    const LookupTable::DimDef LookupTable::dimDefs[] = {
        { &Region::lochan, &Region::hichan,
          &Query::chan, 1, 16, "chan" },
        { &Region::lokey, &Region::hikey,
          &Query::key, 0, 127, "key" },
        { &Region::lovel, &Region::hivel,
          &Query::vel, 0, 127, "vel" },
        { &Region::lochanaft, &Region::hichanaft,
          &Query::chanaft, 0, 127, "chanaft" },
        { &Region::lopolyaft, &Region::hipolyaft,
          &Query::polyaft, 0, 127, "polyaft" },
        { &Region::loprog, &Region::hiprog,
          &Query::prog, 0, 127, "prog" },
        { &Region::sw_previous, &Region::sw_previous,
          &Query::prev_sw_key, -1, -1, "sw_previous" },
        { 0, 0, 0, 0 }
    };

    // fills a mapping array for a given dimension
    int LookupTable::fillMapArr(const std::vector<Region*>& regions,
                                const int Definition::* lo,
                                const int Definition::* hi,
                                int min, int max, int* a) {
        std::set<int> s;
        s.insert(min);
        s.insert(max + 1);
        for (std::vector<Region*>::const_iterator i = regions.begin() ;
             i != regions.end() ; ++i) {
            s.insert((*i)->*lo);
            s.insert((*i)->*hi + 1);
        }

        int j = min;
        int l = -1;
        for (std::set<int>::const_iterator i = s.begin() ;
             i != s.end() ; ++i) {
            dmsg(2,(" %d", *i));
            for ( ; j < *i ; j++) {
                a[j] = l;
            }
            l++;
        }
        dmsg(2,("\n"));
        return l;
    }

    // fills a mapping array for a given control change number
    int LookupTable::fillMapArr(const std::vector<Region*>& regions,
                                int cc, int* a) {
        std::set<int> s;
        s.insert(0);
        s.insert(128);
        for (std::vector<Region*>::const_iterator i = regions.begin() ;
             i != regions.end() ; ++i) {
            s.insert((*i)->locc[cc]);
            s.insert((*i)->hicc[cc] + 1);
        }

        int j = 0;
        int l = -1;
        for (std::set<int>::const_iterator i = s.begin() ;
             i != s.end() ; ++i) {
            dmsg(2,(" %d", *i));
            for ( ; j < *i ; j++) {
                a[j] = l;
            }
            l++;
        }
        dmsg(2,("\n"));
        return l;
    }

    LinuxSampler::ArrayList<Region*>&
    LookupTable::query(const Query& q) const {
        int offset = 0;
        int dim;
        for (dim = 0 ; qargs[dim] ; dim++) {
            offset += mapArr[dim][q.*qargs[dim]];
        }
        for (int cc = 0 ; ccargs[cc] >= 0 ; cc++, dim++) {
            offset += mapArr[dim][q.cc[ccargs[cc]]];
        }
        return regionArr[offset];
    }

    // recursively fills the region array with regions
    void LookupTable::fillRegionArr(const int* len, Region* region,
                                    std::vector<int>::size_type dim, int j) {
        if (dim == dims.size() + ccs.size()) {
            regionArr[j].add(region);
        } else if (dim < dims.size()) {
            int d = dims[dim];
            int hi = region->*dimDefs[d].hi;
            // special case for sw_previous
            if (hi == -1) hi = 127;
            for (int l = mapArr[dim][region->*dimDefs[d].lo] ;
                 l <= mapArr[dim][hi] ; l++) {
                fillRegionArr(len, region, dim + 1, j * len[dim] + l);
            }
        } else {
            int cc = ccs[dim - dims.size()];
            for (int l = mapArr[dim][region->locc[cc]] ;
                 l <= mapArr[dim][region->hicc[cc]] ; l++) {
                fillRegionArr(len, region, dim + 1, j * len[dim] + l);
            }
        }
    }


    LookupTable::LookupTable(const Instrument* instrument) {
        const std::vector<Region*>& regions = instrument->regions;

        // find dimensions used by the instrument
        for (int dim = 0 ; dimDefs[dim].lo ; dim++) {
            for (std::vector<Region*>::const_iterator i = regions.begin() ;
                 i != regions.end() ; ++i) {
                if ((*i)->*dimDefs[dim].lo != dimDefs[dim].min ||
                    (*i)->*dimDefs[dim].hi != dimDefs[dim].max) {
                    dims.push_back(dim);
                    break;
                }
            }
        }

        dmsg(2,("\n"));

        // create and fill the qargs array with pointers to Query
        // members
        qargs = new const uint8_t Query::*[dims.size() + 1];
        for (std::vector<int>::size_type i = 0 ; i < dims.size() ; i++) {
            dmsg(2,("qargs %d: %s\n", i, dimDefs[dims[i]].str));
            qargs[i] = dimDefs[dims[i]].qarg;
        }
        qargs[dims.size()] = 0;

        // find CC dimensions used by the instrument
        for (int cc = 0 ; cc < 128 ; cc++) {
            for (std::vector<Region*>::const_iterator i = regions.begin() ;
                 i != regions.end() ; ++i) {
                if ((*i)->locc[cc] > 0 ||
                    ((*i)->hicc[cc] != 127 && (*i)->hicc[cc] != -1)) {
                    ccs.push_back(cc);
                    break;
                }
            }
        }

        // copy ccs vector to ccargs array
        ccargs = new int[ccs.size() + 1];
        for (std::vector<int>::size_type i = 0 ; i < ccs.size() ; ++i) {
            dmsg(2,("ccargs %d: %d\n", i, ccs[i]));
            ccargs[i] = ccs[i];
        }
        ccargs[ccs.size()] = -1;

        int nbDimensions = dims.size() + ccs.size();
        int* len = new int[nbDimensions];
        mapArr = new int*[nbDimensions];

        int size = 1;
        int dim = 0;

        // create and fill the dimension mapping arrays

        for (std::vector<int>::const_iterator dimi = dims.begin() ;
             dimi != dims.end() ; ++dimi) {
            int min = dimDefs[*dimi].min;
            int max = dimDefs[*dimi].max == -1 ? 127 : dimDefs[*dimi].max;
            mapArr[dim] = new int[max - min + 1] - min;
            len[dim] = fillMapArr(regions, dimDefs[*dimi].lo, dimDefs[*dimi].hi,
                                 min, max, mapArr[dim]);
            size *= len[dim];
            dim++;
        }

        for (std::vector<int>::const_iterator cci = ccs.begin() ;
             cci != ccs.end() ; ++cci) {
            mapArr[dim] = new int[128];
            len[dim] = fillMapArr(regions, *cci, mapArr[dim]);
            size *= len[dim];
            dim++;
        }


        dmsg(2,("-------------------------------\n"));
        dmsg(2,("nbDimensions=%d size=%d\n", nbDimensions, size));

        // create and fill the region array
        regionArr = new LinuxSampler::ArrayList<Region*>[size];

        for (std::vector<Region*>::const_iterator i = regions.begin() ;
             i != regions.end() ; ++i) {
            fillRegionArr(len, *i, 0, 0);
        }

        // multiply the offsets in the mapping arrays so simple
        // addition can be used in the query method
        if (nbDimensions) {
            int c = len[nbDimensions - 1];
            for (dim = nbDimensions - 2 ; dim >= 0 ; dim--) {
                for (int i = 0 ; i < 128 ; i++) mapArr[dim][i] *= c;
                c *= len[dim];
            }
        }

#if CONFIG_DEBUG_LEVEL >= 2
        // print the dimension mapping arrays

        dmsg(2,("-------------------------------\n"));
        dim = 0;
        for (std::vector<int>::const_iterator dimi = dims.begin() ;
             dimi != dims.end() ; ++dimi) {
            dmsg(2,("%d: len=%d dim=%s\n", dim, len[dim], dimDefs[*dimi].str));

            int max = dimDefs[*dimi].max == -1 ? 127 : dimDefs[*dimi].max;
            for (int i = dimDefs[*dimi].min ; i <= max ; i++) {
                dmsg(2,(" %d", mapArr[dim][i]));
            }
            dmsg(2,("\n"));

            dim++;
        }
        for (std::vector<int>::const_iterator cci = ccs.begin() ;
             cci != ccs.end() ; ++cci) {
            dmsg(2,("%d: len=%d cc=%d\n", dim, len[dim], *cci));

            for (int i = 0 ; i < 128 ; i++) {
                dmsg(2,(" %d", mapArr[dim][i]));
            }
            dmsg(2,("\n"));

            dim++;
        }
#endif
        delete[] len;

#if CONFIG_DEBUG_LEVEL >= 3
        // print the region array

        int tot = 0;
        for (int i = 0 ; i < size ; i++) {
            dmsg(3,("%d:", i));
            for (int j = 0 ; j < regionArr[i].size() ; j++) {
                dmsg(3,(" %s", regionArr[i][j]->sample.c_str()));
                tot++;
            }
            dmsg(3,("\n"));
        }
        dmsg(3,("tot=%d\n", tot));
#endif
    }

    LookupTable::~LookupTable() {
        delete[] qargs;
        delete[] ccargs;
        delete[] regionArr;

        int dim = 0;
        for (std::vector<int>::const_iterator dimi = dims.begin() ;
             dimi != dims.end() ; ++dimi) {
            delete[] (mapArr[dim] + dimDefs[*dimi].min);
            dim++;
        }
        for (std::vector<int>::const_iterator cci = ccs.begin() ;
             cci != ccs.end() ; ++cci) {
            delete[] mapArr[dim];
            dim++;
        }
        delete[] mapArr;
    }
}
