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
const char* argv_c[] = { "gigedit" };
char** argv = const_cast<char**>(argv_c);
//FIXME: Gtk only allows to instantiate one Gtk::Main object per process, so this might crash other Gtk applications, i.e. launched as plugins by LinuxSampler
Gtk::Main kit(argc, argv);

static void __init_app() {
    static bool process_initialized = false;
    if (!process_initialized) {
        std::cout << "Initializing 3rd party services needed by gigedit.\n"
                  << std::flush;
        setlocale(LC_ALL, "");
        bindtextdomain(GETTEXT_PACKAGE, LOCALEDIR);
        bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
        textdomain(GETTEXT_PACKAGE);
        // make sure thread_init() is called once and ONLY once per process
        if (!Glib::thread_supported()) Glib::thread_init();

        process_initialized = true;
    }
}

static void __connect_signals(GigEdit* gigedit, MainWindow* mainwindow) {
    // the signals of the "GigEdit" class are actually just proxies, that
    // is they simply forward the signals of the internal classes to the
    // outer world
    mainwindow->signal_file_structure_to_be_changed().connect(
        gigedit->signal_file_structure_to_be_changed().make_slot()
    );
    mainwindow->signal_file_structure_changed().connect(
        gigedit->signal_file_structure_changed().make_slot()
    );
    mainwindow->signal_samples_to_be_removed().connect(
        gigedit->signal_samples_to_be_removed().make_slot()
    );
    mainwindow->signal_samples_removed().connect(
        gigedit->signal_samples_removed().make_slot()
    );
    mainwindow->signal_region_to_be_changed().connect(
        gigedit->signal_region_to_be_changed().make_slot()
    );
    mainwindow->signal_region_changed().connect(
        gigedit->signal_region_changed().make_slot()
    );
    mainwindow->signal_dimreg_to_be_changed().connect(
        gigedit->signal_dimreg_to_be_changed().make_slot()
    );
    mainwindow->signal_dimreg_changed().connect(
        gigedit->signal_dimreg_changed().make_slot()
    );
    mainwindow->signal_sample_ref_changed().connect(
        gigedit->signal_sample_ref_changed().make_slot()
    );
}

int GigEdit::run() {
    __init_app();
    MainWindow window;
    __connect_signals(this, &window);
    kit.run(window);
    return 0;
}

int GigEdit::run(const char* pFileName) {
    __init_app();
    MainWindow window;
    __connect_signals(this, &window);
    if (pFileName) window.load_file(pFileName);
    kit.run(window);
    return 0;
}

int GigEdit::run(gig::Instrument* pInstrument) {
    __init_app();
    MainWindow window;
    __connect_signals(this, &window);
    if (pInstrument) window.load_instrument(pInstrument);
    kit.run(window);
    return 0;
}

sigc::signal<void, gig::File*>& GigEdit::signal_file_structure_to_be_changed() {
    return file_structure_to_be_changed_signal;
}

sigc::signal<void, gig::File*>& GigEdit::signal_file_structure_changed() {
    return file_structure_changed_signal;
}

sigc::signal<void, std::list<gig::Sample*> >& GigEdit::signal_samples_to_be_removed() {
    return samples_to_be_removed_signal;
}

sigc::signal<void>& GigEdit::signal_samples_removed() {
    return samples_removed_signal;
}

sigc::signal<void, gig::Region*>& GigEdit::signal_region_to_be_changed() {
    return region_to_be_changed_signal;
}

sigc::signal<void, gig::Region*>& GigEdit::signal_region_changed() {
    return region_changed_signal;
}

sigc::signal<void, gig::DimensionRegion*>& GigEdit::signal_dimreg_to_be_changed() {
    return dimreg_to_be_changed_signal;
}

sigc::signal<void, gig::DimensionRegion*>& GigEdit::signal_dimreg_changed() {
    return dimreg_changed_signal;
}

sigc::signal<void, gig::Sample*/*old*/, gig::Sample*/*new*/>& GigEdit::signal_sample_ref_changed() {
    return sample_ref_changed_signal;
}
