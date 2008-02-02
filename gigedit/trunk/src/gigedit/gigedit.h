/*                                                         -*- c++ -*-
 * Copyright (C) 2007, 2008 Andreas Persson
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with program; see the file COPYING. If not, write to the Free
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA.
 */

#ifndef GIGEDIT_H
#define GIGEDIT_H

#include <gig.h>

#include <list>
#include <sigc++/signal.h>

class GigEdit {
public:
    GigEdit();

    int run(int argc, char* argv[]);
    int run(gig::Instrument* pInstrument);

    sigc::signal<void, gig::File*>& signal_file_structure_to_be_changed();
    sigc::signal<void, gig::File*>& signal_file_structure_changed();
    sigc::signal<void, std::list<gig::Sample*> >& signal_samples_to_be_removed();
    sigc::signal<void>& signal_samples_removed();
    sigc::signal<void, gig::Region*>& signal_region_to_be_changed();
    sigc::signal<void, gig::Region*>& signal_region_changed();
    sigc::signal<void, gig::DimensionRegion*>& signal_dimreg_to_be_changed();
    sigc::signal<void, gig::DimensionRegion*>& signal_dimreg_changed();
    sigc::signal<void, gig::Sample*/*old*/, gig::Sample*/*new*/>& signal_sample_ref_changed();

    void on_note_on_event(int key, int velocity);
    void on_note_off_event(int key, int velocity);

private:
    sigc::signal<void, gig::File*> file_structure_to_be_changed_signal;
    sigc::signal<void, gig::File*> file_structure_changed_signal;
    sigc::signal<void, std::list<gig::Sample*> > samples_to_be_removed_signal;
    sigc::signal<void> samples_removed_signal;
    sigc::signal<void, gig::Region*> region_to_be_changed_signal;
    sigc::signal<void, gig::Region*> region_changed_signal;
    sigc::signal<void, gig::DimensionRegion*> dimreg_to_be_changed_signal;
    sigc::signal<void, gig::DimensionRegion*> dimreg_changed_signal;
    sigc::signal<void, gig::Sample*/*old*/, gig::Sample*/*new*/> sample_ref_changed_signal;
    void* state;
};

#endif // GIGEDIT_H
