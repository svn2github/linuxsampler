/*
    Copyright (c) 2014 Christian Schoenebeck
    
    This file is part of "gigedit" and released under the terms of the
    GNU General Public License version 2.
*/

#include "CombineInstrumentsDialog.h"

// enable this for debug messages being printed while combining the instruments
#define DEBUG_COMBINE_INSTRUMENTS 0

#include "global.h"
#include "compat.h"

#include <set>
#include <iostream>
#include <assert.h>
#include <stdarg.h>
#include <string.h>

#include <glibmm/ustring.h>
#include <gtkmm/stock.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/label.h>

Glib::ustring gig_to_utf8(const gig::String& gig_string);
Glib::ustring dimTypeAsString(gig::dimension_t d);

typedef std::vector< std::pair<gig::Instrument*, gig::Region*> > OrderedRegionGroup;
typedef std::map<gig::Instrument*, gig::Region*> RegionGroup;
typedef std::map<DLS::range_t,RegionGroup> RegionGroups;

typedef std::vector<DLS::range_t> DimensionZones;
typedef std::map<gig::dimension_t,DimensionZones> Dimensions;

typedef std::map<gig::dimension_t,int> DimensionCase;

typedef std::map<gig::dimension_t, int> DimensionRegionUpperLimits;

typedef std::set<Glib::ustring> Warnings;

///////////////////////////////////////////////////////////////////////////
// private static data

static Warnings g_warnings;

///////////////////////////////////////////////////////////////////////////
// private functions

#if DEBUG_COMBINE_INSTRUMENTS
static void printRanges(const RegionGroups& regions) {
    std::cout << "{ ";
    for (RegionGroups::const_iterator it = regions.begin(); it != regions.end(); ++it) {
        if (it != regions.begin()) std::cout << ", ";
        std::cout << (int)it->first.low << ".." << (int)it->first.high;
    }
    std::cout << " }" << std::flush;
}
#endif

/**
 * Store a warning message that shall be stored and displayed to the user as a
 * list of warnings after the overall operation has finished. Duplicate warning
 * messages are automatically eliminated.
 */
inline void addWarning(const char* fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    const int SZ = 255 + strlen(fmt);
    char* buf = new char[SZ];
    vsnprintf(buf, SZ, fmt, arg);
    Glib::ustring s = buf;
    delete [] buf;
    va_end(arg);
    std::cerr << _("WARNING:") << " " << s << std::endl << std::flush;
    g_warnings.insert(s);
}

/**
 * If the two ranges overlap, then this function returns the smallest point
 * within that overlapping zone. If the two ranges do not overlap, then this
 * function will return -1 instead.
 */
inline int smallestOverlapPoint(const DLS::range_t& r1, const DLS::range_t& r2) {
    if (r1.overlaps(r2.low)) return r2.low;
    if (r2.overlaps(r1.low)) return r1.low;
    return -1;
}

/**
 * Get the most smallest region point (not necessarily its region start point)
 * of all regions of the given instruments, start searching at keyboard
 * position @a iStart.
 *
 * @returns very first region point >= iStart, or -1 if no region could be
 *          found with a range member point >= iStart
 */
static int findLowestRegionPoint(std::vector<gig::Instrument*>& instruments, int iStart) {
    DLS::range_t searchRange = { iStart, 127 };
    int result = -1;
    for (uint i = 0; i < instruments.size(); ++i) {
        gig::Instrument* instr = instruments[i];
        for (gig::Region* rgn = instr->GetFirstRegion(); rgn; rgn = instr->GetNextRegion()) {
            if (rgn->KeyRange.overlaps(searchRange)) {
                int lowest = smallestOverlapPoint(rgn->KeyRange, searchRange);
                if (result == -1 || lowest < result) result = lowest;
            }
        }
    }
    return result;
}

/**
 * Get the most smallest region end of all regions of the given instruments,
 * start searching at keyboard position @a iStart.
 *
 * @returns very first region end >= iStart, or -1 if no region could be found
 *          with a range end >= iStart
 */
static int findFirstRegionEnd(std::vector<gig::Instrument*>& instruments, int iStart) {
    DLS::range_t searchRange = { iStart, 127 };
    int result = -1;
    for (uint i = 0; i < instruments.size(); ++i) {
        gig::Instrument* instr = instruments[i];
        for (gig::Region* rgn = instr->GetFirstRegion(); rgn; rgn = instr->GetNextRegion()) {
            if (rgn->KeyRange.overlaps(searchRange)) {
                if (result == -1 || rgn->KeyRange.high < result)
                    result = rgn->KeyRange.high;
            }
        }
    }
    return result;
}

/**
 * Returns a list of all regions of the given @a instrument where the respective
 * region's key range overlaps the given @a range.
 */
static std::vector<gig::Region*> getAllRegionsWhichOverlapRange(gig::Instrument* instrument, DLS::range_t range) {
    //std::cout << "All regions which overlap { " << (int)range.low << ".." << (int)range.high << " } : " << std::flush;
    std::vector<gig::Region*> v;
    for (gig::Region* rgn = instrument->GetFirstRegion(); rgn; rgn = instrument->GetNextRegion()) {
        if (rgn->KeyRange.overlaps(range)) {
            v.push_back(rgn);
            //std::cout << (int)rgn->KeyRange.low << ".." << (int)rgn->KeyRange.high << ", " << std::flush;
        }
    }
    //std::cout << " END." << std::endl;
    return v;
}

/**
 * Returns all regions of the given @a instruments where the respective region's
 * key range overlaps the given @a range. The regions returned are ordered (in a
 * map) by their instrument pointer.
 */
static RegionGroup getAllRegionsWhichOverlapRange(std::vector<gig::Instrument*>& instruments, DLS::range_t range) {
    RegionGroup group;
    for (uint i = 0; i < instruments.size(); ++i) {
        gig::Instrument* instr = instruments[i];
        std::vector<gig::Region*> v = getAllRegionsWhichOverlapRange(instr, range);
        if (v.empty()) continue;
        if (v.size() > 1) {
            addWarning("More than one region found!");
        }
        group[instr] = v[0];
    }
    return group;
}

/** @brief Identify required regions.
 *
 * Takes a list of @a instruments as argument (which are planned to be combined
 * as separate dimension zones of a certain dimension into one single new
 * instrument) and fulfills the following tasks:
 *
 * - 1. Identification of total amount of regions required to create a new
 *      instrument to become a combined version of the given instruments.
 * - 2. Precise key range of each of those identified required regions to be
 *      created in that new instrument.
 * - 3. Grouping the original source regions of the given original instruments
 *      to the respective target key range (new region) of the instrument to be
 *      created.
 *
 * @param instruments - list of instruments that are planned to be combined
 * @returns structured result of the tasks described above
 */
static RegionGroups groupByRegionIntersections(std::vector<gig::Instrument*>& instruments) {
    RegionGroups groups;

    // find all region intersections of all instruments
    std::vector<DLS::range_t> intersections;
    for (int iStart = 0; iStart <= 127; ) {
        iStart = findLowestRegionPoint(instruments, iStart);
        if (iStart < 0) break;
        const int iEnd = findFirstRegionEnd(instruments, iStart);
        DLS::range_t range = { iStart, iEnd };
        intersections.push_back(range);
        iStart = iEnd + 1;
    }

    // now sort all regions to those found intersections
    for (uint i = 0; i < intersections.size(); ++i) {
        const DLS::range_t& range = intersections[i];
        RegionGroup group = getAllRegionsWhichOverlapRange(instruments, range);
        if (!group.empty())
            groups[range] = group;
        else
            addWarning("Empty region group!");
    }

    return groups;
}

/** @brief Identify required dimensions.
 *
 * Takes a planned new region (@a regionGroup) as argument and identifies which
 * precise dimensions would have to be created for that new region, along with
 * the amount of dimension zones and their precise individual zone sizes.
 *
 * @param regionGroup - planned new region for a new instrument
 * @returns set of dimensions that shall be created for the given planned region
 */
static Dimensions getDimensionsForRegionGroup(RegionGroup& regionGroup) {
    std::map<gig::dimension_t, std::set<int> > dimUpperLimits;

    // collect all dimension region zones' upper limits
    for (RegionGroup::iterator it = regionGroup.begin();
         it != regionGroup.end(); ++it)
    {
        gig::Region* rgn = it->second;
        int previousBits = 0;
        for (uint d = 0; d < rgn->Dimensions; ++d) {
            const gig::dimension_def_t& def = rgn->pDimensionDefinitions[d];
            for (uint z = 0; z < def.zones; ++z) {
                int dr = z << previousBits;
                gig::DimensionRegion* dimRgn = rgn->pDimensionRegions[dr];
                // Store the individual dimension zone sizes (or actually their
                // upper limits here) for each dimension.
                // HACK: Note that the velocity dimension is specially handled
                // here. Instead of taking over custom velocity split sizes
                // here, only a bogus number (zone index number) is stored for
                // each velocity zone, that way only the maxiumum amount of
                // velocity splits of all regions is stored here, and when their
                // individual DimensionRegions are finally copied (later), the
                // individual velocity split size are copied by that.
                dimUpperLimits[def.dimension].insert(
                    (def.dimension == gig::dimension_velocity) ?
                        z : (def.split_type == gig::split_type_bit) ?
                            ((z+1) * 128/def.zones - 1) : dimRgn->DimensionUpperLimits[dr]
                );
            }
            previousBits += def.bits;
        }
    }

    // convert upper limit set to range vector
    Dimensions dims;
    for (std::map<gig::dimension_t, std::set<int> >::const_iterator it = dimUpperLimits.begin();
         it != dimUpperLimits.end(); ++it)
    {
        gig::dimension_t type = it->first;
        int iLow = 0;
        for (std::set<int>::const_iterator itNums = it->second.begin();
             itNums != it->second.end(); ++itNums)
        {
            const int iUpperLimit = *itNums;
            DLS::range_t range = { iLow, iUpperLimit };
            dims[type].push_back(range);
            iLow = iUpperLimit + 1;
        }
    }

    return dims;
}

inline int getDimensionIndex(gig::dimension_t type, gig::Region* rgn) {
    for (uint i = 0; i < rgn->Dimensions; ++i)
        if (rgn->pDimensionDefinitions[i].dimension == type)
            return i;
    return -1;
}

static void fillDimValues(uint* values/*[8]*/, DimensionCase dimCase, gig::Region* rgn, bool bShouldHaveAllDimensionsPassed) {
    #if DEBUG_COMBINE_INSTRUMENTS
    printf("dimvalues = { ");
    fflush(stdout);
    #endif
    for (DimensionCase::iterator it = dimCase.begin(); it != dimCase.end(); ++it) {
        gig::dimension_t type = it->first;
        int iDimIndex = getDimensionIndex(type, rgn);
        if (bShouldHaveAllDimensionsPassed) assert(iDimIndex >= 0);
        else if (iDimIndex < 0) continue;
        values[iDimIndex] = it->second;
        #if DEBUG_COMBINE_INSTRUMENTS
        printf("%x=%d, ", type, it->second);
        #endif
    }
    #if DEBUG_COMBINE_INSTRUMENTS
    printf("}\n");
    #endif
}

static DimensionRegionUpperLimits getDimensionRegionUpperLimits(gig::DimensionRegion* dimRgn) {
    DimensionRegionUpperLimits limits;
    gig::Region* rgn = dimRgn->GetParent();
    for (uint d = 0; d < rgn->Dimensions; ++d) {
        const gig::dimension_def_t& def = rgn->pDimensionDefinitions[d];
        limits[def.dimension] = dimRgn->DimensionUpperLimits[d];
    }
    return limits;
}

static void restoreDimensionRegionUpperLimits(gig::DimensionRegion* dimRgn, const DimensionRegionUpperLimits& limits) {
    gig::Region* rgn = dimRgn->GetParent();
    for (DimensionRegionUpperLimits::const_iterator it = limits.begin();
         it != limits.end(); ++it)
    {
        int index = getDimensionIndex(it->first, rgn);
        assert(index >= 0);
        dimRgn->DimensionUpperLimits[index] = it->second;
    }
}

/**
 * Returns the sum of all bits of all dimensions defined before the given
 * dimensions (@a type). This allows to access cases of that particular
 * dimension directly.
 *
 * @param type - dimension that shall be used
 * @param rgn - parent region of that dimension
 */
inline int baseBits(gig::dimension_t type, gig::Region* rgn) {
    int previousBits = 0;
    for (uint i = 0; i < rgn->Dimensions; ++i) {
        if (rgn->pDimensionDefinitions[i].dimension == type) break;
        previousBits += rgn->pDimensionDefinitions[i].bits;
    }
    return previousBits;
}

inline int dimensionRegionIndex(gig::DimensionRegion* dimRgn) {
    gig::Region* rgn = dimRgn->GetParent();
    int sz = sizeof(rgn->pDimensionRegions) / sizeof(gig::DimensionRegion*);
    for (int i = 0; i < sz; ++i)
        if (rgn->pDimensionRegions[i] == dimRgn)
            return i;
    return -1;
}

/** @brief Get exact zone ranges of given dimension.
 *
 * This function is useful for the velocity type dimension. In contrast to other
 * dimension types, this dimension can have different zone ranges (that is
 * different individual start and end points of its dimension zones) depending
 * on which zones of other dimensions (on that gig::Region) are currently
 * selected.
 *
 * @param type - dimension where the zone ranges should be retrieved for
 *               (usually the velocity dimension in this context)
 * @param dimRgn - reflects the exact cases (zone selections) of all other
 *                 dimensions than the given one in question
 * @returns individual ranges for each zone of the questioned dimension type,
 *          it returns an empty result on errors instead
 */
static DimensionZones preciseDimensionZonesFor(gig::dimension_t type, gig::DimensionRegion* dimRgn) {
    DimensionZones zones;
    gig::Region* rgn = dimRgn->GetParent();
    int iDimension = getDimensionIndex(type, rgn);
    if (iDimension < 0) return zones;
    const gig::dimension_def_t& def = rgn->pDimensionDefinitions[iDimension];
    int iDimRgn = dimensionRegionIndex(dimRgn);
    int iBaseBits = baseBits(type, rgn);
    int mask = ~(((1 << def.bits) - 1) << iBaseBits);

    #if DEBUG_COMBINE_INSTRUMENTS
    printf("velo zones { ");
    fflush(stdout);
    #endif
    int iLow = 0;
    for (int z = 0; z < def.zones; ++z) {
        gig::DimensionRegion* dimRgn2 =
            rgn->pDimensionRegions[ (iDimRgn & mask) | ( z << iBaseBits) ];
        int iHigh = dimRgn2->DimensionUpperLimits[iDimension];
        DLS::range_t range = { iLow, iHigh};
        #if DEBUG_COMBINE_INSTRUMENTS
        printf("%d..%d, ", iLow, iHigh);
        fflush(stdout);
        #endif
        zones.push_back(range);
        iLow = iHigh + 1;
    }
    #if DEBUG_COMBINE_INSTRUMENTS
    printf("}\n");
    #endif
    return zones;
}

struct CopyAssignSchedEntry {
    gig::DimensionRegion* src;
    gig::DimensionRegion* dst;
    int velocityZone;
    int totalSrcVelocityZones;
};
typedef std::vector<CopyAssignSchedEntry> CopyAssignSchedule;

/** @brief Schedule copying DimensionRegions from source Region to target Region.
 *
 * Schedules copying the entire articulation informations (including sample
 * reference) from all individual DimensionRegions of source Region @a inRgn to
 * target Region @a outRgn. It is expected that the required dimensions (thus
 * the required dimension regions) were already created before calling this
 * function.
 *
 * To be precise, it does the task above only for the dimension zones defined by
 * the three arguments @a mainDim, @a iSrcMainBit, @a iDstMainBit, which reflect
 * a selection which dimension zones shall be copied. All other dimension zones
 * will not be scheduled to be copied by a single call of this function. So this
 * function needs to be called several time in case all dimension regions shall
 * be copied of the entire region (@a inRgn, @a outRgn).
 *
 * @param outRgn - where the dimension regions shall be copied to
 * @param inRgn - all dimension regions that shall be copied from
 * @param dims - precise dimension definitions of target region
 * @param mainDim - this dimension type, in combination with @a iSrcMainBit and
 *                  @a iDstMainBit defines a selection which dimension region
 *                  zones shall be copied by this call of this function
 * @param iDstMainBit - destination bit of @a mainDim
 * @param iSrcMainBit - source bit of @a mainDim
 * @param schedule - list of all DimensionRegion copy operations which is filled
 *                   during the nested loops / recursions of this function call
 * @param dimCase - just for internal purpose (function recursion), don't pass
 *                  anything here, this function will call itself recursively
 *                  will fill this container with concrete dimension values for
 *                  selecting the precise dimension regions during its task
 */
static void scheduleCopyDimensionRegions(gig::Region* outRgn, gig::Region* inRgn,
                                 Dimensions dims, gig::dimension_t mainDim,
                                 int iDstMainBit, int iSrcMainBit,
                                 CopyAssignSchedule* schedule,
                                 DimensionCase dimCase = DimensionCase())
{
    if (dims.empty()) { // reached deepest level of function recursion ...
        CopyAssignSchedEntry e;

        // resolve the respective source & destination DimensionRegion ...        
        uint srcDimValues[8] = {};
        uint dstDimValues[8] = {};
        DimensionCase srcDimCase = dimCase;
        DimensionCase dstDimCase = dimCase;
        srcDimCase[mainDim] = iSrcMainBit;
        dstDimCase[mainDim] = iDstMainBit;

        #if DEBUG_COMBINE_INSTRUMENTS
        printf("-------------------------------\n");
        printf("iDstMainBit=%d iSrcMainBit=%d\n", iDstMainBit, iSrcMainBit);
        #endif

        // first select source & target dimension region with an arbitrary
        // velocity split zone, to get access to the precise individual velocity
        // split zone sizes (if there is actually a velocity dimension at all,
        // otherwise we already select the desired source & target dimension
        // region here)
        #if DEBUG_COMBINE_INSTRUMENTS
        printf("src "); fflush(stdout);
        #endif
        fillDimValues(srcDimValues, srcDimCase, inRgn, false);
        #if DEBUG_COMBINE_INSTRUMENTS
        printf("dst "); fflush(stdout);
        #endif
        fillDimValues(dstDimValues, dstDimCase, outRgn, false);
        gig::DimensionRegion* srcDimRgn = inRgn->GetDimensionRegionByValue(srcDimValues);
        gig::DimensionRegion* dstDimRgn = outRgn->GetDimensionRegionByValue(dstDimValues);
        #if DEBUG_COMBINE_INSTRUMENTS
        printf("iDstMainBit=%d iSrcMainBit=%d\n", iDstMainBit, iSrcMainBit);
        printf("srcDimRgn=%lx dstDimRgn=%lx\n", (uint64_t)srcDimRgn, (uint64_t)dstDimRgn);
        printf("srcSample='%s' dstSample='%s'\n",
               (!srcDimRgn->pSample ? "NULL" : srcDimRgn->pSample->pInfo->Name.c_str()),
               (!dstDimRgn->pSample ? "NULL" : dstDimRgn->pSample->pInfo->Name.c_str())
        );
        #endif

        assert(srcDimRgn->GetParent() == inRgn);
        assert(dstDimRgn->GetParent() == outRgn);

        // now that we have access to the precise velocity split zone upper
        // limits, we can select the actual source & destination dimension
        // regions we need to copy (assuming that source or target region has
        // a velocity dimension)
        if (outRgn->GetDimensionDefinition(gig::dimension_velocity)) {
            // re-select target dimension region (with correct velocity zone)
            DimensionZones dstZones = preciseDimensionZonesFor(gig::dimension_velocity, dstDimRgn);
            assert(dstZones.size() > 1);
            const int iDstZoneIndex =
                (mainDim == gig::dimension_velocity)
                    ? iDstMainBit : dstDimCase[gig::dimension_velocity]; // (mainDim == gig::dimension_velocity) exception case probably unnecessary here
            e.velocityZone = iDstZoneIndex;
            #if DEBUG_COMBINE_INSTRUMENTS
            printf("dst velocity zone: %d/%d\n", iDstZoneIndex, (int)dstZones.size());
            #endif
            assert(uint(iDstZoneIndex) < dstZones.size());
            dstDimCase[gig::dimension_velocity] = dstZones[iDstZoneIndex].low; // arbitrary value between low and high
            #if DEBUG_COMBINE_INSTRUMENTS
            printf("dst velocity value = %d\n", dstDimCase[gig::dimension_velocity]);
            printf("dst refilled "); fflush(stdout);
            #endif
            fillDimValues(dstDimValues, dstDimCase, outRgn, false);
            dstDimRgn = outRgn->GetDimensionRegionByValue(dstDimValues);
            #if DEBUG_COMBINE_INSTRUMENTS
            printf("reselected dstDimRgn=%lx\n", (uint64_t)dstDimRgn);
            printf("dstSample='%s'%s\n",
                (!dstDimRgn->pSample ? "NULL" : dstDimRgn->pSample->pInfo->Name.c_str()),
                (dstDimRgn->pSample ? " <--- ERROR ERROR ERROR !!!!!!!!! " : "")
            );
            #endif

            // re-select source dimension region with correct velocity zone
            // (if it has a velocity dimension that is)
            if (inRgn->GetDimensionDefinition(gig::dimension_velocity)) {
                DimensionZones srcZones = preciseDimensionZonesFor(gig::dimension_velocity, srcDimRgn);
                e.totalSrcVelocityZones = srcZones.size();
                assert(srcZones.size() > 0);
                if (srcZones.size() <= 1) {
                    addWarning("Input region has a velocity dimension with only ONE zone!");
                }
                int iSrcZoneIndex =
                    (mainDim == gig::dimension_velocity)
                        ? iSrcMainBit : iDstZoneIndex;
                if (uint(iSrcZoneIndex) >= srcZones.size())
                    iSrcZoneIndex = srcZones.size() - 1;
                srcDimCase[gig::dimension_velocity] = srcZones[iSrcZoneIndex].low; // same zone as used above for target dimension region (no matter what the precise zone ranges are)
                #if DEBUG_COMBINE_INSTRUMENTS
                printf("src refilled "); fflush(stdout);
                #endif
                fillDimValues(srcDimValues, srcDimCase, inRgn, false);
                srcDimRgn = inRgn->GetDimensionRegionByValue(srcDimValues);
                #if DEBUG_COMBINE_INSTRUMENTS
                printf("reselected srcDimRgn=%lx\n", (uint64_t)srcDimRgn);
                printf("srcSample='%s'\n",
                    (!srcDimRgn->pSample ? "NULL" : srcDimRgn->pSample->pInfo->Name.c_str())
                );
                #endif
            }
        }

        // Schedule copy operation of source -> target DimensionRegion for the
        // time after all nested loops have been traversed. We have to postpone
        // the actual copy operations this way, because otherwise it would
        // overwrite informations inside the destination DimensionRegion object
        // that we need to read in the code block above.
        e.src = srcDimRgn;
        e.dst = dstDimRgn;
        schedule->push_back(e);

        return; // returning from deepest level of function recursion
    }

    // Copying n dimensions requires n nested loops. That's why this function
    // is calling itself recursively to provide the required amount of nested
    // loops. With each call it pops from argument 'dims' and pushes to
    // argument 'dimCase'.

    Dimensions::iterator itDimension = dims.begin();
    gig::dimension_t type = itDimension->first;
    DimensionZones  zones = itDimension->second;
    dims.erase(itDimension);

    int iZone = 0;
    for (DimensionZones::iterator itZone = zones.begin();
         itZone != zones.end(); ++itZone, ++iZone)
    {
        DLS::range_t zoneRange = *itZone;
        gig::dimension_def_t* def = outRgn->GetDimensionDefinition(type);
        dimCase[type] = (def->split_type == gig::split_type_bit) ? iZone : zoneRange.low;

        // recurse until 'dims' is exhausted (and dimCase filled up with concrete value)
        scheduleCopyDimensionRegions(outRgn, inRgn, dims, mainDim, iDstMainBit, iSrcMainBit, schedule, dimCase);
    }
}

static OrderedRegionGroup sortRegionGroup(const RegionGroup& group, const std::vector<gig::Instrument*>& instruments) {
    OrderedRegionGroup result;
    for (std::vector<gig::Instrument*>::const_iterator it = instruments.begin();
         it != instruments.end(); ++it)
    {
        RegionGroup::const_iterator itRgn = group.find(*it);
        if (itRgn == group.end()) continue;
        result.push_back(
            std::pair<gig::Instrument*, gig::Region*>(
                itRgn->first, itRgn->second
            )
        );
    }
    return result;
}

/** @brief Combine given list of instruments to one instrument.
 *
 * Takes a list of @a instruments as argument and combines them to one single
 * new @a output instrument. For this task, it will create a dimension of type
 * given by @a mainDimension in the new instrument and copies the source
 * instruments to those dimension zones.
 *
 * @param instruments - (input) list of instruments that shall be combined,
 *                      they will only be read, so they will be left untouched
 * @param gig - (input/output) .gig file where the new combined instrument shall
 *              be created
 * @param output - (output) on success this pointer will be set to the new
 *                 instrument being created
 * @param mainDimension - the dimension that shall be used to combine the
 *                        instruments
 * @throw RIFF::Exception on any kinds of errors
 */
static void combineInstruments(std::vector<gig::Instrument*>& instruments, gig::File* gig, gig::Instrument*& output, gig::dimension_t mainDimension) {
    output = NULL;

    // divide the individual regions to (probably even smaller) groups of
    // regions, coping with the fact that the source regions of the instruments
    // might have quite different range sizes and start and end points
    RegionGroups groups = groupByRegionIntersections(instruments);
    #if DEBUG_COMBINE_INSTRUMENTS
    std::cout << std::endl << "New regions: " << std::flush;
    printRanges(groups);
    std::cout << std::endl;
    #endif

    if (groups.empty())
        throw gig::Exception(_("No regions found to create a new instrument with."));

    // create a new output instrument
    gig::Instrument* outInstr = gig->AddInstrument();
    outInstr->pInfo->Name = _("NEW COMBINATION");

    // Distinguishing in the following code block between 'horizontal' and
    // 'vertical' regions. The 'horizontal' ones are meant to be the key ranges
    // in the output instrument, while the 'vertical' regions are meant to be
    // the set of source regions that shall be layered to that 'horizontal'
    // region / key range. It is important to know, that the key ranges defined
    // in the 'horizontal' and 'vertical' regions might differ.

    // merge the instruments to the new output instrument
    for (RegionGroups::iterator itGroup = groups.begin();
         itGroup != groups.end(); ++itGroup) // iterate over 'horizontal' / target regions ...
    {
        gig::Region* outRgn = outInstr->AddRegion();
        outRgn->SetKeyRange(itGroup->first.low, itGroup->first.high);
        #if DEBUG_COMBINE_INSTRUMENTS
        printf("---> Start target region %d..%d\n", itGroup->first.low, itGroup->first.high);
        #endif

        // detect the total amount of zones required for the given main
        // dimension to build up this combi for current key range
        int iTotalZones = 0;
        for (RegionGroup::iterator itRgn = itGroup->second.begin();
             itRgn != itGroup->second.end(); ++itRgn)
        {
            gig::Region* inRgn = itRgn->second;
            gig::dimension_def_t* def = inRgn->GetDimensionDefinition(mainDimension);
            iTotalZones += (def) ? def->zones : 1;
        }
        #if DEBUG_COMBINE_INSTRUMENTS
        printf("Required total zones: %d, vertical regions: %d\n", iTotalZones, itGroup->second.size());
        #endif

        // create all required dimensions for this output region
        // (except the main dimension used for separating the individual
        // instruments, we create that particular dimension as next step)
        Dimensions dims = getDimensionsForRegionGroup(itGroup->second);
        // the given main dimension which is used to combine the instruments is
        // created separately after the next code block, and the main dimension
        // should not be part of dims here, because it also used for iterating
        // all dimensions zones, which would lead to this dimensions being
        // iterated twice
        dims.erase(mainDimension);
        {
            std::vector<gig::dimension_t> skipTheseDimensions; // used to prevent a misbehavior (i.e. crash) of the combine algorithm in case one of the source instruments has a dimension with only one zone, which is not standard conform

            for (Dimensions::iterator itDim = dims.begin();
                itDim != dims.end(); ++itDim)
            {
                gig::dimension_def_t def;
                def.dimension = itDim->first; // dimension type
                def.zones = itDim->second.size();
                def.bits = zoneCountToBits(def.zones);
                if (def.zones < 2) {
                    addWarning(
                        "Attempt to create dimension with type=0x%x with only "
                        "ONE zone (because at least one of the source "
                        "instruments seems to have such a velocity dimension "
                        "with only ONE zone, which is odd)! Skipping this "
                        "dimension for now.",
                        (int)itDim->first
                    );
                    skipTheseDimensions.push_back(itDim->first);
                    continue;
                }
                #if DEBUG_COMBINE_INSTRUMENTS
                std::cout << "Adding new regular dimension type=" << std::hex << (int)def.dimension << std::dec << ", zones=" << (int)def.zones << ", bits=" << (int)def.bits << " ... " << std::flush;
                #endif
                outRgn->AddDimension(&def);
                #if DEBUG_COMBINE_INSTRUMENTS
                std::cout << "OK" << std::endl << std::flush;
                #endif
            }
            // prevent the following dimensions to be processed further below
            // (since the respective dimension was not created above)
            for (int i = 0; i < skipTheseDimensions.size(); ++i)
                dims.erase(skipTheseDimensions[i]);
        }

        // create the main dimension (if necessary for current key range)
        if (iTotalZones > 1) {
            gig::dimension_def_t def;
            def.dimension = mainDimension; // dimension type
            def.zones = iTotalZones;
            def.bits = zoneCountToBits(def.zones);
            #if DEBUG_COMBINE_INSTRUMENTS
            std::cout << "Adding new main combi dimension type=" << std::hex << (int)def.dimension << std::dec << ", zones=" << (int)def.zones << ", bits=" << (int)def.bits << " ... " << std::flush;
            #endif
            outRgn->AddDimension(&def);
            #if DEBUG_COMBINE_INSTRUMENTS
            std::cout << "OK" << std::endl << std::flush;
            #endif
        } else {
            dims.erase(mainDimension);
        }

        // for the next task we need to have the current RegionGroup to be
        // sorted by instrument in the same sequence as the 'instruments' vector
        // argument passed to this function (because the std::map behind the
        // 'RegionGroup' type sorts by memory address instead, and that would
        // sometimes lead to the source instruments' region to be sorted into
        // the wrong target layer)
        OrderedRegionGroup currentGroup = sortRegionGroup(itGroup->second, instruments);

        // schedule copying the source dimension regions to the target dimension
        // regions
        CopyAssignSchedule schedule;
        int iDstMainBit = 0;
        for (OrderedRegionGroup::iterator itRgn = currentGroup.begin();
             itRgn != currentGroup.end(); ++itRgn) // iterate over 'vertical' / source regions ...
        {
            gig::Region* inRgn = itRgn->second;
            #if DEBUG_COMBINE_INSTRUMENTS
            printf("[source region of '%s']\n", inRgn->GetParent()->pInfo->Name.c_str());
            #endif

            // determine how many main dimension zones this input region requires
            gig::dimension_def_t* def = inRgn->GetDimensionDefinition(mainDimension);
            const int inRgnMainZones = (def) ? def->zones : 1;

            for (uint iSrcMainBit = 0; iSrcMainBit < inRgnMainZones; ++iSrcMainBit, ++iDstMainBit) {
                scheduleCopyDimensionRegions(
                    outRgn, inRgn, dims, mainDimension,
                    iDstMainBit, iSrcMainBit, &schedule
                );
            }
        }

        // finally copy the scheduled source -> target dimension regions
        for (uint i = 0; i < schedule.size(); ++i) {
            CopyAssignSchedEntry& e = schedule[i];

            // backup the target DimensionRegion's current dimension zones upper
            // limits (because the target DimensionRegion's upper limits are
            // already defined correctly since calling AddDimension(), and the
            // CopyAssign() call next, will overwrite those upper limits
            // unfortunately
            DimensionRegionUpperLimits dstUpperLimits = getDimensionRegionUpperLimits(e.dst);
            DimensionRegionUpperLimits srcUpperLimits = getDimensionRegionUpperLimits(e.src);

            // now actually copy over the current DimensionRegion
            const gig::Region* const origRgn = e.dst->GetParent(); // just for sanity check below
            e.dst->CopyAssign(e.src);
            assert(origRgn == e.dst->GetParent()); // if gigedit is crashing here, then you must update libgig (to at least SVN r2547, v3.3.0.svn10)

            // restore all original dimension zone upper limits except of the
            // velocity dimension, because the velocity dimension zone sizes are
            // allowed to differ for individual DimensionRegions in gig v3
            // format
            //
            // if the main dinension is the 'velocity' dimension, then skip
            // restoring the source's original velocity zone limits, because
            // dealing with merging that is not implemented yet
            // TODO: merge custom velocity splits if main dimension is the velocity dimension (for now equal sized velocity zones are used if mainDim is 'velocity')
            if (srcUpperLimits.count(gig::dimension_velocity) && mainDimension != gig::dimension_velocity) {
                if (!dstUpperLimits.count(gig::dimension_velocity)) {
                    addWarning("Source instrument seems to have a velocity dimension whereas new target instrument doesn't!");
                } else {
                    dstUpperLimits[gig::dimension_velocity] =
                        (e.velocityZone >= e.totalSrcVelocityZones)
                            ? 127 : srcUpperLimits[gig::dimension_velocity];
                }
            }
            restoreDimensionRegionUpperLimits(e.dst, dstUpperLimits);
        }
    }

    // success
    output = outInstr;
}

///////////////////////////////////////////////////////////////////////////
// class 'CombineInstrumentsDialog'

CombineInstrumentsDialog::CombineInstrumentsDialog(Gtk::Window& parent, gig::File* gig)
    : Gtk::Dialog(_("Combine Instruments"), parent, true),
      m_gig(gig), m_fileWasChanged(false), m_newCombinedInstrument(NULL),
      m_cancelButton(Gtk::Stock::CANCEL), m_OKButton(Gtk::Stock::OK),
      m_descriptionLabel(), m_tableDimCombo(2, 2), m_comboDimType(),
      m_labelDimType(Glib::ustring(_("Combine by Dimension:")) + "  ", Gtk::ALIGN_END)
{
    m_scrolledWindow.add(m_treeView);
    m_scrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    get_vbox()->pack_start(m_descriptionLabel, Gtk::PACK_SHRINK);
    get_vbox()->pack_start(m_tableDimCombo, Gtk::PACK_SHRINK);
    get_vbox()->pack_start(m_scrolledWindow);
    get_vbox()->pack_start(m_buttonBox, Gtk::PACK_SHRINK);

#if GTKMM_MAJOR_VERSION >= 3
    m_descriptionLabel.set_line_wrap();
#endif
    m_descriptionLabel.set_text(_(
        "Select at least two instruments below that shall be combined (as "
        "separate dimension zones of the selected dimension type) as a new "
        "instrument. The original instruments remain untouched.\n\n"
        "You may use this tool for example to combine solo instruments into "
        "a combi sound arrangement by selecting the 'layer' dimension, or you "
        "might combine similar sounding solo sounds into separate velocity "
        "split layers by using the 'velocity' dimension, and so on."
    ));

    // add dimension type combo box
    {
        int iLayerDimIndex = -1;
        Glib::RefPtr<Gtk::ListStore> refComboModel = Gtk::ListStore::create(m_comboDimsModel);
        for (int i = 0x01, iRow = 0; i < 0xff; i++) {
            Glib::ustring sType =
                dimTypeAsString(static_cast<gig::dimension_t>(i));
            if (sType.find("Unknown") != 0) {
                Gtk::TreeModel::Row row = *(refComboModel->append());
                row[m_comboDimsModel.m_type_id]   = i;
                row[m_comboDimsModel.m_type_name] = sType;
                if (i == gig::dimension_layer) iLayerDimIndex = iRow;
                iRow++;
            }
        }
        m_comboDimType.set_model(refComboModel);
        m_comboDimType.pack_start(m_comboDimsModel.m_type_id);
        m_comboDimType.pack_start(m_comboDimsModel.m_type_name);
        m_tableDimCombo.attach(m_labelDimType, 0, 1, 0, 1);
        m_tableDimCombo.attach(m_comboDimType, 1, 2, 0, 1);
        m_comboDimType.set_active(iLayerDimIndex); // preselect "layer" dimension
    }

    m_refTreeModel = Gtk::ListStore::create(m_columns);
    m_treeView.set_model(m_refTreeModel);
    m_treeView.set_tooltip_text(_(
        "Use SHIFT + left click or CTRL + left click to select the instruments "
        "you want to combine."
    ));
    m_treeView.append_column("Instrument", m_columns.m_col_name);
    m_treeView.set_headers_visible(false);
    m_treeView.get_selection()->set_mode(Gtk::SELECTION_MULTIPLE);
    m_treeView.get_selection()->signal_changed().connect(
        sigc::mem_fun(*this, &CombineInstrumentsDialog::onSelectionChanged)
    );
    m_treeView.show();

    for (int i = 0; true; ++i) {
        gig::Instrument* instr = gig->GetInstrument(i);
        if (!instr) break;

#if DEBUG_COMBINE_INSTRUMENTS
        {
            std::cout << "Instrument (" << i << ") '" << instr->pInfo->Name << "' Regions: " << std::flush;
            for (gig::Region* rgn = instr->GetFirstRegion(); rgn; rgn = instr->GetNextRegion()) {
                std::cout << rgn->KeyRange.low << ".." << rgn->KeyRange.high << ", " << std::flush;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
#endif
        
        Glib::ustring name(gig_to_utf8(instr->pInfo->Name));
        Gtk::TreeModel::iterator iter = m_refTreeModel->append();
        Gtk::TreeModel::Row row = *iter;
        row[m_columns.m_col_name] = name;
        row[m_columns.m_col_instr] = instr;
    }

    m_buttonBox.set_layout(Gtk::BUTTONBOX_END);
    m_buttonBox.set_border_width(5);
    m_buttonBox.pack_start(m_cancelButton, Gtk::PACK_SHRINK);
    m_buttonBox.pack_start(m_OKButton, Gtk::PACK_SHRINK);
    m_buttonBox.show();

    m_cancelButton.show();
    m_OKButton.set_sensitive(false);
    m_OKButton.show();

    m_cancelButton.signal_clicked().connect(
        sigc::mem_fun(*this, &CombineInstrumentsDialog::hide)
    );

    m_OKButton.signal_clicked().connect(
        sigc::mem_fun(*this, &CombineInstrumentsDialog::combineSelectedInstruments)
    );

    show_all_children();

    // show a warning to user if he uses a .gig in v2 format
    if (gig->pVersion->major < 3) {
        Glib::ustring txt = _(
            "You are currently using a .gig file in old v2 format. The current "
            "combine algorithm will most probably fail trying to combine "
            "instruments in this old format. So better save the file in new v3 "
            "format before trying to combine your instruments."
        );
        Gtk::MessageDialog msg(*this, txt, false, Gtk::MESSAGE_WARNING);
        msg.run();
    }
}

void CombineInstrumentsDialog::combineSelectedInstruments() {
    std::vector<gig::Instrument*> instruments;
    std::vector<Gtk::TreeModel::Path> v = m_treeView.get_selection()->get_selected_rows();
    for (uint i = 0; i < v.size(); ++i) {
        Gtk::TreeModel::iterator it = m_refTreeModel->get_iter(v[i]);
        Gtk::TreeModel::Row row = *it;
        Glib::ustring name = row[m_columns.m_col_name];
        gig::Instrument* instrument = row[m_columns.m_col_instr];
        #if DEBUG_COMBINE_INSTRUMENTS
        printf("Selection '%s' 0x%lx\n\n", name.c_str(), int64_t((void*)instrument));
        #endif
        instruments.push_back(instrument);
    }

    g_warnings.clear();

    try {
        // which main dimension was selected in the combo box?
        gig::dimension_t mainDimension;
        {
            Gtk::TreeModel::iterator iterType = m_comboDimType.get_active();
            if (!iterType) throw gig::Exception("No dimension selected");
            Gtk::TreeModel::Row rowType = *iterType;
            if (!rowType) throw gig::Exception("Something is wrong regarding dimension selection");
            int iTypeID = rowType[m_comboDimsModel.m_type_id];
            mainDimension = static_cast<gig::dimension_t>(iTypeID);
        }

        // now start the actual cobination task ...
        combineInstruments(instruments, m_gig, m_newCombinedInstrument, mainDimension);
    } catch (RIFF::Exception e) {;
        Gtk::MessageDialog msg(*this, e.Message, false, Gtk::MESSAGE_ERROR);
        msg.run();
        return;
    } catch (...) {
        Glib::ustring txt = _("An unknown exception occurred!");
        Gtk::MessageDialog msg(*this, txt, false, Gtk::MESSAGE_ERROR);
        msg.run();
        return;
    }

    if (!g_warnings.empty()) {
        Glib::ustring txt = _(
            "Combined instrument was created successfully, but there were warnings:"
        );
        txt += "\n\n";
        for (Warnings::const_iterator itWarn = g_warnings.begin();
             itWarn != g_warnings.end(); ++itWarn)
        {
            txt += "-> " + *itWarn + "\n";
        }
        txt += "\n";
        txt += _(
            "You might also want to check the console for further warnings and "
            "error messages."
        );
        Gtk::MessageDialog msg(*this, txt, false, Gtk::MESSAGE_WARNING);
        msg.run();
    }

    // no error occurred
    m_fileWasChanged = true;
    hide();
}

void CombineInstrumentsDialog::onSelectionChanged() {
    std::vector<Gtk::TreeModel::Path> v = m_treeView.get_selection()->get_selected_rows();
    m_OKButton.set_sensitive(v.size() >= 2);
}

bool CombineInstrumentsDialog::fileWasChanged() const {
    return m_fileWasChanged;
}

gig::Instrument* CombineInstrumentsDialog::newCombinedInstrument() const {
    return m_newCombinedInstrument;
}
