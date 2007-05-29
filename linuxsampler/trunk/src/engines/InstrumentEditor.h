/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2007 Christian Schoenebeck                              *
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
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 ***************************************************************************/

#ifndef LS_INSTRUMENT_EDITOR_H
#define LS_INSTRUMENT_EDITOR_H

#include "../common/global.h"
#include "../common/Thread.h"

#include <set>

namespace LinuxSampler {

    // just symbol prototyping
    class InstrumentEditorListener;

    /** @brief Instrument Editor Interface (external plugin)
     *
     * LinuxSampler allows to spawn arbitrary instrument editor applications
     * within the sampler's own process. That way instrument editors are
     * able to modify already loaded instruments live or on-the-fly, that is
     * without having to load it again neither on sampler nor on editor side,
     * which is essential for editing large instruments.
     *
     * Instrument editors have to implement this abstract base class, embedded
     * into a DLL and placed into the respective sampler's library path. The
     * sampler will load these external DLLs as plugins on startup. Whenever
     * there's a request for editing an instrument, the sampler will try to
     * launch a matching registered editor, by calling the respective
     * plugin's Main() method.
     */
    class InstrumentEditor : protected Thread {
    public:

        /////////////////////////////////////////////////////////////////
        // abstract methods
        //     (these have to be implemented by the descendant)

        /**
         * Entry point for the instrument editor's thread. As the
         * instrument data structure is passed as typeless (void*)
         * pointer, this is not type safe! The implementing instrument
         * editor has to interpret the @a sTypeName and @a sTypeVersion
         * arguments to determine if it's able to cast the instrument
         * pointer to a known type and actually be able to work with it.
         *
         * @param pInstrument - pointer to the respective instrument object
         * @param sTypeName - format of the instrument data structure
         *                    (i.e. "libgig")
         * @param sTypeVersion - version of the instrument data structure
         *                       (i.e. "3.0.1").
         */
        virtual int Main(void* pInstrument, String sTypeName, String sTypeVersion) = 0;

        /**
         * The instrument editor has to return @c true in case it supports
         * the given instrument data structure type and version, it has to
         * return @c false otherwise. This method will be called by the
         * sampler to determine which editor is capable to work with a
         * certain instrument.
         *
         * @param sTypeName - i.e. "libgig"
         * @param STypeVersion - i.e. "3.0.1"
         */
        virtual bool IsTypeSupported(String sTypeName, String sTypeVersion) = 0;

        /**
         * The instrument editor's name (i.e. "gigedit").
         */
        virtual String Name() = 0;

        /**
         * The instrument editor's version (i.e. "0.0.1").
         */
        virtual String Version() = 0;

        /**
         * Arbitrary textual description of the instrument editor
         * (i.e. "Gigasampler and DLS format editor, GTK based").
         */
        virtual String Description() = 0;



        /////////////////////////////////////////////////////////////////
        // normal methods
        //     (usually not to be overriden by descendant)

        /**
         * Launch the instrument editor for the given instrument. The
         * editor will be spawned in its own thread and this method will
         * return as soon as the editor's thread actually started.
         */
        void Launch(void* pInstrument, String sTypeName, String sTypeVersion);

        /**
         * Registers object that wants to be notified on events.
         */
        void AddListener(InstrumentEditorListener* pListener);

        /**
         * Unregisters object that doesn't want to be notified anymore.
         */
        void RemoveListener(InstrumentEditorListener* pListener);

        /**
         * Constructor
         */
        InstrumentEditor();

    protected:
        std::set<InstrumentEditorListener*> listeners;

        // derived abstract method from base class 'Thread'
        virtual int Main();
    private:
        void*    pInstrument;
        String   sTypeName;
        String   sTypeVersion;
    };

    /** @brief Instrument Editor Notifications
     *
     * This abstract interface class has to be implemented by classes that
     * want to be notified on certain events of an instrument editor.
     */
    class InstrumentEditorListener {
    public:
        /// Called after the instrument editor stopped running.
        virtual void OnInstrumentEditorQuit(InstrumentEditor* pSender) = 0;
    };

} // namespace LinuxSampler

#endif // LS_INSTRUMENT_EDITOR_H
