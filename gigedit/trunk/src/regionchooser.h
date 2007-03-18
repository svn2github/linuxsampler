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

#ifndef GIGEDIT_REGIONCHOOSER_H
#define GIGEDIT_REGIONCHOOSER_H

#include <gtkmm/drawingarea.h>
#include <gdkmm/colormap.h>
#include <gtkmm/uimanager.h>
#include <gdkmm/window.h>

#include <gtkmm/menu.h>

#include <gig.h>

class RegionChooser : public Gtk::DrawingArea
{
public:
    RegionChooser();
    virtual ~RegionChooser();

    void set_instrument(gig::Instrument* instrument);
    void set_region(gig::Region* region);

    sigc::signal<void> signal_sel_changed();

    gig::Region* get_region() { return region; }

protected:
    virtual void on_realize();
    virtual bool on_expose_event(GdkEventExpose* e);
    virtual void on_size_request(GtkRequisition* requisition);
    virtual bool on_button_press_event(GdkEventButton* event);
    virtual bool on_button_release_event(GdkEventButton* event);
    virtual bool on_motion_notify_event(GdkEventMotion* event);

    gig::Region* get_region(int key);

    Glib::RefPtr<Gdk::GC> gc;
    Gdk::Color blue, red, black, white, green, grey1;

    void draw_region(int from, int to, const Gdk::Color& color);

    sigc::signal<void> sel_changed_signal;

    gig::Instrument* instrument;
    gig::Region* region;

    // information needed during a resize
    struct {
        bool active;
        enum {
            undecided,
            moving_high_limit,
            moving_low_limit
        } mode;
        int pos;
        int min;
        int max;
        gig::Region* region;
        gig::Region* prev_region;
    } resize;

    bool cursor_is_resize;
    bool is_in_resize_zone(double x, double y);

    int h1;
    int width;

    Gtk::Menu* popup_menu_inside_region;
    Gtk::Menu* popup_menu_outside_region;
    void show_region_properties();
    void add_region();
    void delete_region();
    int new_region_pos;

    Glib::RefPtr<Gtk::ActionGroup> actionGroup;
    Glib::RefPtr<Gtk::UIManager> uiManager;
};

#endif
