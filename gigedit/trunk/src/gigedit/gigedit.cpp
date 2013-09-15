/*
 * Copyright (C) 2007-2013 Andreas Persson
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

#if defined(__APPLE__)
# include <CoreFoundation/CoreFoundation.h>
# include "MacHelper.h"
#endif

#include "mainwindow.h"

#include "global.h"

#ifdef __APPLE__
#include <dlfcn.h>
#include <glibmm/fileutils.h>
#include <glibmm/miscutils.h>
#endif

//TODO: (hopefully) just a temporary nasty hack for launching gigedit on the main thread on Mac (see comments below in this file for details)
#if defined(__APPLE__) // the following global external variables are defined in LinuxSampler's global_private.cpp ...
extern bool g_mainThreadCallbackSupported;
extern void (*g_mainThreadCallback)(void* info);
extern void* g_mainThreadCallbackInfo;
extern bool g_fireMainThreadCallback;
#endif

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
    Cond initialized;
    gig::Instrument* instrument;

    void open_window();
    void close_window();
#if defined(__APPLE__)
    static void runInCFMainLoop(void* info);
#endif
};

#ifdef WIN32
HINSTANCE gigedit_dll_handle = 0;
#endif

#ifdef __APPLE__
std::string gigedit_localedir;
#endif

void init_app() {
    static bool process_initialized = false;
    if (!process_initialized) {
        std::cout << "Initializing 3rd party services needed by gigedit.\n"
                  << std::flush;
        setlocale(LC_ALL, "");

#ifdef __APPLE__
        // Look for pango.modules, gdk-pixbuf.loaders and locale files
        // under the same dir as the gigedit dylib is installed in.
        Dl_info info;
        if (dladdr((void*)&init_app, &info)) {
            std::string libdir = Glib::path_get_dirname(info.dli_fname);

            if (Glib::getenv("PANGO_SYSCONFDIR") == "" &&
                Glib::file_test(Glib::build_filename(libdir,
                                                     "pango/pango.modules"),
                                Glib::FILE_TEST_EXISTS)) {
                Glib::setenv("PANGO_SYSCONFDIR", libdir, true);
            }
            if (Glib::getenv("GDK_PIXBUF_MODULE_FILE") == "") {
                std::string module_file =
                    Glib::build_filename(libdir,
                                         "gtk-2.0/gdk-pixbuf.loaders");
                if (Glib::file_test(module_file, Glib::FILE_TEST_EXISTS)) {
                    Glib::setenv("GDK_PIXBUF_MODULE_FILE", module_file, true);
                }
            }
  //FIXME: for some reason AC GETTEXT check fails on the Mac cross compiler?
  //#if HAVE_GETTEXT
            std::string localedir = Glib::build_filename(libdir, "locale");
            if (Glib::file_test(localedir, Glib::FILE_TEST_EXISTS)) {
                gigedit_localedir = localedir;
                bindtextdomain(GETTEXT_PACKAGE, gigedit_localedir.c_str());
            } else {
                bindtextdomain(GETTEXT_PACKAGE, LOCALEDIR);
            }
  //#endif
        }

        // The gtk file dialog stores its recent files state in
        // ~/.local/share
        g_mkdir_with_parents(
            Glib::build_filename(Glib::get_home_dir(),
                                 ".local/share").c_str(), 0777);
#endif // __APPLE__

//FIXME: for some reason AC GETTEXT check fails on the Mac cross compiler?
#if (HAVE_GETTEXT || defined(__APPLE__))

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
  #elif !defined(__APPLE__)
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

//FIXME: for some reason AC GETTEXT check fails on the Mac cross compiler?
#if (/*HAVE_GETTEXT &&*/ defined(__APPLE__))
    // Gtk::Main binds the gtk locale to a possible non-existent
    // directory. If we have bundled gtk locale files, we rebind here,
    // after the Gtk::Main constructor.
    if (!gigedit_localedir.empty()) {
        bindtextdomain("gtk20", gigedit_localedir.c_str());
    }
#endif

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
//FIXME: for some reason AC GETTEXT check fails on the Mac cross compiler?
#if (/*HAVE_GETTEXT &&*/ defined(__APPLE__))
    if (!gigedit_localedir.empty()) {
        bindtextdomain("gtk20", gigedit_localedir.c_str());
    }
#endif

    dispatcher = new Glib::Dispatcher();
    dispatcher->connect(sigc::ptr_fun(&GigEditState::open_window_static));
    initialized->signal();

    main_loop.run();
}

#if defined(__APPLE__)

void GigEditState::runInCFMainLoop(void* info) {
    printf("runInCFMainLoop() entered\n"); fflush(stdout);
    GigEditState* state = static_cast<GigEditState*>(info);
    state->main_loop_run(
        &state->initialized
    );
    printf("runInCFMainLoop() left\n"); fflush(stdout);
}

#endif // __APPLE__

void GigEditState::run(gig::Instrument* pInstrument) {
    mutex.lock(); // lock access to static variables

    static bool main_loop_started = false;
    if (!main_loop_started) {
#if defined(__APPLE__)
        // spawn GUI on main thread :
        //     On OS X the Gtk GUI can only be launched on a process's "main"
        //     thread. When trying to launch the Gtk GUI on any other thread,
        //     there will only be a white box, because the GUI would not receive
        //     any events, since it would listen to the wrong system event loop.
        //     So far we haven't investigated whether there is any kind of
        //     circumvention to allow doing that also on other OS X threads.
        {
            // In case the sampler was launched as standalone sampler (not as
            // plugin), use the following global callback variable hack ...
            if (g_mainThreadCallbackSupported) {
                printf("Setting callback ...\n"); fflush(stdout);
                g_mainThreadCallback = runInCFMainLoop;
                g_mainThreadCallbackInfo = this;
                g_fireMainThreadCallback = true;
                printf("Callback variables set.\n"); fflush(stdout);
            } else { // Sampler was launched as (i.e. AU / VST) plugin ...
                // When the sampler was launched as plugin, we have no idea
                // whether any sampler thread is the process's "main" thread.
                // So that's why we are trying to use Apple's API for trying to
                // launch our callback function on the process's main thread.
                // However this will only work, if the plugin host application
                // established a CF event loop, that is if the application is
                // using Cocoa for its GUI. For other host applications the
                // callback will never be executed and thus gigedit would not
                // popup.
                
                // should be pretty much the same as the Objective-C solution below with macHelperRunCFuncOnMainThread()
                /*CFRunLoopSourceContext sourceContext = CFRunLoopSourceContext();
                sourceContext.info = this;
                sourceContext.perform = runInCFMainLoop;
                printf("CFRunLoopSourceCreate\n"); fflush(stdout);
                CFRunLoopSourceRef source = CFRunLoopSourceCreate(
                    kCFAllocatorDefault, // allocator
                    1, // priority
                    &sourceContext
                );
                printf("CFRunLoopAddSource\n"); fflush(stdout);
                CFRunLoopAddSource(CFRunLoopGetMain(), source, kCFRunLoopDefaultMode);
                CFRelease(source);*/
                
                // use Apple's Objective-C API to call our callback function
                // 'runInCFMainLoop()' on the process's "main" thread
                macHelperRunCFuncOnMainThread(runInCFMainLoop, this);
            }
        }
#else
  #ifdef OLD_THREADS
        Glib::Thread::create(
            sigc::bind(sigc::ptr_fun(&GigEditState::main_loop_run),
                       &initialized),
            false);
  #else
        Glib::Threads::Thread::create(
            sigc::bind(sigc::ptr_fun(&GigEditState::main_loop_run),
                       &initialized));
  #endif
#endif
        printf("Waiting for GUI being initialized (on main thread) ....\n"); fflush(stdout);
        initialized.wait();
        printf("GUI is now initialized. Everything done.\n"); fflush(stdout);
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
