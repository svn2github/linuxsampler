/*
 * Copyright (C) 2007 Andreas Persson
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

#include "gigedit.h"

#include <gtkmm/main.h>
#include "mainwindow.h"

#include <libintl.h>
#include <config.h>

// the app has to work from a DLL as well, so we hard code argv
int argc = 1;
char* argv_c[] = { "gigedit" };
char** argv = argv_c;

static void __init_app() {
    setlocale(LC_ALL, "");
    bindtextdomain(GETTEXT_PACKAGE, LOCALEDIR);
    bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
    textdomain(GETTEXT_PACKAGE);

    Glib::thread_init();
}

int GigEdit::run() {
    __init_app();
    Gtk::Main kit(argc, argv);
    MainWindow window;
    kit.run(window);
    return 0;
}

int GigEdit::run(const char* pFileName) {
    __init_app();
    Gtk::Main kit(argc, argv);
    MainWindow window;
    if (pFileName) window.load_file(pFileName);
    kit.run(window);
    return 0;
}

int GigEdit::run(gig::Instrument* pInstrument) {
    __init_app();
    Gtk::Main kit(argc, argv);
    MainWindow window;
    if (pInstrument) window.load_instrument(pInstrument);
    kit.run(window);
    return 0;
}
