/*
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

#include "regionchooser.h"
#include <gdkmm/cursor.h>
#include <gtkmm/stock.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/dialog.h>
#include <libintl.h>
#include <math.h>

#define _(String) gettext(String)

RegionChooser::RegionChooser()
{
    Glib::RefPtr<Gdk::Colormap> colormap = get_default_colormap();

    red = Gdk::Color("#8070ff");
    grey1 = Gdk::Color("#b0b0b0");

    colormap->alloc_color(red);
    colormap->alloc_color(grey1);
    instrument = 0;
    region = 0;
    resize.active = false;
    move.active = false;
    cursor_is_resize = false;
    h1 = 20;
    width = 800;

    actionGroup = Gtk::ActionGroup::create();
    actionGroup->add(Gtk::Action::create("Properties",
                                         Gtk::Stock::PROPERTIES),
                     sigc::mem_fun(*this,
                                   &RegionChooser::show_region_properties));
    actionGroup->add(Gtk::Action::create("Remove", Gtk::Stock::REMOVE),
                     sigc::mem_fun(*this, &RegionChooser::delete_region));
    actionGroup->add(Gtk::Action::create("Add", Gtk::Stock::ADD),
                     sigc::mem_fun(*this, &RegionChooser::add_region));
    actionGroup->add(Gtk::Action::create("Dimensions", _("Dimensions...")),
                     sigc::mem_fun(*this, &RegionChooser::manage_dimensions));

    uiManager = Gtk::UIManager::create();
    uiManager->insert_action_group(actionGroup);
    Glib::ustring ui_info =
        "<ui>"
        "  <popup name='PopupMenuInsideRegion'>"
        "    <menuitem action='Properties'/>"
        "    <menuitem action='Dimensions'/>"
        "    <menuitem action='Remove'/>"
        "  </popup>"
        "  <popup name='PopupMenuOutsideRegion'>"
        "    <menuitem action='Add'/>"
        "  </popup>"
        "</ui>";
    uiManager->add_ui_from_string(ui_info);

    popup_menu_inside_region = dynamic_cast<Gtk::Menu*>(
        uiManager->get_widget("/PopupMenuInsideRegion"));
    popup_menu_outside_region = dynamic_cast<Gtk::Menu*>(
        uiManager->get_widget("/PopupMenuOutsideRegion"));

    add_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK |
               Gdk::POINTER_MOTION_MASK | Gdk::POINTER_MOTION_HINT_MASK);

    dimensionManager.region_to_be_changed_signal.connect(
        region_to_be_changed_signal.make_slot()
    );
    dimensionManager.region_changed_signal.connect(
        region_changed_signal.make_slot()
    );
    dimensionManager.region_changed_signal.connect(
        sigc::hide(
            sigc::mem_fun(*this, &RegionChooser::on_dimension_manager_changed)
        )
    );
}

RegionChooser::~RegionChooser()
{
}

void RegionChooser::on_realize()
{
    // We need to call the base on_realize()
    Gtk::DrawingArea::on_realize();

    // Now we can allocate any additional resources we need
    Glib::RefPtr<Gdk::Window> window = get_window();
    gc = Gdk::GC::create(window);
    window->clear();
}

bool RegionChooser::on_expose_event(GdkEventExpose* event)
{
    Glib::RefPtr<Gdk::Window> window = get_window();
    window->clear();
    const int h = 40;
    const int w = width - 1;
    const int bh = int(h * 0.55);

    Glib::RefPtr<const Gdk::GC> black = get_style()->get_black_gc();
    Glib::RefPtr<const Gdk::GC> white = get_style()->get_white_gc();

    Glib::RefPtr<Pango::Context> context = get_pango_context();
    Glib::RefPtr<Pango::Layout> layout = Pango::Layout::create(context);

    window->draw_rectangle(black, false, 0, h1, w, h - 1);
    gc->set_foreground(grey1);
    int x1 = int(w * 20.5 / 128.0 + 0.5);
    int x2 = int(w * 109.5 / 128.0 + 0.5);
    window->draw_rectangle(gc, true, 1, h1 + 1,
                           x1 - 1, h - 2);
    window->draw_rectangle(white, true, x1 + 1, h1 + 1, x2 - x1 - 1, h - 2);
    window->draw_rectangle(gc, true, x2 + 1, h1 + 1,
                           w - x2 - 1, h - 2);
    int octave = -1;
    for (int i = 0 ; i < 128 ; i++) {
        int note = (i + 3) % 12;
        int x = int(w * i / 128.0 + 0.5);

        if (note == 1 || note == 4 || note == 6 || note == 9 || note == 11) {
            int x2 = int(w * (i + 0.5) / 128.0 + 0.5);
            window->draw_line(black, x2, h1 + bh, x2, h1 + h);

            int x3 = int(w * (i + 1) / 128.0 + 0.5);
            window->draw_rectangle(black, true, x, h1 + 1, x3 - x + 1, bh);
        } else if (note == 3 || note == 8) {
            window->draw_line(black, x, h1 + 1, x, h1 + h);
        }
        if (note == 3) {
            char buf[30];
            sprintf(buf, "<span size=\"x-small\">%d</span>", octave);
            layout->set_markup(buf);
            Pango::Rectangle rectangle = layout->get_logical_extents();
            double text_w = double(rectangle.get_width()) / Pango::SCALE;
            double text_h = double(rectangle.get_height()) / Pango::SCALE;
            double x2 = w * (i + 0.75) / 128.0;
            window->draw_layout(black, int(x2 - text_w / 2 + 1),
                                int(h1 + h - text_h + 0.5), layout);
            octave++;
        }
    }

    if (instrument) {
        int i = 0;
        gig::Region *next_region;
        int x3 = -1;
        for (gig::Region *r = instrument->GetFirstRegion() ;
             r ;
             r = next_region) {

            if (x3 < 0) x3 = int(w * (r->KeyRange.low) / 128.0 + 0.5);
            next_region = instrument->GetNextRegion();
            if (!next_region || r->KeyRange.high + 1 != next_region->KeyRange.low) {
                int x2 = int(w * (r->KeyRange.high + 1) / 128.0 + 0.5);
                window->draw_line(black, x3, 0, x2, 0);
                window->draw_line(black, x3, h1 - 1, x2, h1 - 1);
                window->draw_line(black, x2, 1, x2, h1 - 2);
                window->draw_rectangle(white, true, x3 + 1, 1, x2 - x3 - 1, h1 - 2);
                x3 = -1;
            }
            i++;
        }

        for (gig::Region *r = instrument->GetFirstRegion() ;
             r ;
             r = instrument->GetNextRegion()) {
            int x = int(w * (r->KeyRange.low) / 128.0 + 0.5);
            window->draw_line(black, x, 1, x, h1 - 2);
        }

        if (region) {
            int x1 = int(w * (region->KeyRange.low) / 128.0 + 0.5);
            int x2 = int(w * (region->KeyRange.high + 1) / 128.0 + 0.5);
            gc->set_foreground(red);
            window->draw_rectangle(gc, true, x1 + 1, 1, x2 - x1 - 1, h1 - 2);
        }
    }
    return true;
}


void RegionChooser::on_size_request(GtkRequisition* requisition)
{
    *requisition = GtkRequisition();
    requisition->height = 40 + 20;
    requisition->width = 500;
}


// not used
void RegionChooser::draw_region(int from, int to, const Gdk::Color& color)
{
    const int h = 40;
    const int w = width;
    const int bh = int(h * 0.55);

    Glib::RefPtr<Gdk::Window> window = get_window();
    gc->set_foreground(color);

    for (int i = from ; i < to ; i++) {
        int note = (i + 3) % 12;
        int x = int(w * i / 128.0 + 0.5) + 1;
        int x2 = int(w * (i + 1.5) / 128.0 + 0.5);
        int x3 = int(w * (i + 1) / 128.0 + 0.5);
        int x4 = int(w * (i - 0.5) / 128 + 0.5) + 1;
        int w1 = x3 - x;
        switch (note) {
        case 0: case 5: case 10:
            window->draw_rectangle(gc, true, x, h1 + 1, w1, bh);
            window->draw_rectangle(gc, true, x4, h1 + bh + 1, x2 - x4, h - bh - 2);
            break;
        case 2: case 7:
            window->draw_rectangle(gc, true, x, h1 + 1, w1, bh);
            window->draw_rectangle(gc, true, x4, h1 + bh + 1, x3 - x4, h - bh - 2);
            break;
        case 3: case 8:
            window->draw_rectangle(gc, true, x, h1 + 1, w1, bh);
            window->draw_rectangle(gc, true, x, h1 + bh + 1, x2 - x, h - bh - 2);
            break;
        default:
            window->draw_rectangle(gc, true, x, h1 + 1, w1, bh - 1);
            break;
        }
    }
}

void RegionChooser::set_instrument(gig::Instrument* instrument)
{
    this->instrument = instrument;
    region = instrument ? instrument->GetFirstRegion() : 0;
    queue_draw();
    region_selected();
}

bool RegionChooser::on_button_release_event(GdkEventButton* event)
{
    if (resize.active) {
        get_window()->pointer_ungrab(event->time);
        resize.active = false;

        if (resize.mode == resize.moving_high_limit) {
            if (resize.region->KeyRange.high != resize.pos - 1) {
                resize.region->KeyRange.high = resize.pos - 1;
                instrument_changed();
            }
        } else if (resize.mode == resize.moving_low_limit) {
            if (resize.region->KeyRange.low != resize.pos) {
                resize.region->KeyRange.low = resize.pos;
                instrument_changed();
            }
        }

        if (!is_in_resize_zone(event->x, event->y) && cursor_is_resize) {
            get_window()->set_cursor();
            cursor_is_resize = false;
        }
    } else if (move.active) {
        get_window()->pointer_ungrab(event->time);
        move.active = false;

        if (move.pos) {
            region->KeyRange.low += move.pos;
            region->KeyRange.high += move.pos;

            // find the r which is the first one to the right of region
            // at its new position
            gig::Region* r;
            gig::Region* prev_region = 0;
            for (r = instrument->GetFirstRegion() ; r ; r = instrument->GetNextRegion()) {
                if (r->KeyRange.low > region->KeyRange.low) break;
                prev_region = r;
            }

            // place region before r if it's not already there
            if (prev_region != region) {
                instrument_struct_to_be_changed_signal.emit(instrument);
                instrument->MoveRegion(region, r);
                instrument_struct_changed_signal.emit(instrument);
            }
        }

        if (is_in_resize_zone(event->x, event->y)) {
            get_window()->set_cursor(Gdk::Cursor(Gdk::SB_H_DOUBLE_ARROW));
            cursor_is_resize = true;
        }
    }
    return true;
}

bool RegionChooser::on_button_press_event(GdkEventButton* event)
{
    if (!instrument) return true;

    int k = int(event->x / (width - 1) * 128.0);

    if (event->type == GDK_BUTTON_PRESS && event->button == 3) {
        gig::Region* r = get_region(k);
        if (r) {
            region = r;
            queue_draw();
            region_selected();
            popup_menu_inside_region->popup(event->button, event->time);
        } else {
            new_region_pos = k;
            popup_menu_outside_region->popup(event->button, event->time);
        }
    } else {
        if (is_in_resize_zone(event->x, event->y)) {
            get_window()->pointer_grab(false,
                                       Gdk::BUTTON_RELEASE_MASK |
                                       Gdk::POINTER_MOTION_MASK |
                                       Gdk::POINTER_MOTION_HINT_MASK,
                                       Gdk::Cursor(Gdk::SB_H_DOUBLE_ARROW), event->time);
            resize.active = true;
        } else {
            gig::Region* r = get_region(k);
            if (r) {
                region = r;
                queue_draw();
                region_selected();

                get_window()->pointer_grab(false,
                                           Gdk::BUTTON_RELEASE_MASK |
                                           Gdk::POINTER_MOTION_MASK |
                                           Gdk::POINTER_MOTION_HINT_MASK,
                                           Gdk::Cursor(Gdk::FLEUR), event->time);
                move.active = true;
                move.from_x = event->x;
                move.pos = 0;
            }
        }
    }
    return true;
}

gig::Region* RegionChooser::get_region(int key)
{
    gig::Region* prev_region = 0;
    gig::Region* next_region;
    for (gig::Region *r = instrument->GetFirstRegion() ; r ;
         r = next_region) {
        next_region = instrument->GetNextRegion();

        if (key < r->KeyRange.low) return 0;
        if (key <= r->KeyRange.high) {
            move.touch_left = prev_region && prev_region->KeyRange.high + 1 == r->KeyRange.low;
            move.touch_right = next_region && r->KeyRange.high + 1 == next_region->KeyRange.low;
            return r;
        }
        prev_region = r;
    }
    return 0;
}

void RegionChooser::motion_resize_region(int x, int y)
{
    const int w = width - 1;
    Glib::RefPtr<Gdk::Window> window = get_window();

    int k = int(double(x) / w * 128.0 + 0.5);

    if (k < resize.min) k = resize.min;
    else if (k > resize.max) k = resize.max;

    if (k != resize.pos) {
        if (resize.mode == resize.undecided) {
            if (k < resize.pos) {
                // edit high limit of prev_region
                resize.max = resize.region->KeyRange.low;
                resize.region = resize.prev_region;
                resize.mode = resize.moving_high_limit;
            } else {
                // edit low limit of region
                resize.min = resize.prev_region->KeyRange.high + 1;
                resize.mode = resize.moving_low_limit;
            }
        }
        Glib::RefPtr<const Gdk::GC> black = get_style()->get_black_gc();
        Glib::RefPtr<const Gdk::GC> white = get_style()->get_white_gc();
        if (region == resize.region) {
            gc->set_foreground(red);
            white = gc;
        }
        Glib::RefPtr<const Gdk::GC> bg = get_style()->get_bg_gc(Gtk::STATE_NORMAL);
        int prevx = int(w * resize.pos / 128.0 + 0.5);
        x = int(w * k / 128.0 + 0.5);

        if (resize.mode == resize.moving_high_limit) {
            if (k > resize.pos) {
                window->draw_rectangle(white, true, prevx, 1, x - prevx, h1 - 2);
                window->draw_line(black, prevx, 0, x, 0);
                window->draw_line(black, prevx, h1 - 1, x, h1 - 1);
            } else {
                int xx = ((resize.pos == resize.max && resize.max != 128) ? 1 : 0);
                window->draw_rectangle(bg, true, x + 1, 0, prevx - x - xx, h1);
            }
        } else {
            if (k < resize.pos) {
                window->draw_rectangle(white, true, x + 1, 1, prevx - x, h1 - 2);
                window->draw_line(black, x, 0, prevx, 0);
                window->draw_line(black, x, h1 - 1, prevx, h1 - 1);
            } else {
                int xx = ((resize.pos == resize.min && resize.min != 0) ? 1 : 0);
                window->draw_rectangle(bg, true, prevx + xx, 0, x - prevx - xx, h1);
            }
        }
        window->draw_line(black, x, 1, x, h1 - 2);
        resize.pos = k;
    }
}

void RegionChooser::motion_move_region(int x, int y)
{
    const int w = width - 1;
    Glib::RefPtr<Gdk::Window> window = get_window();

    int k = int(double(x - move.from_x) / w * 128.0 + 0.5);
    if (k == move.pos) return;
    int new_k;
    bool new_touch_left;
    bool new_touch_right;
    int a = 0;
    if (k > move.pos) {
        for (gig::Region* r = instrument->GetFirstRegion() ; ;
             r = instrument->GetNextRegion()) {
            if (r != region) {
                int b = r ? r->KeyRange.low : 128;

                // gap: from a to b (not inclusive b)

                if (region->KeyRange.high + move.pos >= b) {
                    // not found the current gap yet, just continue
                } else {

                    if (a > region->KeyRange.low + k) {
                        // this gap is too far to the right, break
                        break;
                    }

                    int newhigh = std::min(region->KeyRange.high + k, b - 1);
                    int newlo = newhigh - (region->KeyRange.high - region->KeyRange.low);

                    if (newlo >= a) {
                        // yes it fits - it's a candidate
                        new_k = newlo - region->KeyRange.low;
                        new_touch_left = a > 0 && a == newlo;
                        new_touch_right = b < 128 && newhigh + 1 == b;
                    }
                }
                if (!r) break;
                a = r->KeyRange.high + 1;
            }
        }
    } else {
        for (gig::Region* r = instrument->GetFirstRegion() ; ;
             r = instrument->GetNextRegion()) {
            if (r != region) {
                int b = r ? r->KeyRange.low : 128;

                // gap from a to b (not inclusive b)

                if (region->KeyRange.high + k >= b) {
                    // not found the current gap yet, just continue
                } else {

                    if (a > region->KeyRange.low + move.pos) {
                        // this gap is too far to the right, break
                        break;
                    }

                    int newlo = std::max(region->KeyRange.low + k, a);
                    int newhigh = newlo + (region->KeyRange.high - region->KeyRange.low);

                    if (newhigh < b) {
                        // yes it fits - break as the first one is the best
                        new_k = newlo - region->KeyRange.low;
                        new_touch_left = a > 0 && a == newlo;
                        new_touch_right = b < 128 && newhigh + 1 == b;
                        break;
                    }
                }
                if (!r) break;
                a = r->KeyRange.high + 1;
            }
        }
    }
    k = new_k;
    if (k == move.pos) return;

    Glib::RefPtr<const Gdk::GC> bg = get_style()->get_bg_gc(Gtk::STATE_NORMAL);
    int prevx = int(w * (move.pos + region->KeyRange.low) / 128.0 + 0.5);
    x = int(w * (k + region->KeyRange.low) / 128.0 + 0.5);
    int prevx2 = int(w * (move.pos + region->KeyRange.high + 1) / 128.0 + 0.5);
    int x2 = int(w * (k + region->KeyRange.high + 1) / 128.0 + 0.5);
    Glib::RefPtr<const Gdk::GC> black = get_style()->get_black_gc();
    gc->set_foreground(red);

    if (!new_touch_left) window->draw_line(black, x, 1, x, h1 - 2);
    if (!new_touch_right) window->draw_line(black, x2, 1, x2, h1 - 2);

    if (k > move.pos) {
        window->draw_rectangle(bg, true, prevx + (move.touch_left ? 1 : 0), 0,
                               std::min(x, prevx2 + 1 - (move.touch_right ? 1 : 0)) -
                               (prevx + (move.touch_left ? 1 : 0)), h1);

        window->draw_line(black, std::max(x, prevx2 + 1), 0, x2, 0);
        window->draw_line(black, std::max(x, prevx2 + 1), h1 - 1, x2, h1 - 1);
        window->draw_rectangle(gc, true, std::max(x + 1, prevx2), 1,
                               x2 - std::max(x + 1, prevx2), h1 - 2);
    } else {
        window->draw_rectangle(bg, true, std::max(x2 + 1, prevx + (move.touch_left ? 1 : 0)), 0,
                               prevx2 + 1 - (move.touch_right ? 1 : 0) -
                               std::max(x2 + 1, prevx + (move.touch_left ? 1 : 0)), h1);

        window->draw_line(black, x, 0, std::min(x2, prevx - 1), 0);
        window->draw_line(black, x, h1 - 1, std::min(x2, prevx - 1), h1 - 1);

        window->draw_rectangle(gc, true, x + 1, 1, std::min(x2 - 1, prevx) - x, h1 - 2);
    }

    move.pos = k;
    move.touch_left = new_touch_left;
    move.touch_right = new_touch_right;
}


bool RegionChooser::on_motion_notify_event(GdkEventMotion* event)
{
    Glib::RefPtr<Gdk::Window> window = get_window();
    int x, y;
    Gdk::ModifierType state = Gdk::ModifierType(0);
    window->get_pointer(x, y, state);

    if (resize.active) {
        motion_resize_region(x, y);
    } else if (move.active) {
        motion_move_region(x, y);
    } else {
        if (is_in_resize_zone(x, y)) {
            if (!cursor_is_resize) {
                window->set_cursor(Gdk::Cursor(Gdk::SB_H_DOUBLE_ARROW));
                cursor_is_resize = true;
            }
        } else if (cursor_is_resize) {
            window->set_cursor();
            cursor_is_resize = false;
        }
    }

    return true;
}

bool RegionChooser::is_in_resize_zone(double x, double y) {
    const int w = width - 1;

    if (instrument && y >= 0 && y <= h1) {
        gig::Region* prev_region = 0;
        gig::Region* next_region;
        for (gig::Region* r = instrument->GetFirstRegion() ; r ; r = next_region) {
            next_region = instrument->GetNextRegion();

            int lo = int(w * (r->KeyRange.low) / 128.0 + 0.5);
            if (x <= lo - 2) break;
            if (x < lo + 2) {
                resize.region = r;
                resize.pos = r->KeyRange.low;
                resize.max = r->KeyRange.high;

                if (prev_region && prev_region->KeyRange.high + 1 == r->KeyRange.low) {
                    // we don't know yet if it's the high limit of
                    // prev_region or the low limit of r that's going
                    // to be edited
                    resize.mode = resize.undecided;
                    resize.min = prev_region->KeyRange.low + 1;
                    resize.prev_region = prev_region;
                    return true;
                }

                // edit low limit
                resize.mode = resize.moving_low_limit;
                resize.min = prev_region ? prev_region->KeyRange.high + 1 : 0;
                return true;
            }
            if (!next_region || r->KeyRange.high + 1 != next_region->KeyRange.low) {
                int hi = int(w * (r->KeyRange.high + 1) / 128.0 + 0.5);
                if (x <= hi - 2) break;
                if (x < hi + 2) {
                    // edit high limit
                    resize.region = r;
                    resize.pos = r->KeyRange.high + 1;
                    resize.mode = resize.moving_high_limit;
                    resize.min = r->KeyRange.low + 1;
                    resize.max = next_region ? next_region->KeyRange.low : 128;
                    return true;
                }
            }
            prev_region = r;
        }
    }
    return false;
}

sigc::signal<void> RegionChooser::signal_region_selected()
{
    return region_selected;
}

sigc::signal<void> RegionChooser::signal_instrument_changed()
{
    return instrument_changed;
}

void RegionChooser::show_region_properties()
{
    if (!region) return;
    Gtk::Dialog dialog("Region Properties", true /*modal*/);
    // add "Keygroup" checkbox
    Gtk::CheckButton checkBoxKeygroup("Member of a Keygroup (Exclusive Group)");
    checkBoxKeygroup.set_active(region->KeyGroup);
    dialog.get_vbox()->pack_start(checkBoxKeygroup);
    checkBoxKeygroup.show();
    // add "Keygroup" spinbox
    Gtk::Adjustment adjustment(1, 1, pow(2,32));
    Gtk::SpinButton spinBox(adjustment);
    if (region->KeyGroup) spinBox.set_value(region->KeyGroup);
    dialog.get_vbox()->pack_start(spinBox);
    spinBox.show();
    // add OK and CANCEL buttons to the dialog
    dialog.add_button(Gtk::Stock::OK, 0);
    dialog.add_button(Gtk::Stock::CANCEL, 1);
    dialog.show_all_children();
    if (!dialog.run()) { // OK selected ...
        region->KeyGroup =
            (checkBoxKeygroup.get_active()) ? spinBox.get_value_as_int() : 0;
    }
}

void RegionChooser::add_region()
{
    gig::Region* r;
    for (r = instrument->GetFirstRegion() ; r ; r = instrument->GetNextRegion()) {
        if (r->KeyRange.low > new_region_pos) break;
    }

    instrument_struct_to_be_changed_signal.emit(instrument);

    region = instrument->AddRegion();
    region->KeyRange.low = region->KeyRange.high = new_region_pos;

    instrument->MoveRegion(region, r);

    instrument_struct_changed_signal.emit(instrument);

    queue_draw();
    region_selected();
    instrument_changed();
}

void RegionChooser::delete_region()
{
    instrument_struct_to_be_changed_signal.emit(instrument);
    instrument->DeleteRegion(region);
    instrument_struct_changed_signal.emit(instrument);

    region = 0;
    queue_draw();
    region_selected();
    instrument_changed();
}

void RegionChooser::manage_dimensions()
{
    gig::Region* region = get_region();
    if (!region) return;
    dimensionManager.show(region);
}

void RegionChooser::on_dimension_manager_changed() {
    region_selected();
    instrument_changed();
}

sigc::signal<void, gig::Instrument*> RegionChooser::signal_instrument_struct_to_be_changed() {
    return instrument_struct_to_be_changed_signal;
}

sigc::signal<void, gig::Instrument*> RegionChooser::signal_instrument_struct_changed() {
    return instrument_struct_changed_signal;
}

sigc::signal<void, gig::Region*> RegionChooser::signal_region_to_be_changed() {
    return region_to_be_changed_signal;
}

sigc::signal<void, gig::Region*> RegionChooser::signal_region_changed_signal() {
    return region_changed_signal;
}
