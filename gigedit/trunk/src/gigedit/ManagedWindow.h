/*
    Copyright (c) 2016 Christian Schoenebeck
    
    This file is part of "gigedit" and released under the terms of the
    GNU General Public License version 2.
*/

#ifndef MANAGED_WINDOW_H
#define MANAGED_WINDOW_H

#include <glibmm/object.h>
#include <gtkmm/window.h>
#include <glibmm/main.h>
#include "Settings.h"

/** @brief Base class intended to be used for all gigedit Windows.
 *
 * This class aims to provide common functionalities for all Windows of the
 * gigedit application. So usually all gigedit Windows should derive from this
 * class.
 *
 * Currently this class only automatically saves and restores the user's
 * preference for the respective Windows position on the screen and size of the
 * window. It saves the position and dimensions automatically as soon as the
 * user moves or resizes the window. And it automatically restores the window's
 * position and size when it is created.
 */
class ManagedWindow : public Gtk::Window {
public:
    ManagedWindow();

    // following methods must be implemented by deriving class
    virtual Settings::Property<int>* windowSettingX() = 0;
    virtual Settings::Property<int>* windowSettingY() = 0;
    virtual Settings::Property<int>* windowSettingWidth() = 0;
    virtual Settings::Property<int>* windowSettingHeight() = 0;

protected:
    bool on_configure_event(GdkEventConfigure* e);
    void enableListeningConfigureEvents() { m_listenOnConfigureEvents = true; }
    bool saveWindowDimensions(int x, int y, int w, int h);
    void restoreWindowDimensions();
private:
    Gtk::Window* m_window;
    bool m_listenOnConfigureEvents;
    Glib::RefPtr<Glib::TimeoutSource> m_eventThrottleTimer;
};

#endif // MANAGED_WINDOW_H