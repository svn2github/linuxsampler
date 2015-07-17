/*
    Copyright (c) 2014 Christian Schoenebeck
    
    This file is part of "gigedit" and released under the terms of the
    GNU General Public License version 2.
*/

#ifndef GIGEDIT_SCRIPTEDITOR_H
#define GIGEDIT_SCRIPTEDITOR_H

#include <gig.h>
#include <gtkmm.h>

#include "compat.h"

class ScriptEditor : public Gtk::Window {
public:
    ScriptEditor();
   ~ScriptEditor();
    void setScript(gig::Script* script);
protected:
    Gtk::VBox m_vbox;
    Gtk::HButtonBox m_buttonBox;
    Gtk::ScrolledWindow m_scrolledWindow;
    Glib::RefPtr<Gtk::TextBuffer> m_textBuffer;
    Glib::RefPtr<Gtk::TextBuffer::TagTable> m_tagTable;
    Glib::RefPtr<Gtk::TextBuffer::Tag> m_keywordTag;
    Glib::RefPtr<Gtk::TextBuffer::Tag> m_eventTag;
    Gtk::TextView m_textView;
    Gtk::Button m_applyButton;
    Gtk::Button m_cancelButton;

    gig::Script* m_script;
    
    void onButtonCancel();
    void onButtonApply();
    void onWindowHide();
    void onTextInserted(const Gtk::TextBuffer::iterator& it, const Glib::ustring& txt, int length);
    void onTextErased(const Gtk::TextBuffer::iterator& itStart, const Gtk::TextBuffer::iterator& itEnd);
    void onModifiedChanged();
};

#endif // GIGEDIT_SCRIPTEDITOR_H
