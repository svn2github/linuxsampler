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

#include "dimregionchooser.h"
#include <cairomm/context.h>
#include <gdkmm/cursor.h>
#include <gdkmm/general.h>
#include <glibmm/stringutils.h>
#include <gtkmm/stock.h>
#include <glibmm/ustring.h>
#include <gtkmm/messagedialog.h>

#include "global.h"

// taken from gdk/gdkkeysyms.h
// (define on demand, to avoid unnecessary dev lib package build dependency)
#ifndef GDK_KEY_Control_L
# define GDK_KEY_Control_L 0xffe3
#endif
#ifndef GDK_KEY_Control_R
# define GDK_KEY_Control_R 0xffe4
#endif

static std::map<gig::dimension_t,int> caseOfDimRegion(gig::DimensionRegion* dr, bool* isValidZone) {
    std::map<gig::dimension_t,int> dimCase;
    if (!dr) {
        *isValidZone = false;
        return dimCase;
    }

    gig::Region* rgn = (gig::Region*) dr->GetParent();

    // find the dimension region index of the passed dimension region
    int drIndex;
    for (drIndex = 0; drIndex < 256; ++drIndex)
        if (rgn->pDimensionRegions[drIndex] == dr)
            break;

    // not found in region, something's horribly wrong
    if (drIndex == 256) {
        fprintf(stderr, "DimRegionChooser: ERROR: index of dim region not found!\n");
        *isValidZone = false;
        return std::map<gig::dimension_t,int>();
    }

    for (int d = 0, baseBits = 0; d < rgn->Dimensions; ++d) {
        const int bits = rgn->pDimensionDefinitions[d].bits;
        dimCase[rgn->pDimensionDefinitions[d].dimension] =
            (drIndex >> baseBits) & ((1 << bits) - 1);
        baseBits += bits;
        // there are also DimensionRegion objects of unused zones, skip them
        if (dimCase[rgn->pDimensionDefinitions[d].dimension] >= rgn->pDimensionDefinitions[d].zones) {
            *isValidZone = false;
            return std::map<gig::dimension_t,int>();
        }
    }

    *isValidZone = true;
    return dimCase;
}

DimRegionChooser::DimRegionChooser(Gtk::Window& window) :
    red("#8070ff"),
    black("black"),
    white("white")
{
    instrument = 0;
    region = 0;
    maindimregno = -1;
    focus_line = 0;
    resize.active = false;
    cursor_is_resize = false;
    h = 24;
    multiSelectKeyDown = false;
    set_can_focus();

    actionGroup = Gtk::ActionGroup::create();
    actionGroup->add(
        Gtk::Action::create("SplitDimZone", _("Split Dimensions Zone")),
        sigc::mem_fun(*this, &DimRegionChooser::split_dimension_zone)
    );
    actionGroup->add(
        Gtk::Action::create("DeleteDimZone", _("Delete Dimension Zone")),
        sigc::mem_fun(*this, &DimRegionChooser::delete_dimension_zone)
    );

    uiManager = Gtk::UIManager::create();
    uiManager->insert_action_group(actionGroup);
    Glib::ustring ui_info =
        "<ui>"
        "  <popup name='PopupMenuInsideDimRegion'>"
        "    <menuitem action='SplitDimZone'/>"
        "    <menuitem action='DeleteDimZone'/>"
        "  </popup>"
//         "  <popup name='PopupMenuOutsideDimRegion'>"
//         "    <menuitem action='Add'/>"
//         "  </popup>"
        "</ui>";
    uiManager->add_ui_from_string(ui_info);

    popup_menu_inside_dimregion = dynamic_cast<Gtk::Menu*>(
        uiManager->get_widget("/PopupMenuInsideDimRegion"));
//     popup_menu_outside_dimregion = dynamic_cast<Gtk::Menu*>(
//         uiManager->get_widget("/PopupMenuOutsideDimRegion"));

    add_events(Gdk::BUTTON_PRESS_MASK | Gdk::POINTER_MOTION_MASK |
               Gdk::POINTER_MOTION_HINT_MASK);

    labels_changed = true;

    set_tooltip_text(_(
        "Right click here for options on altering dimension zones. Press and "
        "hold CTRL key for selecting multiple dimension zones simultaniously."
    ));
    
    window.signal_key_press_event().connect(
        sigc::mem_fun(*this, &DimRegionChooser::onKeyPressed)
    );
    window.signal_key_release_event().connect(
        sigc::mem_fun(*this, &DimRegionChooser::onKeyReleased)
    );
}

DimRegionChooser::~DimRegionChooser()
{
}

#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
bool DimRegionChooser::on_expose_event(GdkEventExpose* e)
{
    double clipx1 = e->area.x;
    double clipx2 = e->area.x + e->area.width;
    double clipy1 = e->area.y;
    double clipy2 = e->area.y + e->area.height;

    const Cairo::RefPtr<Cairo::Context>& cr =
        get_window()->create_cairo_context();
#else
bool DimRegionChooser::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    double clipx1, clipx2, clipy1, clipy2;
    cr->get_clip_extents(clipx1, clipy1, clipx2, clipy2);
#endif

    if (!region) return true;

    // This is where we draw on the window
    int w = get_width();
    Glib::RefPtr<Pango::Context> context = get_pango_context();

    Glib::RefPtr<Pango::Layout> layout = Pango::Layout::create(context);
    cr->set_line_width(1);

    int y = 0;
    if (labels_changed || label_width - 10 > clipx1) {
        // draw labels on the left (reflecting the dimension type)
        double maxwidth = 0;
        for (int i = 0 ; i < region->Dimensions ; i++) {
            int nbZones = region->pDimensionDefinitions[i].zones;
            if (nbZones) {
                const char* dstr;
                char dstrbuf[10];
                switch (region->pDimensionDefinitions[i].dimension) {
                case gig::dimension_none: dstr=_("none"); break;
                case gig::dimension_samplechannel: dstr=_("samplechannel");
                    break;
                case gig::dimension_layer: dstr=_("layer"); break;
                case gig::dimension_velocity: dstr=_("velocity"); break;
                case gig::dimension_channelaftertouch:
                    dstr=_("channelaftertouch"); break;
                case gig::dimension_releasetrigger:
                    dstr=_("releasetrigger"); break;
                case gig::dimension_keyboard: dstr=_("keyswitching"); break;
                case gig::dimension_roundrobin: dstr=_("roundrobin"); break;
                case gig::dimension_random: dstr=_("random"); break;
                case gig::dimension_smartmidi: dstr=_("smartmidi"); break;
                case gig::dimension_roundrobinkeyboard:
                    dstr=_("roundrobinkeyboard"); break;
                case gig::dimension_modwheel: dstr=_("modwheel"); break;
                case gig::dimension_breath: dstr=_("breath"); break;
                case gig::dimension_foot: dstr=_("foot"); break;
                case gig::dimension_portamentotime:
                    dstr=_("portamentotime"); break;
                case gig::dimension_effect1: dstr=_("effect1"); break;
                case gig::dimension_effect2: dstr=_("effect2"); break;
                case gig::dimension_genpurpose1: dstr=_("genpurpose1"); break;
                case gig::dimension_genpurpose2: dstr=_("genpurpose2"); break;
                case gig::dimension_genpurpose3: dstr=_("genpurpose3"); break;
                case gig::dimension_genpurpose4: dstr=_("genpurpose4"); break;
                case gig::dimension_sustainpedal:
                    dstr=_("sustainpedal"); break;
                case gig::dimension_portamento: dstr=_("portamento"); break;
                case gig::dimension_sostenutopedal:
                    dstr=_("sostenutopedal"); break;
                case gig::dimension_softpedal: dstr=_("softpedal"); break;
                case gig::dimension_genpurpose5: dstr=_("genpurpose5"); break;
                case gig::dimension_genpurpose6: dstr=_("genpurpose6"); break;
                case gig::dimension_genpurpose7: dstr=_("genpurpose7"); break;
                case gig::dimension_genpurpose8: dstr=_("genpurpose8"); break;
                case gig::dimension_effect1depth:
                    dstr=_("effect1depth"); break;
                case gig::dimension_effect2depth:
                    dstr=_("effect2depth"); break;
                case gig::dimension_effect3depth:
                    dstr=_("effect3depth"); break;
                case gig::dimension_effect4depth:
                    dstr=_("effect4depth"); break;
                case gig::dimension_effect5depth:
                    dstr=_("effect5depth"); break;
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

                if (y + h > clipy1 && y < clipy2 && text_w >= clipx1) {
                    double text_h = double(rectangle.get_height()) /
                        Pango::SCALE;
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
                    const Gdk::Color fg = get_style()->get_fg(get_state());
#else
                    const Gdk::RGBA fg =
                        get_style_context()->get_color(get_state_flags());
#endif
                    Gdk::Cairo::set_source_rgba(cr, fg);
                    cr->move_to(4, int(y + (h - text_h) / 2 + 0.5));
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 16) || GTKMM_MAJOR_VERSION < 2
                    pango_cairo_show_layout(cr->cobj(), layout->gobj());
#else
                    layout->show_in_cairo_context(cr);
#endif
                }
            }
            y += h;
        }
        label_width = int(maxwidth + 10);
        labels_changed = false;
    }
    if (label_width >= clipx2) return true;

    // draw dimensions' zones areas
    y = 0;
    int bitpos = 0;
    for (int i = 0 ; i < region->Dimensions ; i++) {
        int nbZones = region->pDimensionDefinitions[i].zones;
        if (nbZones) {
            const gig::dimension_t dimension = region->pDimensionDefinitions[i].dimension;

            if (y >= clipy2) break;
            if (y + h > clipy1) {
                // draw focus rectangle around dimension's label and zones
                if (has_focus() && focus_line == i) {
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
                    Gdk::Rectangle farea(0, y, 150, h);
                    get_style()->paint_focus(get_window(), get_state(), farea,
                                             *this, "",
                                             0, y, label_width, h);
#else
                    get_style_context()->render_focus(cr,
                                                      0, y, label_width, h);
#endif
                }

                // draw top and bottom lines of dimension's zones
                Gdk::Cairo::set_source_rgba(cr, black);
                cr->move_to(label_width, y + 0.5);
                cr->line_to(w, y + 0.5);
                cr->move_to(w, y + h - 0.5);
                cr->line_to(label_width, y + h - 0.5);
                cr->stroke();

                // erase whole dimension's zones area
                Gdk::Cairo::set_source_rgba(cr, white);
                cr->rectangle(label_width + 1, y + 1,
                              (w - label_width - 2), h - 2);
                cr->fill();

                int c = 0;
                if (maindimregno >= 0) {
                    int mask =
                        ~(((1 << region->pDimensionDefinitions[i].bits) - 1) <<
                          bitpos);
                    c = maindimregno & mask; // mask away this dimension
                }
                bool customsplits =
                    ((region->pDimensionDefinitions[i].split_type ==
                      gig::split_type_normal &&
                      region->pDimensionRegions[c]->DimensionUpperLimits[i]) ||
                     (region->pDimensionDefinitions[i].dimension ==
                      gig::dimension_velocity &&
                      region->pDimensionRegions[c]->VelocityUpperLimit));

                // draw dimension zones
                Gdk::Cairo::set_source_rgba(cr, black);
                if (customsplits) {
                    cr->move_to(label_width + 0.5, y + 1);
                    cr->line_to(label_width + 0.5, y + h - 1);
                    int prevX = label_width;
                    int prevUpperLimit = -1;

                    for (int j = 0 ; j < nbZones ; j++) {
                        // draw dimension zone's borders for custom splits
                        gig::DimensionRegion* d =
                            region->pDimensionRegions[c + (j << bitpos)];
                        int upperLimit = d->DimensionUpperLimits[i];
                        if (!upperLimit) upperLimit = d->VelocityUpperLimit;
                        int v = upperLimit + 1;
                        int x = int((w - label_width - 1) * v / 128.0 + 0.5) +
                            label_width;
                        if (x >= clipx2) break;
                        if (x < clipx1) continue;
                        Gdk::Cairo::set_source_rgba(cr, black);
                        cr->move_to(x + 0.5, y + 1);
                        cr->line_to(x + 0.5, y + h - 1);
                        cr->stroke();

                        // draw fill for zone
                        bool isSelectedZone = this->dimzones[dimension].count(j);
                        Gdk::Cairo::set_source_rgba(cr, isSelectedZone ? red : white);
                        cr->rectangle(prevX + 1, y + 1, x - prevX - 1, h - 1);
                        cr->fill();

                        // draw text showing the beginning of the dimension zone
                        // as numeric value to the user
                        {
                            Glib::RefPtr<Pango::Layout> layout = Pango::Layout::create(context);
                            layout->set_text(Glib::Ascii::dtostr(prevUpperLimit+1));
                            Gdk::Cairo::set_source_rgba(cr, black);
                            Pango::Rectangle rect = layout->get_logical_extents();
                            // get the text dimensions
                            int text_width, text_height;
                            layout->get_pixel_size(text_width, text_height);
                            // move text to the left end of the dimension zone
                            cr->move_to(prevX + 3, y + (h - text_height) / 2);
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 16) || GTKMM_MAJOR_VERSION < 2
                            pango_cairo_show_layout(cr->cobj(), layout->gobj());
#else
                            layout->show_in_cairo_context(cr);
#endif
                        }
                        // draw text showing the end of the dimension zone
                        // as numeric value to the user
                        {
                            Glib::RefPtr<Pango::Layout> layout = Pango::Layout::create(context);
                            layout->set_text(Glib::Ascii::dtostr(upperLimit));
                            Gdk::Cairo::set_source_rgba(cr, black);
                            Pango::Rectangle rect = layout->get_logical_extents();
                            // get the text dimensions
                            int text_width, text_height;
                            layout->get_pixel_size(text_width, text_height);
                            // move text to the left end of the dimension zone
                            cr->move_to(x - 3 - text_width, y + (h - text_height) / 2);
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 16) || GTKMM_MAJOR_VERSION < 2
                            pango_cairo_show_layout(cr->cobj(), layout->gobj());
#else
                            layout->show_in_cairo_context(cr);
#endif
                        }

                        prevX = x;
                        prevUpperLimit = upperLimit;
                    }
                } else {
                    int prevX = 0;
                    for (int j = 0 ; j <= nbZones ; j++) {
                        // draw dimension zone's borders for normal splits
                        int x = int((w - label_width - 1) * j /
                                    double(nbZones) + 0.5) + label_width;
                        if (x >= clipx2) break;
                        if (x < clipx1) continue;
                        Gdk::Cairo::set_source_rgba(cr, black);
                        cr->move_to(x + 0.5, y + 1);
                        cr->line_to(x + 0.5, y + h - 1);
                        cr->stroke();

                        if (j != 0) {
                            // draw fill for zone
                            bool isSelectedZone = this->dimzones[dimension].count(j-1);
                            Gdk::Cairo::set_source_rgba(cr, isSelectedZone ? red : white);
                            cr->rectangle(prevX + 1, y + 1, x - prevX - 1, h - 1);
                            cr->fill();

                            // draw text showing the beginning of the dimension zone
                            // as numeric value to the user
                            {
                                Glib::RefPtr<Pango::Layout> layout = Pango::Layout::create(context);
                                layout->set_text(Glib::Ascii::dtostr((j-1) * 128/nbZones));
                                Gdk::Cairo::set_source_rgba(cr, black);
                                Pango::Rectangle rect = layout->get_logical_extents();
                                // get the text dimensions
                                int text_width, text_height;
                                layout->get_pixel_size(text_width, text_height);
                                // move text to the left end of the dimension zone
                                cr->move_to(prevX + 3, y + (h - text_height) / 2);
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 16) || GTKMM_MAJOR_VERSION < 2
                                pango_cairo_show_layout(cr->cobj(), layout->gobj());
#else
                                layout->show_in_cairo_context(cr);
#endif
                            }
                            // draw text showing the end of the dimension zone
                            // as numeric value to the user
                            {
                                Glib::RefPtr<Pango::Layout> layout = Pango::Layout::create(context);
                                layout->set_text(Glib::Ascii::dtostr(j * 128/nbZones - 1));
                                Gdk::Cairo::set_source_rgba(cr, black);
                                Pango::Rectangle rect = layout->get_logical_extents();
                                // get the text dimensions
                                int text_width, text_height;
                                layout->get_pixel_size(text_width, text_height);
                                // move text to the left end of the dimension zone
                                cr->move_to(x - 3 - text_width, y + (h - text_height) / 2);
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 16) || GTKMM_MAJOR_VERSION < 2
                                pango_cairo_show_layout(cr->cobj(), layout->gobj());
#else
                                layout->show_in_cairo_context(cr);
#endif
                            }
                        }
                        prevX = x;
                    }       
                }
            }
            y += h;
        }
        bitpos += region->pDimensionDefinitions[i].bits;
    }

    return true;
}

void DimRegionChooser::set_region(gig::Region* region)
{
    this->region = region;
    maindimregno = 0;
    nbDimensions = 0;
    if (region) {
        int bitcount = 0;
        for (int dim = 0 ; dim < region->Dimensions ; dim++) {
            if (region->pDimensionDefinitions[dim].bits == 0) continue;
            nbDimensions++;

            int z = std::min(maindimcase[region->pDimensionDefinitions[dim].dimension],
                             region->pDimensionDefinitions[dim].zones - 1);
            maindimregno |= (z << bitcount);
            bitcount += region->pDimensionDefinitions[dim].bits;
        }
    }
    dimregion_selected();
    set_size_request(800, region ? nbDimensions * h : 0);

    labels_changed = true;
    queue_resize();
    queue_draw();
}

void DimRegionChooser::refresh_all() {
    set_region(region);
}

void DimRegionChooser::get_dimregions(const gig::Region* region, bool stereo,
                                      std::set<gig::DimensionRegion*>& dimregs) const
{
    for (int iDimRgn = 0; iDimRgn < 256; ++iDimRgn) {
        gig::DimensionRegion* dimRgn = region->pDimensionRegions[iDimRgn];
        if (!dimRgn) continue;
        bool isValidZone;
        std::map<gig::dimension_t,int> dimCase = caseOfDimRegion(dimRgn, &isValidZone);
        if (!isValidZone) continue;
        for (std::map<gig::dimension_t,int>::const_iterator it = dimCase.begin();
             it != dimCase.end(); ++it)
        {
            if (stereo && it->first == gig::dimension_samplechannel) continue; // is selected

            std::map<gig::dimension_t, std::set<int> >::const_iterator itSelectedDimension =
                this->dimzones.find(it->first);
            if (itSelectedDimension != this->dimzones.end() &&
                itSelectedDimension->second.count(it->second)) continue; // is selected

            goto notSelected;
        }

        dimregs.insert(dimRgn);

        notSelected:
        ;
    }
}

void DimRegionChooser::update_after_resize()
{
    if (region->pDimensionDefinitions[resize.dimension].dimension == gig::dimension_velocity) {

        int bitpos = 0;
        for (int j = 0 ; j < resize.dimension ; j++) {
            bitpos += region->pDimensionDefinitions[j].bits;
        }
        int mask =
            ~(((1 << region->pDimensionDefinitions[resize.dimension].bits) - 1) << bitpos);
        int c = maindimregno & mask; // mask away this dimension

        if (region->pDimensionRegions[c]->DimensionUpperLimits[resize.dimension] == 0) {
            // the velocity dimension didn't previously have
            // custom v3 splits, so we initialize all splits with
            // default values
            int nbZones = region->pDimensionDefinitions[resize.dimension].zones;
            for (int j = 0 ; j < nbZones ; j++) {
                gig::DimensionRegion* d = region->pDimensionRegions[c + (j << bitpos)];
                d->DimensionUpperLimits[resize.dimension] = int(128.0 * (j + 1) / nbZones - 1);
            }
        }
        if (region->pDimensionRegions[c]->VelocityUpperLimit == 0) {
            // the velocity dimension didn't previously have
            // custom v2 splits, so we initialize all splits with
            // default values
            int nbZones = region->pDimensionDefinitions[resize.dimension].zones;
            for (int j = 0 ; j < nbZones ; j++) {
                gig::DimensionRegion* d = region->pDimensionRegions[c + (j << bitpos)];
                d->VelocityUpperLimit = int(128.0 * (j + 1) / nbZones - 1);
            }
        }

        gig::DimensionRegion* d = region->pDimensionRegions[c + resize.offset];
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
                    gig::DimensionRegion* d = region->pDimensionRegions[i + (j << bitpos)];
                    d->DimensionUpperLimits[resize.dimension] = int(128.0 * (j + 1) / nbZones - 1);
                }
            }
            gig::DimensionRegion* d = region->pDimensionRegions[i + resize.offset];
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
}

bool DimRegionChooser::on_button_release_event(GdkEventButton* event)
{
    if (resize.active) {
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
        get_window()->pointer_ungrab(event->time);
#else
        Glib::wrap(event->device, true)->ungrab(event->time);
#endif
        resize.active = false;

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
    int w = get_width();
    if (region && event->y < nbDimensions * h &&
        event->x >= label_width && event->x < w) {

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
            if (maindimregno < 0) maindimregno = 0;
            int mask = ~(((1 << region->pDimensionDefinitions[i].bits) - 1) << bitpos);
            int c = this->maindimregno & mask; // mask away this dimension

            bool customsplits =
                ((region->pDimensionDefinitions[i].split_type == gig::split_type_normal &&
                  region->pDimensionRegions[c]->DimensionUpperLimits[i]) ||
                 (region->pDimensionDefinitions[i].dimension == gig::dimension_velocity &&
                  region->pDimensionRegions[c]->VelocityUpperLimit));
            if (customsplits) {
                int val = int((event->x - label_width) * 128 / (w - label_width - 1));

                if (region->pDimensionRegions[c]->DimensionUpperLimits[i]) {
                    for (z = 0 ; z < nbZones ; z++) {
                        gig::DimensionRegion* d = region->pDimensionRegions[c + (z << bitpos)];
                        if (val <= d->DimensionUpperLimits[i]) break;
                    }
                } else {
                    for (z = 0 ; z < nbZones ; z++) {
                        gig::DimensionRegion* d = region->pDimensionRegions[c + (z << bitpos)];
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
            this->maindimcase[region->pDimensionDefinitions[dim].dimension] = z;
            this->maindimregno = c | (z << bitpos);
            this->maindimtype = region->pDimensionDefinitions[dim].dimension;

            if (multiSelectKeyDown) {
                if (dimzones[this->maindimtype].count(z)) {
                    if (dimzones[this->maindimtype].size() > 1) {
                        dimzones[this->maindimtype].erase(z);
                    }
                } else {
                    dimzones[this->maindimtype].insert(z);
                }
            } else {
                this->dimzones.clear();
                for (std::map<gig::dimension_t,int>::const_iterator it = this->maindimcase.begin();
                     it != this->maindimcase.end(); ++it)
                {
                    this->dimzones[it->first].insert(it->second);
                }
            }

            focus_line = dim;
            if (has_focus()) queue_draw();
            else grab_focus();
            dimregion_selected();

            if (event->button == 3) {
                printf("dimregion right click\n");
                popup_menu_inside_dimregion->popup(event->button, event->time);
            }

            queue_draw();
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
        int w = get_width();
        int k = int((x - label_width) * 128.0 / (w - label_width - 1) + 0.5);

        if (k < resize.min) k = resize.min;
        else if (k > resize.max) k = resize.max;

        if (k < 2) k = 2; // k is upper limit + 1, upper limit 0 is forbidden

        if (k != resize.pos) {
            int prevx = int((w - label_width - 1) * resize.pos / 128.0 + 0.5) + label_width;
            int x = int((w - label_width - 1) * k / 128.0 + 0.5) + label_width;
            int y = resize.dimension * h;
            int x1, x2;
            if (k > resize.pos) {
                x1 = prevx;
                x2 = x;
            } else {
                x1 = x;
                x2 = prevx;
            }
            Gdk::Rectangle rect(x1, y + 1, x2 - x1 + 1, h - 2);

            resize.pos = k;
            update_after_resize();
            get_window()->invalidate_rect(rect, false); // not sufficient ...
            queue_draw(); // ... so do a complete redraw instead.
        }
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

bool DimRegionChooser::is_in_resize_zone(double x, double y)
{
    int w = get_width();
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
        if (maindimregno >= 0) {
            int mask = ~(((1 << region->pDimensionDefinitions[dim].bits) - 1) << bitpos);
            c = maindimregno & mask; // mask away this dimension
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
                gig::DimensionRegion* d = region->pDimensionRegions[c + (iZone << bitpos)];
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

                    int dr = (maindimregno >> bitpos) &
                        ((1 << region->pDimensionDefinitions[dim].bits) - 1);
                    resize.selected = dr == iZone ? resize.left :
                        dr == iZone + 1 ? resize.right : resize.none;

                    iZone++;
                    gig::DimensionRegion* d = region->pDimensionRegions[c + (iZone << bitpos)];

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

sigc::signal<void>& DimRegionChooser::signal_dimregion_selected()
{
    return dimregion_selected;
}

sigc::signal<void>& DimRegionChooser::signal_region_changed()
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

void DimRegionChooser::split_dimension_zone() {    
    printf("split_dimension_zone() type=%d, zone=%d\n", maindimtype, maindimcase[maindimtype]);
    try {
        region->SplitDimensionZone(maindimtype, maindimcase[maindimtype]);
    } catch (RIFF::Exception e) {
        Gtk::MessageDialog msg(e.Message, false, Gtk::MESSAGE_ERROR);
        msg.run();
    } catch (...) {
        Glib::ustring txt = _("An unknown exception occurred!");
        Gtk::MessageDialog msg(txt, false, Gtk::MESSAGE_ERROR);
        msg.run();
    }
    refresh_all();
}

void DimRegionChooser::delete_dimension_zone() {
    printf("delete_dimension_zone() type=%d, zone=%d\n", maindimtype, maindimcase[maindimtype]);
    try {
        region->DeleteDimensionZone(maindimtype, maindimcase[maindimtype]);
    } catch (RIFF::Exception e) {
        Gtk::MessageDialog msg(e.Message, false, Gtk::MESSAGE_ERROR);
        msg.run();
    } catch (...) {
        Glib::ustring txt = _("An unknown exception occurred!");
        Gtk::MessageDialog msg(txt, false, Gtk::MESSAGE_ERROR);
        msg.run();
    }
    refresh_all();
}

bool DimRegionChooser::onKeyPressed(GdkEventKey* key) {
    //printf("key down\n");
    if (key->keyval == GDK_KEY_Control_L || key->keyval == GDK_KEY_Control_R)
        multiSelectKeyDown = true;
}

bool DimRegionChooser::onKeyReleased(GdkEventKey* key) {
    //printf("key up\n");
    if (key->keyval == GDK_KEY_Control_L || key->keyval == GDK_KEY_Control_R)
        multiSelectKeyDown = false;
}

gig::DimensionRegion* DimRegionChooser::get_main_dimregion() const {
    if (!region) return NULL;
    return region->pDimensionRegions[maindimregno];
}
