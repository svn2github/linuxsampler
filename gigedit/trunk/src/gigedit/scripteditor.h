/*
    Copyright (c) 2014-2016 Christian Schoenebeck
    
    This file is part of "gigedit" and released under the terms of the
    GNU General Public License version 2.
*/

#ifndef GIGEDIT_SCRIPTEDITOR_H
#define GIGEDIT_SCRIPTEDITOR_H

#include <gig.h>
#include <gtkmm.h>
#include <config.h>

#include "compat.h"

// Should we use a very simple (and buggy) local NKSP syntax parser, or should
// we rather use the full features NKSP syntax highlighting backend from
// liblinuxsampler for syntax highlighting of this text editor?
#if HAVE_LINUXSAMPLER
# define USE_LS_SCRIPTVM 1
#endif

#if USE_LS_SCRIPTVM
namespace LinuxSampler {
    class ScriptVM;
}
#endif

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
    Glib::RefPtr<Gtk::TextBuffer::Tag> m_variableTag;
    Glib::RefPtr<Gtk::TextBuffer::Tag> m_functionTag;
    Glib::RefPtr<Gtk::TextBuffer::Tag> m_numberTag;
    Glib::RefPtr<Gtk::TextBuffer::Tag> m_stringTag;
    Glib::RefPtr<Gtk::TextBuffer::Tag> m_commentTag;
    Glib::RefPtr<Gtk::TextBuffer::Tag> m_preprocTag;
    Gtk::TextView m_textView;
    Gtk::Button m_applyButton;
    Gtk::Button m_cancelButton;

    gig::Script* m_script;
#if USE_LS_SCRIPTVM
    LinuxSampler::ScriptVM* m_vm;
#endif

    void onButtonCancel();
    void onButtonApply();
    void onWindowHide();
    void onTextInserted(const Gtk::TextBuffer::iterator& it, const Glib::ustring& txt, int length);
    void onTextErased(const Gtk::TextBuffer::iterator& itStart, const Gtk::TextBuffer::iterator& itEnd);
    void onModifiedChanged();
#if USE_LS_SCRIPTVM
    void updateSyntaxHighlightingByVM();
#endif
};

#endif // GIGEDIT_SCRIPTEDITOR_H
