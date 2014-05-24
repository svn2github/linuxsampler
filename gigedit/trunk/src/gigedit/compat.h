/*                                                         -*- c++ -*-
 * Copyright (C) 2011-2014 Andreas Persson
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

#ifndef GIGEDIT_COMPAT_H
#define GIGEDIT_COMPAT_H


// 2.10

#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 10) || GTKMM_MAJOR_VERSION < 2
#define create_cairo_context()                                          \
    gobj() ? Cairo::RefPtr<Cairo::Context>(                             \
        new Cairo::Context(gdk_cairo_create(get_window()->gobj()))) :   \
    Cairo::RefPtr<Cairo::Context>()
#endif


// 2.12

#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 12) || GTKMM_MAJOR_VERSION < 2
#include <gtkmm/cellrenderertext.h>
namespace Gtk {
    // this is not a real spin cell renderer, instead it's just text,
    // extended with a property for storing an adjustment
    class CellRendererSpin : public CellRendererText {
    private:
        Adjustment* adj;
        struct Proxy {
            Adjustment*& adj;
            Proxy(Adjustment*& adj) : adj(adj) { }
            const Adjustment* get_value() const { return adj; }
            void operator=(Adjustment* x) { adj = x; }
        };
    public:
        Proxy property_adjustment() const {
            return const_cast<Adjustment*&>(adj);
        }
    };
}
#endif


// 2.18

#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 18) || GTKMM_MAJOR_VERSION < 2
#define set_can_focus() set_flags(Gtk::CAN_FOCUS)
#define set_can_default() set_flags(Gtk::CAN_DEFAULT)
#endif


// 2.21.9

#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION == 21 && GTKMM_MICRO_VERSION < 9) || \
    (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 21) || GTKMM_MAJOR_VERSION < 2
#define ALIGN_START ALIGN_LEFT
#define ALIGN_END ALIGN_RIGHT
#endif


// 2.24

#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 24) || GTKMM_MAJOR_VERSION < 2
#define get_first_cell() get_first_cell_renderer()
#endif


// 3.0

#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
#include <cairomm/context.h>
#include <gdkmm/color.h>

namespace Gdk {
    typedef Color RGBA;

    namespace Cairo {
        void set_source_rgba(const ::Cairo::RefPtr< ::Cairo::Context >& context,
                             const Gdk::RGBA& color);
    }
}
#endif


// glibmm 2.31.2

#if (GLIBMM_MAJOR_VERSION == 2 && GLIBMM_MINOR_VERSION == 31 && GLIBMM_MICRO_VERSION < 2) || \
    (GLIBMM_MAJOR_VERSION == 2 && GLIBMM_MINOR_VERSION < 31) || GLIBMM_MAJOR_VERSION < 2

namespace Glib {
    namespace Threads {
        using Glib::Thread;
        using Glib::Mutex;
        using Glib::Cond;
    }
}

#define OLD_THREADS

#endif

#endif
