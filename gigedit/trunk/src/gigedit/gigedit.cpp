/*
 * Copyright (C) 2007-2009 Andreas Persson
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

#include <glibmm/dispatcher.h>
#include <glibmm/main.h>
#include <gtkmm/main.h>

#include "mainwindow.h"

#include "global.h"

namespace {

// State for a gigedit thread.
//
// This class is only used when gigedit is run as a plugin and makes
// sure that there's only one Gtk::Main event loop. The event loop is
// started in a separate thread. The plugin thread just dispatches an
// event to the main loop to open a window and then goes to sleep
// until the window is closed.
//
class GigEditState : public sigc::trackable {
public:
    GigEditState(GigEdit* parent) : parent(parent) { }
    void run(gig::Instrument* pInstrument);

    MainWindow* window;

private:

    // simple condition variable abstraction
    class Cond {
    private:
        bool pred;
        Glib::Threads::Mutex mutex;
        Glib::Threads::Cond cond;
    public:
        Cond() : pred(false) { }
        void signal() {
            Glib::Threads::Mutex::Lock lock(mutex);
            pred = true;
            cond.signal();
        }
        void wait() {
            Glib::Threads::Mutex::Lock lock(mutex);
            while (!pred) cond.wait(mutex);
        }
    };

#ifdef OLD_THREADS
    static Glib::StaticMutex mutex;
#else
    static Glib::Threads::Mutex mutex;
#endif
    static Glib::Dispatcher* dispatcher;
    static GigEditState* current;

    static void main_loop_run(Cond* intialized);
    static void open_window_static();

    GigEdit* parent;
    Cond open;
    Cond close;
    gig::Instrument* instrument;

    void open_window();
    void close_window();
};

#ifdef WIN32
HINSTANCE gigedit_dll_handle = 0;
#endif

void init_app() {
    static bool process_initialized = false;
    if (!process_initialized) {
        std::cout << "Initializing 3rd party services needed by gigedit.\n"
                  << std::flush;
        setlocale(LC_ALL, "");

#if HAVE_GETTEXT

#ifdef WIN32
#if GLIB_CHECK_VERSION(2, 16, 0)
        gchar* root =
            g_win32_get_package_installation_directory_of_module(gigedit_dll_handle);
#else
        gchar* root =
            g_win32_get_package_installation_directory(NULL, NULL);
#endif
        gchar* temp = g_build_filename(root, "/share/locale", NULL);
        g_free(root);
        gchar* localedir = g_win32_locale_filename_from_utf8(temp);
        g_free(temp);
        bindtextdomain(GETTEXT_PACKAGE, localedir);
        g_free(localedir);
#else
        bindtextdomain(GETTEXT_PACKAGE, LOCALEDIR);
#endif
        bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
        textdomain(GETTEXT_PACKAGE);
#endif // HAVE_GETTEXT

#ifdef OLD_THREADS
        // make sure thread_init() is called once and ONLY once per process
        if (!Glib::thread_supported()) Glib::thread_init();
#endif
        process_initialized = true;
    }
}

void connect_signals(GigEdit* gigedit, MainWindow* mainwindow) {
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
    mainwindow->signal_sample_changed().connect(
        gigedit->signal_sample_changed().make_slot()
    );
    mainwindow->signal_sample_ref_changed().connect(
        gigedit->signal_sample_ref_changed().make_slot()
    );
    mainwindow->signal_keyboard_key_hit().connect(
        gigedit->signal_keyboard_key_hit().make_slot()
    );
    mainwindow->signal_keyboard_key_released().connect(
        gigedit->signal_keyboard_key_released().make_slot()
    );
}

} // namespace

GigEdit::GigEdit() {
    state = NULL;
}

int GigEdit::run(int argc, char* argv[]) {
    init_app();

    Gtk::Main kit(argc, argv);
    MainWindow window;
    connect_signals(this, &window);
    if (argc >= 2) window.load_file(argv[1]);
    kit.run(window);
    return 0;
}

int GigEdit::run(gig::Instrument* pInstrument) {
    init_app();

    GigEditState state(this);
    this->state = &state;
    state.run(pInstrument);
    this->state = NULL;
    return 0;
}

void GigEdit::on_note_on_event(int key, int velocity) {
    if (!this->state) return;
    GigEditState* state = (GigEditState*) this->state;
    state->window->signal_note_on().emit(key, velocity);
}

void GigEdit::on_note_off_event(int key, int velocity) {
    if (!this->state) return;
    GigEditState* state = (GigEditState*) this->state;
    state->window->signal_note_off().emit(key, velocity);
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

sigc::signal<void, gig::Sample*>& GigEdit::signal_sample_changed() {
    return sample_changed_signal;
}

sigc::signal<void, gig::Sample*/*old*/, gig::Sample*/*new*/>& GigEdit::signal_sample_ref_changed() {
    return sample_ref_changed_signal;
}

sigc::signal<void, int/*key*/, int/*velocity*/>& GigEdit::signal_keyboard_key_hit() {
    return keyboard_key_hit_signal;
}

sigc::signal<void, int/*key*/, int/*velocity*/>& GigEdit::signal_keyboard_key_released() {
    return keyboard_key_released_signal;
}

#ifdef OLD_THREADS
Glib::StaticMutex GigEditState::mutex = GLIBMM_STATIC_MUTEX_INIT;
#else
Glib::Threads::Mutex GigEditState::mutex;
#endif
Glib::Dispatcher* GigEditState::dispatcher = 0;
GigEditState* GigEditState::current = 0;

void GigEditState::open_window_static() {
    GigEditState* c = GigEditState::current;
    c->open.signal();
    c->open_window();
}

void GigEditState::open_window() {
    window = new MainWindow();

    connect_signals(parent, window);
    if (instrument) window->load_instrument(instrument);

    window->signal_hide().connect(sigc::mem_fun(this,
                                                &GigEditState::close_window));
    window->present();
}

void GigEditState::close_window() {
    delete window;
    close.signal();
}

void GigEditState::main_loop_run(Cond* initialized) {
    int argc = 1;
    const char* argv_c[] = { "gigedit" };
    char** argv = const_cast<char**>(argv_c);
    Gtk::Main main_loop(argc, argv);

    dispatcher = new Glib::Dispatcher();
    dispatcher->connect(sigc::ptr_fun(&GigEditState::open_window_static));
    initialized->signal();

    main_loop.run();
}

void GigEditState::run(gig::Instrument* pInstrument) {
    mutex.lock(); // lock access to static variables

    static bool main_loop_started = false;
    if (!main_loop_started) {
        Cond initialized;
        Glib::Threads::Thread::create(
            sigc::bind(sigc::ptr_fun(&GigEditState::main_loop_run),
                       &initialized),
            false);
        initialized.wait();
        main_loop_started = true;
    }
    instrument = pInstrument;
    current = this;
    dispatcher->emit();
    open.wait(); // wait until the GUI thread has read current
    mutex.unlock();
    close.wait(); // sleep until window is closed
}

#if defined(WIN32)
extern "C" {
    BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
    {
        switch (reason) {
        case DLL_PROCESS_ATTACH:
            gigedit_dll_handle = instance;
            break;
        }
        return TRUE;
    }
}
#endif
