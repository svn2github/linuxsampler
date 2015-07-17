/*
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

#include <gtkmmconfig.h>

#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
#include <gdkmm/window.h>
#include <gdkmm/general.h>
#include <gdk/gdkcairo.h>
#include "compat.h"

namespace Gdk {
    namespace Cairo {
        void set_source_rgba(const ::Cairo::RefPtr< ::Cairo::Context >& context,
                             const Gdk::RGBA& color) {
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 10) || GTKMM_MAJOR_VERSION < 2
            gdk_cairo_set_source_color(context->cobj(),
                                       const_cast<GdkColor*>(color.gobj()));
#else
            set_source_color(context, color);
#endif
        }
    }
}
#endif
