/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005, 2006 Christian Schoenebeck                        *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this library; if not, write to the Free Software           *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 ***************************************************************************/

#ifndef __LS_INSTRUMENTMANAGER_H__
#define __LS_INSTRUMENTMANAGER_H__

#include "../common/global.h"

#include <vector>

namespace LinuxSampler {

    // just symbol prototyping
    class EngineChannel;

    /** @brief Abstract interface class for InstrumentManagers.
     *
     * Sampler engines should provide an InstrumentManager for allowing
     * detailed information retrieval and setting of its managed instruments
     * through this general API.
     */
    class InstrumentManager {
        public:
            /**
             * Defines life-time of an instrument.
             */
            enum mode_t {
                ON_DEMAND      = 0, ///< Instrument will be loaded when needed, freed once not needed anymore.
                ON_DEMAND_HOLD = 1, ///< Instrument will be loaded when needed and kept even if not needed anymore.
                PERSISTENT     = 2  ///< Instrument will immediately be loaded and kept all the time.
            };

            /**
             * Reflects unique ID of an instrument.
             */
            struct instrument_id_t {
                String FileName; ///< File name of the instrument.
                uint   Index;    ///< Index of the instrument within the file.

                // TODO: we should extend operator<() so it will be able to detect that file x and file y are actually the same files, e.g. because one of them is a symlink / share the same inode
                bool operator<(const instrument_id_t& o) const {
                    return (Index < o.Index || (Index == o.Index && FileName < o.FileName));
                }
            };

            /**
             * Returns all managed instruments.
             *
             * This method has to be implemented by the descendant.
             */
            virtual std::vector<instrument_id_t> Instruments() = 0;

            /**
             * Returns the current life-time strategy for the given
             * instrument.
             *
             * This method has to be implemented by the descendant.
             */
            virtual mode_t GetMode(const instrument_id_t& ID) = 0;

            /**
             * Change the current life-time strategy for the given
             * instrument.
             *
             * This method has to be implemented by the descendant.
             */
            virtual void SetMode(const instrument_id_t& ID, mode_t Mode) = 0;

            /**
             * Same as SetMode(), but with the difference that this method
             * won't block.
             */
            void SetModeInBackground(const instrument_id_t& ID, mode_t Mode);

            /**
             * Same as loading the given instrument directly on the given
             * EngineChannel, but this method will not block, instead it
             * will load the instrument in a separate thread.
             *
             * @param ID - the instrument to be loaded
             * @param pEngineChannel - on which engine channel the instrument
             *                         should be loaded
             */
            static void LoadInstrumentInBackground(instrument_id_t ID, EngineChannel* pEngineChannel);

            /**
             * Returns the name of the given instrument as reflected by its
             * file.
             *
             * This method has to be implemented by the descendant.
             */
            virtual String GetInstrumentName(instrument_id_t ID) = 0;
    };

};

#endif // __LS_INSTRUMENTMANAGER_H__
