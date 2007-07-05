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
#include <gdkmm/cursor.h>

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
    resize.active = false;
    cursor_is_resize = false;
    h = 20;
    w = 800;
    set_flags(Gtk::CAN_FOCUS);
    add_events(Gdk::BUTTON_PRESS_MASK | Gdk::POINTER_MOTION_MASK |
               Gdk::POINTER_MOTION_HINT_MASK);

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

    // This is where we draw on the window
    Glib::RefPtr<Gdk::Window> window = get_window();
    Glib::RefPtr<Pango::Context> context = get_pango_context();

    Glib::RefPtr<Pango::Layout> layout = Pango::Layout::create(context);

    window->clear();

    // draw labels on the left (reflecting the dimension type)
    int y = 0;
    double maxwidth = 0;
    for (int i = 0 ; i < region->Dimensions ; i++) {
        int nbZones = region->pDimensionDefinitions[i].zones;
        if (nbZones) {
            const char* dstr;
            char dstrbuf[10];
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
            case gig::dimension_smartmidi: dstr="smartmidi"; break;
            case gig::dimension_roundrobinkeyboard: dstr="roundrobinkeyboard"; break;
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
            default:
                sprintf(dstrbuf, "%d",
                        region->pDimensionDefinitions[i].dimension);
                dstr = dstrbuf;
                break;
            }
            layout->set_text(dstr);

            Pango::Rectangle rectangle = layout->get_logical_extents();
            double text_w = double(rectangle.get_width()) / Pango::SCALE;
            if (text_w > maxwidth) maxwidth = text_w;
            double text_h = double(rectangle.get_height()) / Pango::SCALE;
            Glib::RefPtr<const Gdk::GC> fg = get_style()->get_fg_gc(get_state());
            window->draw_layout(fg, 4, int(y + (h - text_h) / 2 + 0.5), layout);

        }
        y += h;
    }

    // draw dimensions' zones areas
    y = 0;
    int bitpos = 0;
    label_width = int(maxwidth + 10);
    for (int i = 0 ; i < region->Dimensions ; i++) {
        int nbZones = region->pDimensionDefinitions[i].zones;
        if (nbZones) {
            // draw focus rectangle around dimension's label and zones
            if (has_focus() && focus_line == i) {
                Gdk::Rectangle farea(0, y, 150, 20);
                get_style()->paint_focus(window, get_state(), farea, *this, "",
                                         0, y, label_width, 20);
            }

            Glib::RefPtr<const Gdk::GC> black = get_style()->get_black_gc();
            // draw top and bottom lines of dimension's zones
            window->draw_line(black, label_width, y, w - 1, y);
            window->draw_line(black, w - 1, y + h - 1, label_width, y + h - 1);
            // erase whole dimension's zones area
            window->draw_rectangle(get_style()->get_white_gc(), true,
                                   label_width + 1, y + 1, (w - label_width - 2), h - 2);

            int c = 0;
            if (dimregno >= 0) {
                int mask = ~(((1 << region->pDimensionDefinitions[i].bits) - 1) << bitpos);
                c = dimregno & mask; // mask away this dimension
            }
            bool customsplits =
                ((region->pDimensionDefinitions[i].split_type == gig::split_type_normal &&
                 region->pDimensionRegions[c]->DimensionUpperLimits[i]) ||
                (region->pDimensionDefinitions[i].dimension == gig::dimension_velocity &&
                 region->pDimensionRegions[c]->VelocityUpperLimit));

            // draw dimension's zone borders
            if (customsplits) {
                window->draw_line(black, label_width, y + 1, label_width, y + h - 2);
                for (int j = 0 ; j < nbZones ; j++) {
                    gig::DimensionRegion *d = region->pDimensionRegions[c + (j << bitpos)];
                    int upperLimit = d->DimensionUpperLimits[i];
                    if (!upperLimit) upperLimit = d->VelocityUpperLimit;
                    int v = upperLimit + 1;
                    int x = int((w - label_width - 1) * v / 128.0 + 0.5);
                    window->draw_line(black, label_width + x, y + 1, label_width + x, y + h - 2);
                }
            } else {
                for (int j = 0 ; j <= nbZones ; j++) {
                    int x = int((w - label_width - 1) * j / double(nbZones) + 0.5);
                    window->draw_line(black, label_width + x, y + 1, label_width + x, y + h - 2);
                }
            }

            // draw fill for currently selected zone
            if (dimregno >= 0) {
                gc->set_foreground(red);
                int dr = (dimregno >> bitpos) & ((1 << region->pDimensionDefinitions[i].bits) - 1);
                if (customsplits) {
                    int x1 = 0;
                    for (int j = 0 ; j < nbZones ; j++) {
                        gig::DimensionRegion *d = region->pDimensionRegions[c + (j << bitpos)];
                        int upperLimit = d->DimensionUpperLimits[i];
                        if (!upperLimit) upperLimit = d->VelocityUpperLimit;
                        int v = upperLimit + 1;
                        int x2 = int((w - label_width - 1) * v / 128.0 + 0.5);
                        if (j == dr && x1 < x2) {
                            window->draw_rectangle(gc, true, label_width + x1 + 1, y + 1,
                                                   (x2 - x1) - 1, h - 2);
                            break;
                        }
                        x1 = x2;
                    }
                } else {
                    if (dr < nbZones) {
                        int x1 = int((w - label_width - 1) * dr / double(nbZones) + 0.5);
                        int x2 = int((w - label_width - 1) * (dr + 1) / double(nbZones) + 0.5);
                        window->draw_rectangle(gc, true, label_width + x1 + 1, y + 1,
                                               (x2 - x1) - 1, h - 2);
                    }
                }
            }

            y += h;
        }
        bitpos += region->pDimensionDefinitions[i].bits;
    }

    return true;
}

void DimRegionChooser::on_size_request(GtkRequisition* requisition)
{
    printf("DimRegionChooser::on_size_request\n");
    *requisition = GtkRequisition();
    requisition->height = region ? nbDimensions * 20 : 0;
    requisition->width = 800;
}

void DimRegionChooser::set_region(gig::Region* region)
{
    this->region = region;
    dimregno = 0;
    nbDimensions = 0;
    if (region) {
        int bitcount = 0;
        for (int dim = 0 ; dim < region->Dimensions ; dim++) {
            if (region->pDimensionDefinitions[dim].bits == 0) continue;
            nbDimensions++;

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
    } else {
        dimreg = 0;
    }
    dimregion_selected();
    queue_resize();
}

bool DimRegionChooser::on_button_release_event(GdkEventButton* event)
{
    if (resize.active) {
        get_window()->pointer_ungrab(event->time);
        resize.active = false;

        if (region->pDimensionDefinitions[resize.dimension].dimension == gig::dimension_velocity) {

            int bitpos = 0;
            for (int j = 0 ; j < resize.dimension ; j++) {
                bitpos += region->pDimensionDefinitions[j].bits;
            }
            int mask =
                ~(((1 << region->pDimensionDefinitions[resize.dimension].bits) - 1) << bitpos);
            int c = dimregno & mask; // mask away this dimension

            if (region->pDimensionRegions[c]->DimensionUpperLimits[resize.dimension] == 0) {
                // the velocity dimension didn't previously have
                // custom v3 splits, so we initialize all splits with
                // default values
                int nbZones = region->pDimensionDefinitions[resize.dimension].zones;
                for (int j = 0 ; j < nbZones ; j++) {
                    gig::DimensionRegion *d = region->pDimensionRegions[c + (j << bitpos)];
                    d->DimensionUpperLimits[resize.dimension] = int(128.0 * (j + 1) / nbZones - 1);
                }
            }
            if (region->pDimensionRegions[c]->VelocityUpperLimit == 0) {
                // the velocity dimension didn't previously have
                // custom v2 splits, so we initialize all splits with
                // default values
                int nbZones = region->pDimensionDefinitions[resize.dimension].zones;
                for (int j = 0 ; j < nbZones ; j++) {
                    gig::DimensionRegion *d = region->pDimensionRegions[c + (j << bitpos)];
                    d->VelocityUpperLimit = int(128.0 * (j + 1) / nbZones - 1);
                }
            }

            gig::DimensionRegion *d = region->pDimensionRegions[c + resize.offset];
            // update both v2 and v3 values
            d->DimensionUpperLimits[resize.dimension] = resize.pos - 1;
            d->VelocityUpperLimit = resize.pos - 1;

        } else {
            for (int i = 0 ; i < region->DimensionRegions ; ) {

                if (region->pDimensionRegions[i]->DimensionUpperLimits[resize.dimension] == 0) {
                    // the dimension didn't previously have custom
                    // limits, so we have to set default limits for
                    // all the dimension regions
                    int bitpos = 0;
                    for (int j = 0 ; j < resize.dimension ; j++) {
                        bitpos += region->pDimensionDefinitions[j].bits;
                    }
                    int nbZones = region->pDimensionDefinitions[resize.dimension].zones;

                    for (int j = 0 ; j < nbZones ; j++) {
                        gig::DimensionRegion *d = region->pDimensionRegions[i + (j << bitpos)];
                        d->DimensionUpperLimits[resize.dimension] = int(128.0 * (j + 1) / nbZones - 1);
                    }
                }
                gig::DimensionRegion *d = region->pDimensionRegions[i + resize.offset];
                d->DimensionUpperLimits[resize.dimension] = resize.pos - 1;

                int bitpos = 0;
                int j;
                for (j = 0 ; j < region->Dimensions ; j++) {
                    if (j != resize.dimension) {
                        int maxzones = 1 << region->pDimensionDefinitions[j].bits;
                        int dimj = (i >> bitpos) & (maxzones - 1);
                        if (dimj + 1 < region->pDimensionDefinitions[j].zones) break;
                    }
                    bitpos += region->pDimensionDefinitions[j].bits;
                }
                if (j == region->Dimensions) break;
                i = (i & ~((1 << bitpos) - 1)) + (1 << bitpos);
            }
        }
        region_changed();

        if (!is_in_resize_zone(event->x, event->y) && cursor_is_resize) {
            get_window()->set_cursor();
            cursor_is_resize = false;
        }
    }
    return true;
}

bool DimRegionChooser::on_button_press_event(GdkEventButton* event)
{
    if (region && event->y < nbDimensions * h &&
        event->x >= label_width && event->x < w) {

        if (is_in_resize_zone(event->x, event->y)) {
            Gdk::Cursor double_arrow(Gdk::SB_H_DOUBLE_ARROW);
            get_window()->pointer_grab(false,
                                       Gdk::BUTTON_RELEASE_MASK |
                                       Gdk::POINTER_MOTION_MASK |
                                       Gdk::POINTER_MOTION_HINT_MASK,
                                       double_arrow, event->time);
            resize.active = true;
        } else {
            int ydim = int(event->y / h);
            int dim;
            for (dim = 0 ; dim < region->Dimensions ; dim++) {
                if (region->pDimensionDefinitions[dim].bits == 0) continue;
                if (ydim == 0) break;
                ydim--;
            }
            int nbZones = region->pDimensionDefinitions[dim].zones;

            int z = -1;
            int bitpos = 0;
            for (int i = 0 ; i < dim ; i++) {
                bitpos += region->pDimensionDefinitions[i].bits;
            }

            int i = dim;
            if (dimregno < 0) dimregno = 0;
            int mask = ~(((1 << region->pDimensionDefinitions[i].bits) - 1) << bitpos);
            int c = dimregno & mask; // mask away this dimension

            bool customsplits =
                ((region->pDimensionDefinitions[i].split_type == gig::split_type_normal &&
                  region->pDimensionRegions[c]->DimensionUpperLimits[i]) ||
                 (region->pDimensionDefinitions[i].dimension == gig::dimension_velocity &&
                  region->pDimensionRegions[c]->VelocityUpperLimit));
            if (customsplits) {
                int val = int((event->x - label_width) * 128 / (w - label_width - 1));

                if (region->pDimensionRegions[c]->DimensionUpperLimits[i]) {
                    for (z = 0 ; z < nbZones ; z++) {
                        gig::DimensionRegion *d = region->pDimensionRegions[c + (z << bitpos)];
                        if (val <= d->DimensionUpperLimits[i]) break;
                    }
                } else {
                    for (z = 0 ; z < nbZones ; z++) {
                        gig::DimensionRegion *d = region->pDimensionRegions[c + (z << bitpos)];
                        if (val <= d->VelocityUpperLimit) break;
                    }
                }
            } else {
                z = int((event->x - label_width) * nbZones / (w - label_width - 1));
            }

            printf("dim=%d z=%d dimensionsource=%d split_type=%d zones=%d zone_size=%f\n", dim, z,
                   region->pDimensionDefinitions[dim].dimension,
                   region->pDimensionDefinitions[dim].split_type,
                   region->pDimensionDefinitions[dim].zones,
                   region->pDimensionDefinitions[dim].zone_size);
#if 0
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
#endif

            dimregno = c | (z << bitpos);

            focus_line = dim;
            if (has_focus()) queue_draw();
            else grab_focus();
            dimreg = region->pDimensionRegions[dimregno];
            dimregion_selected();
        }
    }
    return true;
}

bool DimRegionChooser::on_motion_notify_event(GdkEventMotion* event)
{
    Glib::RefPtr<Gdk::Window> window = get_window();
    int x, y;
    Gdk::ModifierType state = Gdk::ModifierType(0);
    window->get_pointer(x, y, state);

    if (resize.active) {
        int k = int((x - label_width) * 128.0 / (w - label_width - 1) + 0.5);

        if (k < resize.min) k = resize.min;
        else if (k > resize.max) k = resize.max;

        if (k < 2) k = 2; // k is upper limit + 1, upper limit 0 is forbidden

        if (k != resize.pos) {
            Glib::RefPtr<const Gdk::GC> black = get_style()->get_black_gc();
            Glib::RefPtr<const Gdk::GC> white = get_style()->get_white_gc();

            int prevx = int((w - label_width - 1) * resize.pos / 128.0 + 0.5) + label_width;
            int x = int((w - label_width - 1) * k / 128.0 + 0.5) + label_width;
            int y = resize.dimension * h;

            if (resize.selected == resize.none) {
                if (resize.pos != resize.min && resize.pos != resize.max) {
                    window->draw_line(white, prevx, y + 1, prevx, y + h - 2);
                }
            } else {
                gc->set_foreground(red);

                Glib::RefPtr<const Gdk::GC> left;
                Glib::RefPtr<const Gdk::GC> right;
                if (resize.selected == resize.left) {
                    left = gc;
                    right = white;
                } else {
                    left = white;
                    right = gc;
                }

                if (k > resize.pos) {
                    int xx = resize.pos == resize.min ? 1 : 0;
                    window->draw_rectangle(left, true,
                                           prevx + xx, y + 1, x - prevx - xx, h - 2);
                } else {
                    int xx = resize.pos == resize.max ? 0 : 1;
                    window->draw_rectangle(right, true,
                                           x, y + 1, prevx - x + xx, h - 2);
                }
            }
            window->draw_line(black, x, y + 1, x, y + h - 2);
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

bool DimRegionChooser::is_in_resize_zone(double x, double y)
{
    if (region && y < nbDimensions * h && x >= label_width && x < w) {
        int ydim = int(y / h);
        int dim;
        int bitpos = 0;
        for (dim = 0 ; dim < region->Dimensions ; dim++) {
            if (region->pDimensionDefinitions[dim].bits == 0) continue;
            if (ydim == 0) break;
            ydim--;
            bitpos += region->pDimensionDefinitions[dim].bits;
        }
        int nbZones = region->pDimensionDefinitions[dim].zones;

        int c = 0;
        if (dimregno >= 0) {
            int mask = ~(((1 << region->pDimensionDefinitions[dim].bits) - 1) << bitpos);
            c = dimregno & mask; // mask away this dimension
        }
        const bool customsplits =
            ((region->pDimensionDefinitions[dim].split_type == gig::split_type_normal &&
              region->pDimensionRegions[c]->DimensionUpperLimits[dim]) ||
             (region->pDimensionDefinitions[dim].dimension == gig::dimension_velocity &&
              region->pDimensionRegions[c]->VelocityUpperLimit));

        // dimensions of split_type_bit cannot be resized
        if (region->pDimensionDefinitions[dim].split_type != gig::split_type_bit) {
            int prev_limit = 0;
            for (int iZone = 0 ; iZone < nbZones - 1 ; iZone++) {
                gig::DimensionRegion *d = region->pDimensionRegions[c + (iZone << bitpos)];
                const int upperLimit =
                    (customsplits) ?
                        (d->DimensionUpperLimits[dim]) ?
                            d->DimensionUpperLimits[dim] : d->VelocityUpperLimit
                        : (iZone+1) * (int)region->pDimensionDefinitions[dim].zone_size - 1;
                int limit = upperLimit + 1;
                int limitx = int((w - label_width - 1) * limit / 128.0 + 0.5) + label_width;
                if (x <= limitx - 2) break;
                if (x <= limitx + 2) {
                    resize.dimension = dim;
                    resize.offset = iZone << bitpos;
                    resize.pos = limit;
                    resize.min = prev_limit;

                    int dr = (dimregno >> bitpos) &
                        ((1 << region->pDimensionDefinitions[dim].bits) - 1);
                    resize.selected = dr == iZone ? resize.left :
                        dr == iZone + 1 ? resize.right : resize.none;

                    iZone++;
                    gig::DimensionRegion *d = region->pDimensionRegions[c + (iZone << bitpos)];

                    const int upperLimit =
                        (customsplits) ?
                            (d->DimensionUpperLimits[dim]) ?
                                d->DimensionUpperLimits[dim] : d->VelocityUpperLimit
                            : (iZone+1) * (int)region->pDimensionDefinitions[dim].zone_size - 1;

                    int limit = upperLimit + 1;
                    resize.max = limit;
                    return true;
                }
                prev_limit = limit;
            }
        }
    }
    return false;
}

sigc::signal<void> DimRegionChooser::signal_dimregion_selected()
{
    return dimregion_selected;
}

sigc::signal<void> DimRegionChooser::signal_region_changed()
{
    return region_changed;
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
