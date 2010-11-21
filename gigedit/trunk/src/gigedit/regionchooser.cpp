/*
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

#include "regionchooser.h"

#include <algorithm>
#include <cmath>
#include <sstream>

#include <cairomm/context.h>
#include <gdkmm/general.h>
#include <gdkmm/cursor.h>
#include <gtkmm/stock.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/dialog.h>

#include "global.h"

#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 10) || GTKMM_MAJOR_VERSION < 2

#define create_cairo_context()                                          \
    gobj() ? Cairo::RefPtr<Cairo::Context>(                             \
        new Cairo::Context(gdk_cairo_create(get_window()->gobj()))) :   \
    Cairo::RefPtr<Cairo::Context>()

namespace Gdk {
    namespace Cairo {
        void set_source_color(const ::Cairo::RefPtr< ::Cairo::Context >& cr,
                              const Gdk::Color& color) {
            gdk_cairo_set_source_color(cr->cobj(),
                                       const_cast<GdkColor*>(color.gobj()));
        }
    }
}
#endif

#define REGION_BLOCK_HEIGHT		20
#define KEYBOARD_HEIGHT			40

void SortedRegions::update(gig::Instrument* instrument) {
    // Usually, the regions in a gig file are ordered after their key
    // range, but there are files where they are not. The
    // RegionChooser code needs a sorted list of regions.
    regions.clear();
    if (instrument) {
        for (gig::Region* r = instrument->GetFirstRegion() ;
             r ;
             r = instrument->GetNextRegion()) {
            regions.push_back(r);
        }
        sort(regions.begin(), regions.end(), *this);
    }
}

gig::Region* SortedRegions::first() {
    region_iterator = regions.begin();
    return region_iterator == regions.end() ? 0 : *region_iterator;
}

gig::Region* SortedRegions::next() {
    region_iterator++;
    return region_iterator == regions.end() ? 0 : *region_iterator;
}



RegionChooser::RegionChooser() :
    m_VirtKeybModeChoice(_("Virtual Keyboard Mode")),
    currentActiveKey(-1)
{
    red = Gdk::Color("#8070ff");
    grey1 = Gdk::Color("#b0b0b0");
    activeKeyColor = Gdk::Color("#ff0000");
    white = Gdk::Color("#ffffff");
    black = Gdk::Color("#000000");

    instrument = 0;
    region = 0;
    resize.active = false;
    move.active = false;
    cursor_is_resize = false;
    h1 = REGION_BLOCK_HEIGHT;

    // properties of the virtual keyboard
    {
        const char* choices[] = { _("normal"), _("chord"), NULL };
        static const virt_keyboard_mode_t values[] = {
            VIRT_KEYBOARD_MODE_NORMAL,
            VIRT_KEYBOARD_MODE_CHORD
        };
        m_VirtKeybModeChoice.set_choices(choices, values);
        m_VirtKeybModeChoice.set_value(VIRT_KEYBOARD_MODE_NORMAL);
    }
    m_VirtKeybVelocityLabelDescr.set_text(_("Note-On Velocity:"));
    m_VirtKeybVelocityLabel.set_text("-");
    m_VirtKeybOffVelocityLabelDescr.set_text(_("Note-Off Velocity:"));
    m_VirtKeybOffVelocityLabel.set_text("-");
    m_VirtKeybPropsBox.pack_start(m_VirtKeybModeChoice.label, Gtk::PACK_SHRINK);
    m_VirtKeybPropsBox.pack_start(m_VirtKeybModeChoice.widget, Gtk::PACK_SHRINK);
    m_VirtKeybPropsBox.pack_start(m_VirtKeybVelocityLabelDescr, Gtk::PACK_SHRINK);
    m_VirtKeybPropsBox.pack_start(m_VirtKeybVelocityLabel, Gtk::PACK_SHRINK);
    m_VirtKeybPropsBox.pack_start(m_VirtKeybOffVelocityLabelDescr, Gtk::PACK_SHRINK);
    m_VirtKeybPropsBox.pack_start(m_VirtKeybOffVelocityLabel, Gtk::PACK_SHRINK);
    m_VirtKeybPropsBox.set_spacing(10);
    m_VirtKeybPropsBox.show();

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
    keyboard_key_hit_signal.connect(
        sigc::mem_fun(*this, &RegionChooser::on_note_on_event)
    );
    keyboard_key_released_signal.connect(
        sigc::mem_fun(*this, &RegionChooser::on_note_off_event)
    );
}

RegionChooser::~RegionChooser()
{
}

template<class T> inline std::string ToString(T o) {
    std::stringstream ss;
    ss << o;
    return ss.str();
}

void RegionChooser::on_note_on_event(int key, int velocity) {
    draw_key(key, activeKeyColor);
    m_VirtKeybVelocityLabel.set_text(ToString(velocity));
}

void RegionChooser::on_note_off_event(int key, int velocity) {
    if (is_black_key(key)) {
        draw_key(key, black);
    } else {
        draw_key(key, key >= 21 && key <= 108 ? white : grey1);
    }
    m_VirtKeybOffVelocityLabel.set_text(ToString(velocity));
}


bool RegionChooser::on_expose_event(GdkEventExpose* event)
{
    Glib::RefPtr<Gdk::Window> window = get_window();
    if (window) {
        Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
        if (event) {
            cr->rectangle(event->area.x, event->area.y,
                          event->area.width, event->area.height);
            cr->clip();
        }
        const int h = KEYBOARD_HEIGHT;
        const int w = get_width() - 1;
        const int bh = int(h * 0.55);

        cr->save();
        cr->set_line_width(1);

        const Gdk::Color bg = get_style()->get_bg(Gtk::STATE_NORMAL);
        Gdk::Cairo::set_source_color(cr, bg);
        cr->paint();

        Gdk::Cairo::set_source_color(cr, black);
        cr->rectangle(0.5, h1 + 0.5, w, h - 1);
        cr->stroke();

        int x1 = int(w * 20.5 / 128.0 + 0.5);
        int x2 = int(w * 109.5 / 128.0 + 0.5);

        Gdk::Cairo::set_source_color(cr, grey1);
        cr->rectangle(1, h1 + 1, x1 - 1, h - 2);
        cr->fill();

        Gdk::Cairo::set_source_color(cr, white);
        cr->rectangle(x1 + 1, h1 + 1, x2 - x1 - 1, h - 2);
        cr->fill();

        Gdk::Cairo::set_source_color(cr, grey1);
        cr->rectangle(x2 + 1, h1 + 1, w - x2 - 1, h - 2);
        cr->fill();

        Gdk::Cairo::set_source_color(cr, black);
        for (int i = 0 ; i < 128 ; i++) {
            int note = (i + 3) % 12;
            int x = int(w * i / 128.0 + 0.5);

            if (note == 1 || note == 4 || note == 6 ||
                note == 9 || note == 11) {
                int x2 = int(w * (i + 0.5) / 128.0 + 0.5);
                cr->move_to(x2 + 0.5, h1 + bh + 0.5);
                cr->line_to(x2 + 0.5, h1 + h - 1);
                cr->stroke();

                int x3 = int(w * (i + 1) / 128.0 + 0.5);
                cr->rectangle(x, h1 + 1, x3 - x + 1, bh);
                cr->fill();
            } else if (note == 3 || note == 8) {
                cr->move_to(x + 0.5, h1 + 1);
                cr->line_to(x + 0.5, h1 + h - 1);
                cr->stroke();

                if (note == 3) draw_digit(i);
            }
        }

        if (instrument) {
            int i = 0;
            gig::Region* next_region;
            int x3 = -1;
            for (gig::Region* r = regions.first() ; r ; r = next_region) {

                if (x3 < 0) x3 = int(w * (r->KeyRange.low) / 128.0 + 0.5);
                next_region = regions.next();
                if (!next_region ||
                    r->KeyRange.high + 1 != next_region->KeyRange.low) {
                    int x2 = int(w * (r->KeyRange.high + 1) / 128.0 + 0.5);
                    cr->move_to(x3, 0.5);
                    cr->line_to(x2 + 0.5, 0.5);
                    cr->line_to(x2 + 0.5, h1 - 0.5);
                    cr->line_to(x3, h1 - 0.5);
                    cr->stroke();

                    Gdk::Cairo::set_source_color(cr, white);
                    cr->rectangle(x3 + 1, 1, x2 - x3 - 1, h1 - 2);
                    cr->fill();
                    Gdk::Cairo::set_source_color(cr, black);

                    x3 = -1;
                }
                i++;
            }

            for (gig::Region* r = regions.first() ; r ; r = regions.next()) {
                int x = int(w * (r->KeyRange.low) / 128.0 + 0.5);
                cr->move_to(x + 0.5, 1);
                cr->line_to(x + 0.5, h1 - 1);
                cr->stroke();
            }

            if (region) {
                int x1 = int(w * (region->KeyRange.low) / 128.0 + 0.5);
                int x2 = int(w * (region->KeyRange.high + 1) / 128.0 + 0.5);
                Gdk::Cairo::set_source_color(cr, red);
                cr->rectangle(x1 + 1, 1, x2 - x1 - 1, h1 - 2);
                cr->fill();
            }
        }

        cr->restore();
    }

    return true;
}


void RegionChooser::on_size_request(GtkRequisition* requisition)
{
    *requisition = GtkRequisition();
    requisition->height = KEYBOARD_HEIGHT + REGION_BLOCK_HEIGHT;
    requisition->width = 500;
}

bool RegionChooser::is_black_key(int key) {
    const int note = (key + 3) % 12;
    return note == 1 || note == 4 || note == 6 || note == 9 || note == 11;
}

void RegionChooser::draw_digit(int key) {
    const int h = KEYBOARD_HEIGHT;
    const int w = get_width() - 1;
    Glib::RefPtr<Pango::Layout> layout = Pango::Layout::create(get_pango_context());
    char buf[30];
    sprintf(buf, "<span size=\"8000\">%d</span>", key / 12 - 1);
    layout->set_markup(buf);
    Pango::Rectangle rectangle = layout->get_logical_extents();
    double text_w = double(rectangle.get_width()) / Pango::SCALE;
    double text_h = double(rectangle.get_height()) / Pango::SCALE;
    double x = w * (key + 0.75) / 128.0;
    Cairo::RefPtr<Cairo::Context> cr = get_window()->create_cairo_context();
    Gdk::Cairo::set_source_color(cr, black);
    cr->move_to(int(x - text_w / 2 + 1), int(h1 + h - text_h + 0.5));
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 16) || GTKMM_MAJOR_VERSION < 2
    pango_cairo_show_layout(cr->cobj(), layout->gobj());
#else
    layout->show_in_cairo_context(cr);
#endif
}

void RegionChooser::draw_key(int key, const Gdk::Color& color)
{
    const int h = KEYBOARD_HEIGHT;
    const int w = get_width() - 1;
    const int bh = int(h * 0.55);

    Cairo::RefPtr<Cairo::Context> cr = get_window()->create_cairo_context();
    Gdk::Cairo::set_source_color(cr, color);

    int note = (key + 3) % 12;
    int x = int(w * key / 128.0 + 0.5) + 1;
    int x2 = int(w * (key + 1.5) / 128.0 + 0.5);
    int x3 = int(w * (key + 1) / 128.0 + 0.5);
    int x4 = int(w * (key - 0.5) / 128.0 + 0.5);
    int w1 = x3 - x;
    switch (note) {
    case 0: case 5: case 10:
        cr->rectangle(x, h1 + 1, w1, bh);
        cr->fill();
        cr->rectangle(x4 + 1, h1 + bh + 1, x2 - x4 - 1, h - bh - 2);
        cr->fill();
        break;
    case 2: case 7:
        cr->rectangle(x, h1 + 1, w1, bh);
        cr->fill();
        cr->rectangle(x4 + 1, h1 + bh + 1, x3 - x4 - 1, h - bh - 2);
        cr->fill();
        break;
    case 3: case 8:
        cr->rectangle(x, h1 + 1, w1, bh);
        cr->fill();
        cr->rectangle(x, h1 + bh + 1, x2 - x, h - bh - 2);
        cr->fill();
        if (note == 3) draw_digit(key);
        break;
    default:
        cr->rectangle(x, h1 + 1, w1, bh - 1);
        cr->fill();
        break;
    }
}

void RegionChooser::set_instrument(gig::Instrument* instrument)
{
    this->instrument = instrument;
    regions.update(instrument);
    region = regions.first();
    queue_draw();
    region_selected();
    dimensionManager.set_region(region);
}

bool RegionChooser::on_button_release_event(GdkEventButton* event)
{
    const int k = int(event->x / (get_width() - 1) * 128.0);

    // handle-note off on virtual keyboard
    if (event->type == GDK_BUTTON_RELEASE) {
        int velocity = (event->y >= REGION_BLOCK_HEIGHT + KEYBOARD_HEIGHT - 1) ? 127 :
                       int(float(event->y - REGION_BLOCK_HEIGHT) / float(KEYBOARD_HEIGHT) * 128.0f) + 1;
        if (velocity <= 0) velocity = 1;
        switch (m_VirtKeybModeChoice.get_value()) {
            case VIRT_KEYBOARD_MODE_CHORD:
                if (event->y >= REGION_BLOCK_HEIGHT)
                    keyboard_key_released_signal.emit(k, velocity);
                break;
            case VIRT_KEYBOARD_MODE_NORMAL:
            default:
                if (currentActiveKey >= 0 && currentActiveKey <= 127) {
                    keyboard_key_released_signal.emit(currentActiveKey, velocity);
                    currentActiveKey = -1;
                }
                break;
        }
    }

    if (resize.active) {
        get_window()->pointer_ungrab(event->time);
        resize.active = false;

        if (resize.mode == resize.moving_high_limit) {
            if (resize.region->KeyRange.high != resize.pos - 1) {
                instrument_struct_to_be_changed_signal.emit(instrument);
                resize.region->SetKeyRange(
                    resize.region->KeyRange.low, // low
                    resize.pos - 1 // high
                );
                regions.update(instrument);
                instrument_changed.emit();
                instrument_struct_changed_signal.emit(instrument);
            }
        } else if (resize.mode == resize.moving_low_limit) {
            if (resize.region->KeyRange.low != resize.pos) {
                instrument_struct_to_be_changed_signal.emit(instrument);
                resize.region->SetKeyRange(
                    resize.pos, // low
                    resize.region->KeyRange.high // high
                );
                regions.update(instrument);
                instrument_changed.emit();
                instrument_struct_changed_signal.emit(instrument);
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
            instrument_struct_to_be_changed_signal.emit(instrument);
            region->SetKeyRange(
                region->KeyRange.low  + move.pos,
                region->KeyRange.high + move.pos
            );
            regions.update(instrument);
            instrument_changed.emit();
            instrument_struct_changed_signal.emit(instrument);
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

    const int k = int(event->x / (get_width() - 1) * 128.0);

    if (event->type == GDK_BUTTON_PRESS) {
        if (event->y >= REGION_BLOCK_HEIGHT) {
            int velocity = (event->y >= REGION_BLOCK_HEIGHT + KEYBOARD_HEIGHT - 1) ? 127 :
                           int(float(event->y - REGION_BLOCK_HEIGHT) / float(KEYBOARD_HEIGHT) * 128.0f) + 1;
            currentActiveKey = k;
            keyboard_key_hit_signal.emit(k, velocity);
        }
    }

    if (event->y >= REGION_BLOCK_HEIGHT) return true;
    if (event->type == GDK_BUTTON_PRESS && event->button == 3) {
        gig::Region* r = get_region(k);
        if (r) {
            region = r;
            queue_draw();
            region_selected();
            dimensionManager.set_region(region);
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
                dimensionManager.set_region(region);

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
    for (gig::Region* r = regions.first() ; r ; r = next_region) {
        next_region = regions.next();

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
    const int w = get_width() - 1;

    int k = int(double(x) / w * 128.0 + 0.5);

    if (k < resize.min) k = resize.min;
    else if (k > resize.max) k = resize.max;

    if (k != resize.pos) {
        Cairo::RefPtr<Cairo::Context> cr = get_window()->create_cairo_context();
        cr->set_line_width(1);

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
        const Gdk::Color white =
            region == resize.region ? red : get_style()->get_white();
        const Gdk::Color bg = get_style()->get_bg(Gtk::STATE_NORMAL);

        int prevx = int(w * resize.pos / 128.0 + 0.5);
        x = int(w * k / 128.0 + 0.5);

        if (resize.mode == resize.moving_high_limit) {
            if (k > resize.pos) {
                Gdk::Cairo::set_source_color(cr, white);
                cr->rectangle(prevx, 1, x - prevx, h1 - 2);
                cr->fill();

                Gdk::Cairo::set_source_color(cr, black);
                cr->move_to(prevx, 0.5);
                cr->line_to(x + 1, 0.5);
                cr->move_to(prevx, h1 - 0.5);
                cr->line_to(x + 1, h1 - 0.5);
                cr->stroke();
            } else {
                int xx = (resize.pos == resize.max &&
                          resize.max != 128) ? 1 : 0;
                Gdk::Cairo::set_source_color(cr, bg);
                cr->rectangle(x + 1, 0, prevx - x - xx, h1);
                cr->fill();
            }
        } else {
            if (k < resize.pos) {
                Gdk::Cairo::set_source_color(cr, white);
                cr->rectangle(x + 1, 1, prevx - x, h1 - 2);
                cr->fill();

                Gdk::Cairo::set_source_color(cr, black);
                cr->move_to(x, 0.5);
                cr->line_to(prevx, 0.5);
                cr->move_to(x, h1 - 0.5);
                cr->line_to(prevx, h1 - 0.5);
                cr->stroke();
            } else {
                int xx = (resize.pos == resize.min &&
                          resize.min != 0) ? 1 : 0;
                Gdk::Cairo::set_source_color(cr, bg);
                cr->rectangle(prevx + xx, 0, x - prevx - xx, h1);
                cr->fill();
            }
        }
        Gdk::Cairo::set_source_color(cr, black);
        cr->move_to(x + 0.5, 1);
        cr->line_to(x + 0.5, h1 - 1);
        cr->stroke();
        resize.pos = k;
    }
}

void RegionChooser::motion_move_region(int x, int y)
{
    const int w = get_width() - 1;
    Cairo::RefPtr<Cairo::Context> cr = get_window()->create_cairo_context();
    cr->set_line_width(1);

    int k = int(double(x - move.from_x) / w * 128.0 + 0.5);
    if (k == move.pos) return;
    int new_k;
    bool new_touch_left;
    bool new_touch_right;
    int a = 0;
    if (k > move.pos) {
        for (gig::Region* r = regions.first() ; ; r = regions.next()) {
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
        for (gig::Region* r = regions.first() ; ; r = regions.next()) {
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

    const Gdk::Color bg = get_style()->get_bg(Gtk::STATE_NORMAL);
    int prevx = int(w * (move.pos + region->KeyRange.low) / 128.0 + 0.5);
    x = int(w * (k + region->KeyRange.low) / 128.0 + 0.5);
    int prevx2 = int(w * (move.pos + region->KeyRange.high + 1) / 128.0 + 0.5);
    int x2 = int(w * (k + region->KeyRange.high + 1) / 128.0 + 0.5);
    const Gdk::Color black = get_style()->get_black();

    if (!new_touch_left) { 
        Gdk::Cairo::set_source_color(cr, black);
        cr->move_to(x + 0.5, 1);
        cr->line_to(x + 0.5, h1 - 1);
        cr->stroke();
    }
    if (!new_touch_right) { 
        Gdk::Cairo::set_source_color(cr, black);
        cr->move_to(x2 + 0.5, 1);
        cr->line_to(x2 + 0.5, h1 - 1);
        cr->stroke();
    }

    if (k > move.pos) {
        Gdk::Cairo::set_source_color(cr, bg);
        cr->rectangle(prevx + (move.touch_left ? 1 : 0), 0,
                      std::min(x, prevx2 + 1 - (move.touch_right ? 1 : 0)) -
                      (prevx + (move.touch_left ? 1 : 0)), h1);
        cr->fill();

        Gdk::Cairo::set_source_color(cr, black);
        cr->move_to(std::max(x, prevx2 + 1), 0.5);
        cr->line_to(x2 + 1, 0.5);
        cr->move_to(std::max(x, prevx2 + 1), h1 - 0.5);
        cr->line_to(x2 + 1, h1 - 0.5);
        cr->stroke();

        Gdk::Cairo::set_source_color(cr, red);
        cr->rectangle(std::max(x + 1, prevx2), 1,
                      x2 - std::max(x + 1, prevx2), h1 - 2);
        cr->fill();
    } else {
        Gdk::Cairo::set_source_color(cr, bg);
        cr->rectangle(std::max(x2 + 1, prevx + (move.touch_left ? 1 : 0)), 0,
                      prevx2 + 1 - (move.touch_right ? 1 : 0) -
                      std::max(x2 + 1, prevx + (move.touch_left ? 1 : 0)), h1);
        cr->fill();

        Gdk::Cairo::set_source_color(cr, black);
        cr->move_to(x, 0.5);
        cr->line_to(std::min(x2, prevx - 1) + 1, 0.5);
        cr->move_to(x, h1 - 0.5);
        cr->line_to(std::min(x2, prevx - 1) + 1, h1 - 0.5);
        cr->stroke();

        Gdk::Cairo::set_source_color(cr, red);
        cr->rectangle(x + 1, 1, std::min(x2 - 1, prevx) - x, h1 - 2);
        cr->fill();
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

    // handle virtual MIDI keyboard
    if (m_VirtKeybModeChoice.get_value() != VIRT_KEYBOARD_MODE_CHORD &&
        currentActiveKey > 0 &&
        event->y >= REGION_BLOCK_HEIGHT &&
        event->y < REGION_BLOCK_HEIGHT + KEYBOARD_HEIGHT)
    {
        const int k = int(event->x / (get_width() - 1) * 128.0);
        if (k != currentActiveKey) {
            int velocity =
                (event->y >= REGION_BLOCK_HEIGHT + KEYBOARD_HEIGHT - 1) ? 127 :
                int(float(event->y - REGION_BLOCK_HEIGHT) /
                    float(KEYBOARD_HEIGHT) * 128.0f) + 1;
            if (velocity <= 0) velocity = 1;
            keyboard_key_released_signal.emit(currentActiveKey, velocity);
            currentActiveKey = k;
            keyboard_key_hit_signal.emit(k, velocity);
        }
    }

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
    const int w = get_width() - 1;

    if (instrument && y >= 0 && y <= h1) {
        gig::Region* prev_region = 0;
        gig::Region* next_region;
        for (gig::Region* r = regions.first(); r ; r = next_region) {
            next_region = regions.next();

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
                    return resize.min != resize.max;
                }

                // edit low limit
                resize.mode = resize.moving_low_limit;
                resize.min = prev_region ? prev_region->KeyRange.high + 1 : 0;
                return resize.min != resize.max;
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
                    return resize.min != resize.max;
                }
            }
            prev_region = r;
        }
    }
    return false;
}

sigc::signal<void>& RegionChooser::signal_region_selected()
{
    return region_selected;
}

sigc::signal<void>& RegionChooser::signal_instrument_changed()
{
    return instrument_changed;
}

void RegionChooser::show_region_properties()
{
    if (!region) return;
    Gtk::Dialog dialog(_("Region Properties"), true /*modal*/);
    // add "Keygroup" checkbox
    Gtk::CheckButton checkBoxKeygroup(_("Member of a Keygroup (Exclusive Group)"));
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
    instrument_struct_to_be_changed_signal.emit(instrument);

    region = instrument->AddRegion();
    region->SetKeyRange(new_region_pos, new_region_pos);

    instrument_struct_changed_signal.emit(instrument);
    regions.update(instrument);

    queue_draw();
    region_selected();
    dimensionManager.set_region(region);
    instrument_changed();
}

void RegionChooser::delete_region()
{
    instrument_struct_to_be_changed_signal.emit(instrument);
    instrument->DeleteRegion(region);
    instrument_struct_changed_signal.emit(instrument);
    regions.update(instrument);

    region = 0;
    queue_draw();
    region_selected();
    dimensionManager.set_region(region);
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

sigc::signal<void, gig::Instrument*>& RegionChooser::signal_instrument_struct_to_be_changed() {
    return instrument_struct_to_be_changed_signal;
}

sigc::signal<void, gig::Instrument*>& RegionChooser::signal_instrument_struct_changed() {
    return instrument_struct_changed_signal;
}

sigc::signal<void, gig::Region*>& RegionChooser::signal_region_to_be_changed() {
    return region_to_be_changed_signal;
}

sigc::signal<void, gig::Region*>& RegionChooser::signal_region_changed_signal() {
    return region_changed_signal;
}

sigc::signal<void, int/*key*/, int/*velocity*/>& RegionChooser::signal_keyboard_key_hit() {
    return keyboard_key_hit_signal;
}

sigc::signal<void, int/*key*/, int/*velocity*/>& RegionChooser::signal_keyboard_key_released() {
    return keyboard_key_released_signal;
}
