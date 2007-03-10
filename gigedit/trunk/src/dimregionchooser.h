/*                                                         -*- c++ -*-
 * Copyright (C) 2006, 2007 Andreas Persson
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

#ifndef GIGEDIT_DIMREGIONCHOOSER_H
#define GIGEDIT_DIMREGIONCHOOSER_H

#include <gtkmm/drawingarea.h>
#include <gdkmm/colormap.h>
#include <gdkmm/window.h>

#include <gig.h>

class DimRegionChooser : public Gtk::DrawingArea
{
public:
    DimRegionChooser();
    virtual ~DimRegionChooser();

    void set_fromto(int from, int to);

    void set_instrument(gig::Instrument* instrument);
    void set_region(gig::Region* region);
//    void set_dimregno(int x);

    sigc::signal<void> signal_sel_changed();

    gig::DimensionRegion* get_dimregion() { return dimreg; }

protected:
    virtual void on_realize();
    virtual bool on_expose_event(GdkEventExpose* e);
    virtual void on_size_request(GtkRequisition* requisition);
    virtual bool on_button_press_event(GdkEventButton* event);
//    virtual bool on_key_press_event(GdkEventKey* event);
//    virtual bool on_focus_in_event(GdkEventFocus* event);
    virtual bool on_focus(Gtk::DirectionType direction);

//    virtual void on_size_allocate(Gtk::Allocation& allocation);

    Glib::RefPtr<Gdk::GC> gc;
    Gdk::Color blue, red, black, white, green;

    gig::Instrument* instrument;
    gig::Region* region;
    int dimregno;

    sigc::signal<void> sel_changed_signal;

    gig::DimensionRegion* dimreg;
    int focus_line;
    int dimvalue_from[256];
    int dimvalue_to[256];
    int label_width;
    int nbDimensions;
};

#endif
