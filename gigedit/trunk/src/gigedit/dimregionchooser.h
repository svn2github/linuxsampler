/*                                                         -*- c++ -*-
 * Copyright (C) 2006-2011 Andreas Persson
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
#include <gdkmm/window.h>

#include "compat.h"

#include <gig.h>

#include <set>

class DimRegionChooser : public Gtk::DrawingArea
{
public:
    DimRegionChooser();
    virtual ~DimRegionChooser();

    void set_region(gig::Region* region);

    sigc::signal<void>& signal_dimregion_selected();
    sigc::signal<void>& signal_region_changed();

    gig::DimensionRegion* get_dimregion() const { return dimreg; }
    void get_dimregions(const gig::Region* region, bool stereo,
                        std::set<gig::DimensionRegion*>& dimregs) const;

protected:
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
    virtual bool on_expose_event(GdkEventExpose* e);
#else
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
#endif
    virtual bool on_button_press_event(GdkEventButton* event);
    virtual bool on_button_release_event(GdkEventButton* event);
    virtual bool on_motion_notify_event(GdkEventMotion* event);
    virtual bool on_focus(Gtk::DirectionType direction);

    Gdk::RGBA red, black, white;

    gig::Instrument* instrument;
    gig::Region* region;
    int dimregno;

    sigc::signal<void> dimregion_selected;
    sigc::signal<void> region_changed;

    gig::DimensionRegion* dimreg;
    int focus_line;
    int dimvalue[256];
    int label_width;
    bool labels_changed;
    int nbDimensions;

    // information needed during a resize
    struct {
        bool active;
        enum {
            none,
            left,
            right
        } selected;
        int pos;
        int min;
        int max;
        int dimension;
        int offset;
    } resize;

    bool cursor_is_resize;
    bool is_in_resize_zone(double x, double y);
    void update_after_resize();

    int h;
};

#endif
