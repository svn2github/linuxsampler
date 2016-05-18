/*
    Copyright (c) 2016 Christian Schoenebeck
    
    This file is part of "gigedit" and released under the terms of the
    GNU General Public License version 2.
*/

#include "ManagedWindow.h"
#include <typeinfo>
#include <glib.h>
#include "global.h"

///////////////////////////////////////////////////////////////////////////
// class 'ManagedWindow'

ManagedWindow::ManagedWindow() : m_listenOnConfigureEvents(false)
{
    if (!Settings::singleton()->autoRestoreWindowDimension)
        return;

    Glib::signal_idle().connect_once( // timeout starts given amount of ms after the main loop became idle again ...
        sigc::mem_fun(*this, &ManagedWindow::restoreWindowDimensions),
        0
    );
    //HACK: Gtk does not support to distinguish between user caused window resize/move and programmtical window resize/move, so as a workaround we ignore such events for a certain amount of time while this window is constructing
    Glib::signal_idle().connect_once( // timeout starts given amount of ms after the main loop became idle again ...
        sigc::mem_fun(*this, &ManagedWindow::enableListeningConfigureEvents),
        300
    );
}

bool ManagedWindow::on_configure_event(GdkEventConfigure* e) {
    //printf("on_configure_event x=%d y=%d w=%d h=%d\n", e->x, e->y, e->width, e->height);
    if (m_listenOnConfigureEvents) {
        //printf("reset event throttle timer\n");
        // invalidate timer (so it won't fire)
        if (m_eventThrottleTimer) m_eventThrottleTimer->destroy();
        // restart timer
        m_eventThrottleTimer = Glib::TimeoutSource::create(300);
        m_eventThrottleTimer->connect(
            sigc::bind(
                sigc::bind(
                    sigc::bind(
                        sigc::bind(
                            sigc::mem_fun(*this, &ManagedWindow::saveWindowDimensions),
                            e->height
                        ),
                        e->width
                    ),
                    e->y
                ),
                e->x
            )
        );
        m_eventThrottleTimer->attach(Glib::MainContext::get_default());
    }
    return Gtk::Window::on_configure_event(e);
}

bool ManagedWindow::saveWindowDimensions(int x, int y, int w, int h) {
    printf("saveWindowDimensions(%d,%d,%d,%d)\n",x,y,w,h);
    if (*windowSettingX() != x) *windowSettingX() = x;
    if (*windowSettingY() != y) *windowSettingY() = y;
    if (*windowSettingWidth() != w) *windowSettingWidth() = w;
    if (*windowSettingHeight() != h) *windowSettingHeight() = h;
    return false; // kill timeout which called this method
}

void ManagedWindow::restoreWindowDimensions() {
    int x = *windowSettingX();
    int y = *windowSettingY();
    int w = *windowSettingWidth();
    int h = *windowSettingHeight();
    printf("restoreWindowDimensions(%d,%d,%d,%d)\n",x,y,w,h);
    if (x >= 0 && y >= 0) move(x, y);
    if (w > 0 && h > 0) resize(w, h);
}

///////////////////////////////////////////////////////////////////////////
// class 'ManagedDialog'

ManagedDialog::ManagedDialog()
    : Gtk::Dialog(), m_listenOnConfigureEvents(false)
{
    initManagedDialog();
}

ManagedDialog::ManagedDialog(const Glib::ustring& title, bool modal)
    : Gtk::Dialog(title, modal), m_listenOnConfigureEvents(false)
{
    initManagedDialog();
}

ManagedDialog::ManagedDialog(const Glib::ustring& title, Gtk::Window& parent, bool modal)
    : Gtk::Dialog(title, parent, modal), m_listenOnConfigureEvents(false)
{
    initManagedDialog();
}

// ManagedDialog::ManagedDialog(const Glib::ustring& title, Gtk::DialogFlags flags)
//     : Gtk::Dialog(title, flags), m_listenOnConfigureEvents(false)
// {
//     initManagedDialog();
// }

void ManagedDialog::initManagedDialog() {
    if (!Settings::singleton()->autoRestoreWindowDimension)
        return;

    Glib::signal_idle().connect_once( // timeout starts given amount of ms after the main loop became idle again ...
        sigc::mem_fun(*this, &ManagedDialog::restoreWindowDimensions),
        0
    );
    //HACK: Gtk does not support to distinguish between user caused window resize/move and programmtical window resize/move, so as a workaround we ignore such events for a certain amount of time while this window is constructing
    Glib::signal_idle().connect_once( // timeout starts given amount of ms after the main loop became idle again ...
        sigc::mem_fun(*this, &ManagedDialog::enableListeningConfigureEvents),
        300
    );
}

bool ManagedDialog::on_configure_event(GdkEventConfigure* e) {
    //printf("on_configure_event x=%d y=%d w=%d h=%d\n", e->x, e->y, e->width, e->height);
    if (m_listenOnConfigureEvents) {
        //printf("reset event throttle timer\n");
        // invalidate timer (so it won't fire)
        if (m_eventThrottleTimer) m_eventThrottleTimer->destroy();
        // restart timer
        m_eventThrottleTimer = Glib::TimeoutSource::create(300);
        m_eventThrottleTimer->connect(
            sigc::bind(
                sigc::bind(
                    sigc::bind(
                        sigc::bind(
                            sigc::mem_fun(*this, &ManagedDialog::saveWindowDimensions),
                            e->height
                        ),
                        e->width
                    ),
                    e->y
                ),
                e->x
            )
        );
        m_eventThrottleTimer->attach(Glib::MainContext::get_default());
    }
    return Gtk::Dialog::on_configure_event(e);
}

bool ManagedDialog::saveWindowDimensions(int x, int y, int w, int h) {
    printf("saveDialogDimensions(%d,%d,%d,%d)\n",x,y,w,h);
    if (*windowSettingX() != x) *windowSettingX() = x;
    if (*windowSettingY() != y) *windowSettingY() = y;
    if (*windowSettingWidth() != w) *windowSettingWidth() = w;
    if (*windowSettingHeight() != h) *windowSettingHeight() = h;
    return false; // kill timeout which called this method
}

void ManagedDialog::restoreWindowDimensions() {
    int x = *windowSettingX();
    int y = *windowSettingY();
    int w = *windowSettingWidth();
    int h = *windowSettingHeight();
    printf("restoreDialogDimensions(%d,%d,%d,%d)\n",x,y,w,h);
    if (x >= 0 && y >= 0) move(x, y);
    if (w > 0 && h >= 0) resize(w, h);
}
