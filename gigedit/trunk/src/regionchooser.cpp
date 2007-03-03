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

    add_events(Gdk::BUTTON_PRESS_MASK | Gdk::POINTER_MOTION_MASK);
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
    const int h1 = 20;
    const int h = 40;
    const int w = 800 - 1;
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
//          draw_region(r->KeyRange.low, r->KeyRange.high + 1, i % 3 == 0 ? blue : i % 3 == 1 ? red : green);
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


void RegionChooser::draw_region(int from, int to, const Gdk::Color& color)
{
    const int h1 = 20;
    const int h = 40;
    const int w = 800;
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
    region = instrument->GetFirstRegion();
    queue_draw();
    sel_changed_signal.emit();
}

void RegionChooser::set_region(gig::Region* region)
{
    this->region = region;
    queue_draw();
}

bool RegionChooser::on_button_press_event(GdkEventButton* event)
{
    const int w = 800 - 1;

    if (instrument) {
        int i = 0;
        for (gig::Region *r = instrument->GetFirstRegion() ;
             r ;
             r = instrument->GetNextRegion()) {
            int x = int(w * (r->KeyRange.low) / 128.0 + 0.5);
            int x2 = int(w * (r->KeyRange.high + 1) / 128.0 + 0.5);
            if (event->x >= x && event->x < x2) {
                region = r;
                break;
            }
            i++;
        }
        queue_draw();
        sel_changed_signal.emit();
    }
}

// muspekarexperiment. Fel eventhantering - se example_drawingarea.cc
bool inside = false;
bool RegionChooser::on_motion_notify_event(GdkEventMotion* event)
{
    if (event->x > 100 && event->x < 120) {
        if (!inside) {
            Gdk::Cursor oj(Gdk::CROSSHAIR);
            get_window()->set_cursor(oj);
            inside = true;
        }
    } else if (inside) {
        get_window()->set_cursor();
        inside = false;
    }
}

sigc::signal<void> RegionChooser::signal_sel_changed()
{
    return sel_changed_signal;
}
