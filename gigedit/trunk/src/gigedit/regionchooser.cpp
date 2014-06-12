/*
 * Copyright (C) 2006-2014 Andreas Persson
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

#include <cairomm/context.h>
#include <gdkmm/general.h>
#include <gdkmm/cursor.h>
#include <gtkmm/stock.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/dialog.h>

#include "global.h"

#define REGION_BLOCK_HEIGHT             30
#define KEYBOARD_HEIGHT                 40

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
    activeKeyColor("red"),
    red("#8070ff"),
    grey1("grey69"),
    white("white"),
    black("black"),
    m_VirtKeybModeChoice(_("Virtual Keyboard Mode")),
    currentActiveKey(-1)
{
    set_size_request(500, KEYBOARD_HEIGHT + REGION_BLOCK_HEIGHT);

    instrument = 0;
    region = 0;
    resize.active = false;
    move.active = false;
    cursor_is_resize = false;
    h1 = REGION_BLOCK_HEIGHT;

    // properties of the virtual keyboard
    {
        const char* choices[] = { _("normal"), _("chord"), 0 };
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
    for (int i = 0 ; i < 128 ; i++) key_pressed[i] = false;

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
    set_tooltip_text(_("Right click here for adding new region. Use mouse pointer for moving (dragging) or resizing existing regions (by pointing at region's boundary). Right click on an existing region for more actions."));
}

RegionChooser::~RegionChooser()
{
}

void RegionChooser::invalidate_key(int key) {
    const int h = KEYBOARD_HEIGHT;
    const int w = get_width() - 1;
    int x1 = key_to_x(key - 0.5, w);
    int x2 = key_to_x(key + 1.5, w);

    Gdk::Rectangle rect(x1 + 1, h1 + 1, x2 - x1 - 1, h - 2);
    get_window()->invalidate_rect(rect, false);
}

void RegionChooser::on_note_on_event(int key, int velocity) {
    key_pressed[key] = true;
    invalidate_key(key);
    m_VirtKeybVelocityLabel.set_text(ToString(velocity));
}

void RegionChooser::on_note_off_event(int key, int velocity) {
    key_pressed[key] = false;
    invalidate_key(key);
    m_VirtKeybOffVelocityLabel.set_text(ToString(velocity));
}


#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
bool RegionChooser::on_expose_event(GdkEventExpose* e) {
    double clipx1 = e->area.x;
    double clipx2 = e->area.x + e->area.width;
    double clipy1 = e->area.y;
    double clipy2 = e->area.y + e->area.height;

    const Cairo::RefPtr<Cairo::Context>& cr =
        get_window()->create_cairo_context();
#if 0
}
#endif
#else
bool RegionChooser::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    double clipx1, clipx2, clipy1, clipy2;
    cr->get_clip_extents(clipx1, clipy1, clipx2, clipy2);
#endif

    cr->save();
    cr->set_line_width(1);

#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
    const Gdk::Color bg = get_style()->get_bg(Gtk::STATE_NORMAL);
#else
    const Gdk::RGBA bg = get_style_context()->get_background_color();
#endif
    Gdk::Cairo::set_source_rgba(cr, bg);
    cr->paint();

    if (clipy2 > h1) {
        draw_keyboard(cr, clipx1, clipx2);
    }

    if (clipy1 < h1 && instrument) {
        draw_regions(cr, clipx1, clipx2);
    }

    cr->restore();

    return true;
}

void RegionChooser::draw_keyboard(const Cairo::RefPtr<Cairo::Context>& cr,
                                  int clip_low, int clip_high) {
    const int h = KEYBOARD_HEIGHT;
    const int w = get_width() - 1;
    const int bh = int(h * 0.55);

    Gdk::Cairo::set_source_rgba(cr, black);
    cr->rectangle(0.5, h1 + 0.5, w, h - 1);
    cr->stroke();

    int x1 = key_to_x(20.5, w);
    Gdk::Cairo::set_source_rgba(cr, grey1);
    cr->rectangle(1, h1 + 1, x1 - 1, h - 2);
    cr->fill();

    int x2 = key_to_x(109.5, w);
    Gdk::Cairo::set_source_rgba(cr, white);
    cr->rectangle(x1 + 1, h1 + 1, x2 - x1 - 1, h - 2);
    cr->fill();

    Gdk::Cairo::set_source_rgba(cr, grey1);
    cr->rectangle(x2 + 1, h1 + 1, w - x2 - 1, h - 2);
    cr->fill();

    Gdk::Cairo::set_source_rgba(cr, black);

    int clipkey1 = std::max(0, x_to_key_right(clip_low - 1, w));
    int clipkey2 = std::min(x_to_key_right(clip_high - 1, w) + 1, 128);

    for (int i = clipkey1 ; i < clipkey2 ; i++) {
        int note = (i + 3) % 12;
        int x = key_to_x(i, w);

        if (note == 1 || note == 4 || note == 6 ||
            note == 9 || note == 11) {
            // black key: short line in the middle, with a rectangle
            // on top
            int x2 = key_to_x(i + 0.5, w);
            cr->move_to(x2 + 0.5, h1 + bh + 0.5);
            cr->line_to(x2 + 0.5, h1 + h - 1);
            cr->stroke();

            int x3 = key_to_x(i + 1, w);
            cr->rectangle(x, h1 + 1, x3 - x + 1, bh);
            cr->fill();
        } else if (note == 3 || note == 8) {
            // C or F: long line to the left
            cr->move_to(x + 0.5, h1 + 1);
            cr->line_to(x + 0.5, h1 + h - 1);
            cr->stroke();
        }

        if (key_pressed[i]) draw_key(cr, i);

        if (note == 3) draw_digit(cr, i);
    }
}


void RegionChooser::draw_regions(const Cairo::RefPtr<Cairo::Context>& cr,
                                 int clip_low, int clip_high) {
    const int w = get_width() - 1;

    Gdk::Cairo::set_source_rgba(cr, black);
    gig::Region* next_region;
    int x3 = -1;
    for (gig::Region* r = regions.first() ; r ; r = next_region) {
        next_region = regions.next();

        if (x3 < 0) {
            x3 = key_to_x(r->KeyRange.low, w);
            if (x3 >= clip_high) break;
        }
        if (!next_region ||
            r->KeyRange.high + 1 != next_region->KeyRange.low ||
            r == region || next_region == region) {

            int x2 = key_to_x(r->KeyRange.high + 1, w);
            if (x2 >= clip_low) {
                cr->move_to(x3, 0.5);
                cr->line_to(x2 + 0.5, 0.5);
                cr->line_to(x2 + 0.5, h1 - 0.5);
                cr->line_to(x3, h1 - 0.5);
                cr->stroke();

                Gdk::Cairo::set_source_rgba(cr, region == r ? red : white);
                cr->rectangle(x3 + 1, 1, x2 - x3 - 1, h1 - 2);
                cr->fill();
                Gdk::Cairo::set_source_rgba(cr, black);
            }
            x3 = -1;
        }
    }

    for (gig::Region* r = regions.first() ; r ; r = regions.next()) {
        int x = key_to_x(r->KeyRange.low, w);

        if (x < clip_low) continue;
        if (x >= clip_high) break;

        cr->move_to(x + 0.5, 1);
        cr->line_to(x + 0.5, h1 - 1);
        cr->stroke();
    }

    // if there is no region yet, show the user some hint text that he may
    // right click on this area to create a new region
    if (!regions.first()) {
        Glib::RefPtr<Pango::Context> context = get_pango_context();
        Glib::RefPtr<Pango::Layout> layout = Pango::Layout::create(context);
        layout->set_alignment(Pango::ALIGN_CENTER);
        layout->set_text(Glib::ustring("*** ") + _("Right click here to create a region.") + " ***");
        layout->set_width(get_width() * Pango::SCALE);
        //layout->set_height(get_height() * Pango::SCALE);
        layout->set_spacing(10);
        Gdk::Cairo::set_source_rgba(cr, red);        
        // get the text dimensions
        Pango::Rectangle rect = layout->get_logical_extents();
        int text_width, text_height;
        layout->get_pixel_size(text_width, text_height);
        cr->move_to(0, (REGION_BLOCK_HEIGHT - text_height) / 2);
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 16) || GTKMM_MAJOR_VERSION < 2
        pango_cairo_show_layout(cr->cobj(), layout->gobj());
#else
        layout->show_in_cairo_context(cr);
#endif
    }
}

bool RegionChooser::is_black_key(int key) {
    const int note = (key + 3) % 12;
    return note == 1 || note == 4 || note == 6 || note == 9 || note == 11;
}

void RegionChooser::draw_digit(const Cairo::RefPtr<Cairo::Context>& cr,
                               int key) {
    const int h = KEYBOARD_HEIGHT;
    const int w = get_width() - 1;
    Glib::RefPtr<Pango::Layout> layout =
        Pango::Layout::create(get_pango_context());
    char buf[30];
    sprintf(buf, "<span size=\"8000\">%d</span>", key / 12 - 1);
    layout->set_markup(buf);
    Pango::Rectangle rectangle = layout->get_logical_extents();
    double text_w = double(rectangle.get_width()) / Pango::SCALE;
    double text_h = double(rectangle.get_height()) / Pango::SCALE;
    double x = w * (key + 0.75) / 128.0;
    Gdk::Cairo::set_source_rgba(cr, black);
    cr->move_to(int(x - text_w / 2 + 1), int(h1 + h - text_h + 0.5));
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 16) || GTKMM_MAJOR_VERSION < 2
    pango_cairo_show_layout(cr->cobj(), layout->gobj());
#else
    layout->show_in_cairo_context(cr);
#endif
}

void RegionChooser::draw_key(const Cairo::RefPtr<Cairo::Context>& cr,
                             int key) {
    const int h = KEYBOARD_HEIGHT;
    const int w = get_width() - 1;
    const int bh = int(h * 0.55);

    Gdk::Cairo::set_source_rgba(cr, activeKeyColor);

    int note = (key + 3) % 12;
    int x = key_to_x(key, w) + 1;
    int x2 = key_to_x(key + 1.5, w);
    int x3 = key_to_x(key + 1, w);
    int x4 = key_to_x(key - 0.5, w);
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
        break;
    default:
        cr->rectangle(x, h1 + 1, w1, bh - 1);
        cr->fill();
        break;
    }
    Gdk::Cairo::set_source_rgba(cr, black);
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
    const int k = x_to_key(event->x, get_width() - 1);

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
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
        get_window()->pointer_ungrab(event->time);
#else
        Glib::wrap(event->device, true)->ungrab(event->time);
#endif
        resize.active = false;

        if (!is_in_resize_zone(event->x, event->y) && cursor_is_resize) {
            get_window()->set_cursor();
            cursor_is_resize = false;
        }
    } else if (move.active) {
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
        get_window()->pointer_ungrab(event->time);
#else
        Glib::wrap(event->device, true)->ungrab(event->time);
#endif
        move.active = false;

        if (is_in_resize_zone(event->x, event->y)) {
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
            get_window()->set_cursor(Gdk::Cursor(Gdk::SB_H_DOUBLE_ARROW));
#else
            get_window()->set_cursor(Gdk::Cursor::create(Gdk::SB_H_DOUBLE_ARROW));
#endif
            cursor_is_resize = true;
        }
    }
    return true;
}

void RegionChooser::update_after_resize()
{
    if (resize.mode == resize.moving_high_limit) {
        if (resize.region->KeyRange.high != resize.pos - 1) {
            instrument_struct_to_be_changed_signal.emit(instrument);
            resize.region->SetKeyRange(resize.region->KeyRange.low,
                                       resize.pos - 1);
            regions.update(instrument);
            instrument_changed.emit();
            instrument_struct_changed_signal.emit(instrument);
        }
    } else if (resize.mode == resize.moving_low_limit) {
        if (resize.region->KeyRange.low != resize.pos) {
            instrument_struct_to_be_changed_signal.emit(instrument);
            resize.region->SetKeyRange(resize.pos,
                                       resize.region->KeyRange.high);
            regions.update(instrument);
            instrument_changed.emit();
            instrument_struct_changed_signal.emit(instrument);
        }
    }
}

void RegionChooser::update_after_move(int pos)
{
    instrument_struct_to_be_changed_signal.emit(instrument);
    region->SetKeyRange(pos, pos + region->KeyRange.high -
                        region->KeyRange.low);
    regions.update(instrument);
    instrument_changed.emit();
    instrument_struct_changed_signal.emit(instrument);
}

bool RegionChooser::on_button_press_event(GdkEventButton* event)
{
    if (!instrument) return true;

    const int w = get_width() - 1;
    const int k = x_to_key(event->x, w);

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
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
            get_window()->pointer_grab(false,
                                       Gdk::BUTTON_RELEASE_MASK |
                                       Gdk::POINTER_MOTION_MASK |
                                       Gdk::POINTER_MOTION_HINT_MASK,
                                       Gdk::Cursor(Gdk::SB_H_DOUBLE_ARROW),
                                       event->time);
#else
            Glib::wrap(event->device, true)->grab(get_window(),
                                                  Gdk::OWNERSHIP_NONE,
                                                  false,
                                                  Gdk::BUTTON_RELEASE_MASK |
                                                  Gdk::POINTER_MOTION_MASK |
                                                  Gdk::POINTER_MOTION_HINT_MASK,
                                                  Gdk::Cursor::create(Gdk::SB_H_DOUBLE_ARROW),
                                                  event->time);
#endif
            resize.active = true;
        } else {
            gig::Region* r = get_region(k);
            if (r) {
                region = r;
                queue_draw();
                region_selected();
                dimensionManager.set_region(region);

#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
                get_window()->pointer_grab(false,
                                           Gdk::BUTTON_RELEASE_MASK |
                                           Gdk::POINTER_MOTION_MASK |
                                           Gdk::POINTER_MOTION_HINT_MASK,
                                           Gdk::Cursor(Gdk::FLEUR),
                                           event->time);
#else
                Glib::wrap(event->device, true)->grab(get_window(),
                                                      Gdk::OWNERSHIP_NONE,
                                                      false,
                                                      Gdk::BUTTON_RELEASE_MASK |
                                                      Gdk::POINTER_MOTION_MASK |
                                                      Gdk::POINTER_MOTION_HINT_MASK,
                                                      Gdk::Cursor::create(Gdk::FLEUR),
                                                      event->time);
#endif
                move.active = true;
                move.offset = event->x - key_to_x(region->KeyRange.low, w);
            }
        }
    }
    return true;
}

gig::Region* RegionChooser::get_region(int key)
{
    for (gig::Region* r = regions.first() ; r ; r = regions.next()) {
        if (key < r->KeyRange.low) return 0;
        if (key <= r->KeyRange.high) return r;
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
        resize.pos = k;

        int x1, x2;
        if (resize.mode == resize.moving_high_limit) {
            if (resize.region->KeyRange.high < resize.pos - 1) {
                x1 = resize.region->KeyRange.high;
                x2 = resize.pos - 1;
            } else {
                x1 = resize.pos - 1;
                x2 = resize.region->KeyRange.high;
            }
        } else {
            if (resize.region->KeyRange.low < resize.pos) {
                x1 = resize.region->KeyRange.low;
                x2 = resize.pos;
            } else {
                x1 = resize.pos;
                x2 = resize.region->KeyRange.low;
            }
        }
        x1 = key_to_x(x1, w);
        x2 = key_to_x(x2 + 1, w) + 1;
        Gdk::Rectangle rect(x1, 0, x2 - x1, h1);

        update_after_resize();

        get_window()->invalidate_rect(rect, false);
    }
}

void RegionChooser::motion_move_region(int x, int y)
{
    const int w = get_width() - 1;

    int l = int(double(x - move.offset) / w * 128.0 + 0.5);

    if (l == region->KeyRange.low) return;
    int new_l;
    int regionsize = region->KeyRange.high - region->KeyRange.low;
    int a = 0;
    if (l > region->KeyRange.low) {
        for (gig::Region* r = regions.first() ; ; r = regions.next()) {
            if (r != region) {
                int b = r ? r->KeyRange.low : 128;

                // gap: from a to b (not inclusive b)

                if (region->KeyRange.high >= b) {
                    // not found the current gap yet, just continue
                } else {

                    if (a > l) {
                        // this gap is too far to the right, break
                        break;
                    }

                    int newhigh = std::min(l + regionsize, b - 1);
                    int newlo = newhigh - regionsize;

                    if (newlo >= a) {
                        // yes it fits - it's a candidate
                        new_l = newlo;
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

                if (l + regionsize >= b) {
                    // not found the current gap yet, just continue
                } else {

                    if (a > region->KeyRange.low) {
                        // this gap is too far to the right, break
                        break;
                    }

                    int newlo = std::max(l, a);
                    int newhigh = newlo + regionsize;

                    if (newhigh < b) {
                        // yes it fits - break as the first one is the best
                        new_l = newlo;
                        break;
                    }
                }
                if (!r) break;
                a = r->KeyRange.high + 1;
            }
        }
    }
    if (new_l == region->KeyRange.low) return;

    int x1 = key_to_x(std::min(int(region->KeyRange.low), new_l), w);
    int x2 = key_to_x(std::max(int(region->KeyRange.high),
                               new_l + regionsize) + 1, w) + 1;

    Gdk::Rectangle rect(x1, 0, x2 - x1, h1);
    update_after_move(new_l);

    get_window()->invalidate_rect(rect, false);
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
        const int k = x_to_key(event->x, get_width() - 1);
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
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
                window->set_cursor(Gdk::Cursor(Gdk::SB_H_DOUBLE_ARROW));
#else
                window->set_cursor(Gdk::Cursor::create(Gdk::SB_H_DOUBLE_ARROW));
#endif
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

            int lo = key_to_x(r->KeyRange.low, w);
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
                int hi = key_to_x(r->KeyRange.high + 1, w);
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
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
    Gtk::Adjustment adjustment(1, 1, 999);
    Gtk::SpinButton spinBox(adjustment);
#else
    Gtk::SpinButton spinBox(Gtk::Adjustment::create(1, 1, 999));
#endif
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
