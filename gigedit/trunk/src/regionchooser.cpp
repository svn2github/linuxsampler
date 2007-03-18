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

RegionChooser::RegionChooser()
{
    Glib::RefPtr<Gdk::Colormap> colormap = get_default_colormap();

    black = Gdk::Color("black");
    white = Gdk::Color("white");
    red = Gdk::Color("#8070ff");
    blue = Gdk::Color("#c098ff");
    green = Gdk::Color("#a088ff");
    grey1 = Gdk::Color("red");

    colormap->alloc_color(black);
    colormap->alloc_color(white);
    colormap->alloc_color(red);
    colormap->alloc_color(blue);
    colormap->alloc_color(green);
    colormap->alloc_color(grey1);
    instrument = 0;
    region = 0;
    resize.active = false;
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

    uiManager = Gtk::UIManager::create();
    uiManager->insert_action_group(actionGroup);
    Glib::ustring ui_info =
        "<ui>"
        "  <popup name='PopupMenuInsideRegion'>"
        "    <menuitem action='Properties'/>"
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

    window->draw_rectangle(black, false, 0, h1, w, h - 1);
    window->draw_rectangle(white, true, 1, h1 + 1, w - 1, h - 2);
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
    }

    if (instrument) {
        int i = 0;
        gig::Region *nextRegion;
        int x3 = -1;
        for (gig::Region *r = instrument->GetFirstRegion() ;
             r ;
             r = nextRegion) {

            if (x3 < 0) x3 = int(w * (r->KeyRange.low) / 128.0 + 0.5);
            nextRegion = instrument->GetNextRegion();
            if (!nextRegion || r->KeyRange.high + 1 != nextRegion->KeyRange.low) {
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
    sel_changed_signal.emit();
}

bool RegionChooser::on_button_release_event(GdkEventButton* event)
{
    if (resize.active) {
        get_window()->pointer_ungrab(event->time);
        resize.active = false;

        if (resize.mode == resize.moving_high_limit) {
            resize.region->KeyRange.high = resize.pos - 1;
        } else if (resize.mode == resize.moving_low_limit) {
            resize.region->KeyRange.low = resize.pos;
        }

        if (!is_in_resize_zone(event->x, event->y) && cursor_is_resize) {
            get_window()->set_cursor();
            cursor_is_resize = false;
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
            sel_changed_signal.emit();
            popup_menu_inside_region->popup(event->button, event->time);
        } else {
            new_region_pos = k;
            popup_menu_outside_region->popup(event->button, event->time);
        }
    } else {
        if (is_in_resize_zone(event->x, event->y)) {
            Gdk::Cursor double_arrow(Gdk::SB_H_DOUBLE_ARROW);
            get_window()->pointer_grab(false,
                                       Gdk::BUTTON_RELEASE_MASK |
                                       Gdk::POINTER_MOTION_MASK |
                                       Gdk::POINTER_MOTION_HINT_MASK,
                                       double_arrow, event->time);
            resize.active = true;
        } else {
            gig::Region* r = get_region(k);
            if (r) {
                region = r;
                queue_draw();
                sel_changed_signal.emit();
            }
        }
    }
    return true;
}

gig::Region* RegionChooser::get_region(int key)
{
    for (gig::Region *r = instrument->GetFirstRegion() ; r ;
         r = instrument->GetNextRegion()) {
        if (key < r->KeyRange.low) return 0;
        if (key <= r->KeyRange.high) return r;
    }
    return 0;
}

bool RegionChooser::on_motion_notify_event(GdkEventMotion* event)
{
    const int w = width - 1;
    Glib::RefPtr<Gdk::Window> window = get_window();
    int x, y;
    Gdk::ModifierType state = Gdk::ModifierType(0);
    window->get_pointer(x, y, state);
    if (resize.active) {
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
    } else {
        if (is_in_resize_zone(x, y)) {
            if (!cursor_is_resize) {
                Gdk::Cursor double_arrow(Gdk::SB_H_DOUBLE_ARROW);
                window->set_cursor(double_arrow);
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

sigc::signal<void> RegionChooser::signal_sel_changed()
{
    return sel_changed_signal;
}

void RegionChooser::show_region_properties()
{
}

void RegionChooser::add_region()
{
    gig::Region* r;
    for (r = instrument->GetFirstRegion() ; r ; r = instrument->GetNextRegion()) {
        if (r->KeyRange.low > new_region_pos) break;
    }

    region = instrument->AddRegion();
    region->KeyRange.low = region->KeyRange.high = new_region_pos;

    instrument->MoveRegion(region, r);
    queue_draw();
    sel_changed_signal.emit();
}

void RegionChooser::delete_region()
{
    instrument->DeleteRegion(region);
    region = 0;
    queue_draw();
    sel_changed_signal.emit();
}
