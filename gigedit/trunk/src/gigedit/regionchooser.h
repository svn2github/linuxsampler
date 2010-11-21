/*                                                         -*- c++ -*-
 * Copyright (C) 2006-2010 Andreas Persson
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

#include <vector>

#include <gtkmm/drawingarea.h>
#include <gtkmm/uimanager.h>
#include <gdkmm/window.h>
#include <gtkmm/menu.h>

#include "dimensionmanager.h"
#include "paramedit.h"

#include <gig.h>

enum virt_keyboard_mode_t {
    VIRT_KEYBOARD_MODE_NORMAL,
    VIRT_KEYBOARD_MODE_CHORD
};

class SortedRegions {
private:
    std::vector<gig::Region*> regions;
    std::vector<gig::Region*>::iterator region_iterator;

public:
    void update(gig::Instrument* instrument);
    gig::Region* first();
    gig::Region* next();
    bool operator() (gig::Region* x, gig::Region* y) {
        return x->KeyRange.low < y->KeyRange.low;
    }
};

class RegionChooser : public Gtk::DrawingArea
{
public:
    RegionChooser();
    virtual ~RegionChooser();

    void set_instrument(gig::Instrument* instrument);

    sigc::signal<void>& signal_region_selected();
    sigc::signal<void>& signal_instrument_changed();

    sigc::signal<void, gig::Instrument*>& signal_instrument_struct_to_be_changed();
    sigc::signal<void, gig::Instrument*>& signal_instrument_struct_changed();

    sigc::signal<void, gig::Region*>& signal_region_to_be_changed();
    sigc::signal<void, gig::Region*>& signal_region_changed_signal();

    sigc::signal<void, int/*key*/, int/*velocity*/>& signal_keyboard_key_hit();
    sigc::signal<void, int/*key*/, int/*velocity*/>& signal_keyboard_key_released();

    gig::Region* get_region() { return region; }

    void on_note_on_event(int key, int velocity);
    void on_note_off_event(int key, int velocity);

    Gtk::HBox m_VirtKeybPropsBox;

protected:
    virtual bool on_expose_event(GdkEventExpose* e);
    virtual void on_size_request(GtkRequisition* requisition);
    virtual bool on_button_press_event(GdkEventButton* event);
    virtual bool on_button_release_event(GdkEventButton* event);
    virtual bool on_motion_notify_event(GdkEventMotion* event);

    gig::Region* get_region(int key);

    Gdk::Color activeKeyColor, red, grey1, white, black;

    sigc::signal<void> region_selected;
    sigc::signal<void> instrument_changed;

    sigc::signal<void, gig::Instrument*> instrument_struct_to_be_changed_signal;
    sigc::signal<void, gig::Instrument*> instrument_struct_changed_signal;

    sigc::signal<void, gig::Region*> region_to_be_changed_signal;
    sigc::signal<void, gig::Region*> region_changed_signal;

    sigc::signal<void, int/*key*/, int/*velocity*/> keyboard_key_hit_signal;
    sigc::signal<void, int/*key*/, int/*velocity*/> keyboard_key_released_signal;

    gig::Instrument* instrument;
    gig::Region* region;
    SortedRegions regions;

    bool is_black_key(int key);
    void draw_key(int key, const Gdk::Color& color);
    void draw_digit(int key);
    void motion_resize_region(int x, int y);
    void motion_move_region(int x, int y);

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

    // information needed during a region move
    struct {
        bool active;
        double from_x;
        int pos;
        bool touch_left;
        bool touch_right;
    } move;

    bool cursor_is_resize;
    bool is_in_resize_zone(double x, double y);

    int h1;

    Gtk::Menu* popup_menu_inside_region;
    Gtk::Menu* popup_menu_outside_region;
    void show_region_properties();
    void add_region();
    void delete_region();
    void manage_dimensions();
    void on_dimension_manager_changed();
    int new_region_pos;

    Glib::RefPtr<Gtk::ActionGroup> actionGroup;
    Glib::RefPtr<Gtk::UIManager> uiManager;

    // properties of the virtaul keyboard
    ChoiceEntry<virt_keyboard_mode_t> m_VirtKeybModeChoice;
    Gtk::Label m_VirtKeybVelocityLabelDescr;
    Gtk::Label m_VirtKeybVelocityLabel;
    Gtk::Label m_VirtKeybOffVelocityLabelDescr;
    Gtk::Label m_VirtKeybOffVelocityLabel;
    int currentActiveKey;

    DimensionManager dimensionManager;
};

#endif
