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

#include "dimregionchooser.h"

DimRegionChooser::DimRegionChooser()
{
    // get_window() would return 0 because the Gdk::Window has not yet been realized
    // So we can only allocate the colors here - the rest will happen in on_realize().
    Glib::RefPtr<Gdk::Colormap> colormap = get_default_colormap();

    black = Gdk::Color("black");
    white = Gdk::Color("white");
    red = Gdk::Color("#8070ff");
    blue = Gdk::Color("blue");
    green = Gdk::Color("green");

    colormap->alloc_color(black);
    colormap->alloc_color(white);
    colormap->alloc_color(red);
    colormap->alloc_color(blue);
    colormap->alloc_color(green);
    instrument = 0;
    region = 0;
    dimregno = -1;
    focus_line = 0;
    set_flags(Gtk::CAN_FOCUS);
    add_events(Gdk::BUTTON_PRESS_MASK);

    for (int i = 0 ; i < 256 ; i++) {
        dimvalue_from[i] = 0;
        dimvalue_to[i] = 1;
    }
}

DimRegionChooser::~DimRegionChooser()
{
}

void DimRegionChooser::on_realize()
{
    // We need to call the base on_realize()
    Gtk::DrawingArea::on_realize();

    // Now we can allocate any additional resources we need
    Glib::RefPtr<Gdk::Window> window = get_window();
    gc = Gdk::GC::create(window);
}

bool DimRegionChooser::on_expose_event(GdkEventExpose* event)
{
    if (!region) return true;

    int a = 1, b, c;
    for (int i = 0 ; i < region->Dimensions ; i++) {
        b = a * region->pDimensionDefinitions[i].zones;
        if (region->pDimensionDefinitions[i].dimension == gig::dimension_velocity) {
            c = dimregno >= 0 ? (dimregno & ((a - 1) | ~(b - 1))) : 0;
            break;
        }
        a = b;
    }

    // This is where we draw on the window
    Glib::RefPtr<Gdk::Window> window = get_window();
    Glib::RefPtr<Pango::Context> context = get_pango_context();

    Glib::RefPtr<Pango::Layout> layout = Pango::Layout::create(context);

    window->clear();
    const int h = 20;
    const int w = 800;
    const int w1 = 100;
    int y = 0;
    int bitcount = 0;
    for (int i = 0 ; i < region->Dimensions ; i++) {
        const int nb = region->pDimensionDefinitions[i].zones;
        if (nb) {
            char* dstr;
            switch (region->pDimensionDefinitions[i].dimension) {
            case gig::dimension_none: dstr="none"; break;
            case gig::dimension_samplechannel: dstr="samplechannel"; break;
            case gig::dimension_layer: dstr="layer"; break;
            case gig::dimension_velocity: dstr="velocity"; break;
            case gig::dimension_channelaftertouch: dstr="channelaftertouch"; break;
            case gig::dimension_releasetrigger: dstr="releasetrigger"; break;
            case gig::dimension_keyboard: dstr="keyboard"; break;
            case gig::dimension_roundrobin: dstr="roundrobin"; break;
            case gig::dimension_random: dstr="random"; break;
            case gig::dimension_modwheel: dstr="modwheel"; break;
            case gig::dimension_breath: dstr="breath"; break;
            case gig::dimension_foot: dstr="foot"; break;
            case gig::dimension_portamentotime: dstr="portamentotime"; break;
            case gig::dimension_effect1: dstr="effect1"; break;
            case gig::dimension_effect2: dstr="effect2"; break;
            case gig::dimension_genpurpose1: dstr="genpurpose1"; break;
            case gig::dimension_genpurpose2: dstr="genpurpose2"; break;
            case gig::dimension_genpurpose3: dstr="genpurpose3"; break;
            case gig::dimension_genpurpose4: dstr="genpurpose4"; break;
            case gig::dimension_sustainpedal: dstr="sustainpedal"; break;
            case gig::dimension_portamento: dstr="portamento"; break;
            case gig::dimension_sostenutopedal: dstr="sostenutopedal"; break;
            case gig::dimension_softpedal: dstr="softpedal"; break;
            case gig::dimension_genpurpose5: dstr="genpurpose5"; break;
            case gig::dimension_genpurpose6: dstr="genpurpose6"; break;
            case gig::dimension_genpurpose7: dstr="genpurpose7"; break;
            case gig::dimension_genpurpose8: dstr="genpurpose8"; break;
            case gig::dimension_effect1depth: dstr="effect1depth"; break;
            case gig::dimension_effect2depth: dstr="effect2depth"; break;
            case gig::dimension_effect3depth: dstr="effect3depth"; break;
            case gig::dimension_effect4depth: dstr="effect4depth"; break;
            case gig::dimension_effect5depth: dstr="effect5depth"; break;
            }
            layout->set_text(dstr);

	    Pango::Rectangle rectangle = layout->get_logical_extents();
	    double text_h = double(rectangle.get_height()) / Pango::SCALE;
            Glib::RefPtr<const Gdk::GC> fg = get_style()->get_fg_gc(get_state());
            window->draw_layout(fg, 4, int(y + (h - text_h) / 2 + 0.5), layout);

            if (has_focus() && focus_line == i) {
                Gdk::Rectangle farea(0, y, 50, 20);
                get_style()->paint_focus(window, get_state(), farea, *this, "hejsan", 0, y, 50, 20);
            }

            Glib::RefPtr<const Gdk::GC> black = get_style()->get_black_gc();
            window->draw_line(black, w1, y, w - 1, y);
            window->draw_line(black, w - 1, y + h - 1, w1, y + h - 1);
            window->draw_rectangle(get_style()->get_white_gc(), true, w1 + 1, y + 1, (w - w1 - 2), h - 2);

            if (region->pDimensionDefinitions[i].dimension == gig::dimension_velocity &&
                region->pDimensionRegions[c]->VelocityUpperLimit) {
                window->draw_line(black, w1, y + 1, w1, y + h - 2);
                for (int k = c ; k < b ; k += a) {
                    gig::DimensionRegion *d = region->pDimensionRegions[k];
                    int v = d->VelocityUpperLimit + 1;
                    int x = int((w - w1 - 1) * v / 128.0 + 0.5);
                    window->draw_line(black, w1 + x, y + 1, w1 + x, y + h - 2);
                }
            } else {
                for (int j = 0 ; j <= nb ; j++) {
                    int x = int((w - w1 - 1) * j / double(nb) + 0.5);
                    window->draw_line(black, w1 + x, y + 1, w1 + x, y + h - 2);
                }
            }

            if (dimregno >= 0) {
                gc->set_foreground(red);
                int dr = (dimregno >> bitcount) & ((1 << region->pDimensionDefinitions[i].bits) - 1);
                if (region->pDimensionDefinitions[i].dimension == gig::dimension_velocity &&
                    region->pDimensionRegions[c]->VelocityUpperLimit) {
                    int x1 = 0, dr2 = 0;
                    for (int k = c ; k < b ; k += a) {
                        gig::DimensionRegion *d = region->pDimensionRegions[k];
                        int v = d->VelocityUpperLimit + 1;
                        int x2 = int((w - w1 - 1) * v / 128.0 + 0.5);
                        if (dr2 == dr) {
                            window->draw_rectangle(gc, true, w1 + x1 + 1, y + 1, (x2 - x1) - 1, h - 2);
                            break;
                        }
                        dr2++;
                        x1 = x2;
                    }
                } else {
                    if (dr < nb) {
                        int x1 = int((w - w1 - 1) * dr / double(nb) + 0.5);
                        int x2 = int((w - w1 - 1) * (dr + 1) / double(nb) + 0.5);
                        window->draw_rectangle(gc, true, w1 + x1 + 1, y + 1, (x2 - x1) - 1, h - 2);
                    }
                }
            }

            y += h;
        }
        bitcount += region->pDimensionDefinitions[i].bits;
    }

    return true;
}


void DimRegionChooser::on_size_request(GtkRequisition* requisition)
{
    printf("DimRegionChooser::on_size_request\n");
    *requisition = GtkRequisition();
    requisition->height = region ? region->Dimensions * 20 : 0;
    requisition->width = 800;
}

void DimRegionChooser::set_instrument(gig::Instrument* instrument)
{
    this->instrument = instrument;
    this->region = 0;
    this->dimregno = -1;
    queue_draw();
}

void DimRegionChooser::set_region(gig::Region* region)
{
    this->region = region;
    dimregno = 0;
    int bitcount = 0;
    for (int dim = 0 ; dim < region->Dimensions ; dim++) {
        int from = dimvalue_from[region->pDimensionDefinitions[dim].dimension];
        int to = dimvalue_to[region->pDimensionDefinitions[dim].dimension];
        int z;
        switch (region->pDimensionDefinitions[dim].split_type) {
        case gig::split_type_normal:
            z = int((to + from) / 2.0 / region->pDimensionDefinitions[dim].zone_size);
            break;
        case gig::split_type_bit:
            z = std::min(from, region->pDimensionDefinitions[dim].zones - 1);
            break;
        }
        int mask =
            ~(((1 << region->pDimensionDefinitions[dim].bits) - 1) <<
              bitcount);
        dimregno &= mask;
        dimregno |= (z << bitcount);
        bitcount += region->pDimensionDefinitions[dim].bits;
    }
    dimreg = region->pDimensionRegions[dimregno];
    sel_changed_signal.emit();
    queue_resize();
}

/*
  void DimRegionChooser::set_dimregno(int x) {
  this->dimregno = x;
  queue_draw();
  }
*/

bool DimRegionChooser::on_button_press_event(GdkEventButton* event)
{
    const int h = 20;
    const int w = 800;
    const int w1 = 100;

    if (region) {
        if (event->y < region->Dimensions * h &&
            event->x >= w1 && event->x < w) {

            int dim = int(event->y / h);
            const int nb = region->pDimensionDefinitions[dim].zones;

            int z = -1;
            if (region->pDimensionDefinitions[dim].dimension == gig::dimension_velocity) {
                int a = 1, b, c;
                for (int i = 0 ; i < region->Dimensions ; i++) {
                    b = a * region->pDimensionDefinitions[i].zones;
                    if (region->pDimensionDefinitions[i].dimension == gig::dimension_velocity) {
                        c = dimregno >= 0 ? (dimregno & ((a - 1) | ~(b - 1))) : 0;
                        break;
                    }
                    a = b;
                }

                if (region->pDimensionRegions[c]->VelocityUpperLimit) {
                    int vel = int((event->x - w1) * 128 / (w - w1 - 1));

                    z = 0;
                    for (int k = c ; k < b ; k += a) {
                        gig::DimensionRegion *d = region->pDimensionRegions[k];
                        if (vel <= d->VelocityUpperLimit) break;
                        z++;
                    }
                }
            }

            if (z == -1) {
                z = int((event->x - w1) * nb / (w - w1 - 1));
            }

            printf("dim=%d z=%d dimensionsource=%d split_type=%d zones=%d zone_size=%f\n", dim, z,
                   region->pDimensionDefinitions[dim].dimension,
                   region->pDimensionDefinitions[dim].split_type,
                   region->pDimensionDefinitions[dim].zones,
                   region->pDimensionDefinitions[dim].zone_size);
            switch (region->pDimensionDefinitions[dim].split_type) {
            case gig::split_type_normal:
                dimvalue_from[region->pDimensionDefinitions[dim].dimension] =
                    int(z * region->pDimensionDefinitions[dim].zone_size);
                dimvalue_to[region->pDimensionDefinitions[dim].dimension] =
                    int((z + 1) * region->pDimensionDefinitions[dim].zone_size) - 1;
                break;
            case gig::split_type_bit:
                dimvalue_from[region->pDimensionDefinitions[dim].dimension] = z;
                dimvalue_to[region->pDimensionDefinitions[dim].dimension] = z + 1;
                break;
            }
            if (dimregno < 0) dimregno = 0;
            int bitcount = 0;
            for (int i = 0 ; i < dim ; i++) {
                bitcount += region->pDimensionDefinitions[i].bits;
            }

            int mask =
                ~(((1 << region->pDimensionDefinitions[dim].bits) - 1) <<
                  bitcount);
            dimregno &= mask;
            dimregno |= (z << bitcount);

            focus_line = dim;
            if (has_focus()) queue_draw();
            else grab_focus();
            dimreg = region->pDimensionRegions[dimregno];
            sel_changed_signal.emit();
        }
    }
    return true;
}

sigc::signal<void> DimRegionChooser::signal_sel_changed()
{
    return sel_changed_signal;
}

bool DimRegionChooser::on_focus(Gtk::DirectionType direction)
{
    // TODO: kolla att region finns osv, dvs att det går att sätta
    // fokus.
    if (direction == Gtk::DIR_TAB_FORWARD ||
        direction == Gtk::DIR_DOWN) {
        if (!has_focus()) {
            focus_line = 0;
            grab_focus();
            return true;
        } else {
            if (focus_line + 1 < region->Dimensions) {
                focus_line++;
                queue_draw();
                return true;
            } else {
                return false;
            }
        }
    } else if (direction == Gtk::DIR_TAB_BACKWARD ||
               direction == Gtk::DIR_UP) {
        if (!has_focus()) {
            focus_line = region->Dimensions - 1;
            grab_focus();
            return true;
        } else {
            if (focus_line > 0) {
                focus_line--;
                queue_draw();
                return true;
            } else {
                return false;
            }
        }
    } else if (!has_focus()) {
        // TODO: kolla att focus_line finns!
        grab_focus();
        return true;
    } else {
        // TODO: öka eller minska värde!
    }
}
