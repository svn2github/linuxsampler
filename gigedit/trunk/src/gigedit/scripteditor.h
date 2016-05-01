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
#include "ManagedWindow.h"

// Should we use a very simple (and buggy) local NKSP syntax parser, or should
// we rather use the full features NKSP syntax highlighting backend from
// liblinuxsampler for syntax highlighting of this text editor?
#if HAVE_LINUXSAMPLER
# define USE_LS_SCRIPTVM 1
#endif

#if USE_LS_SCRIPTVM
# include <linuxsampler/scriptvm/ScriptVM.h>
# include <linuxsampler/scriptvm/ScriptVMFactory.h>
#endif

class ScriptEditor : public ManagedWindow {
public:
    ScriptEditor();
   ~ScriptEditor();
    void setScript(gig::Script* script);

    // implementation for abstract methods of interface class "ManagedWindow"
    virtual Settings::Property<int>* windowSettingX() { return &Settings::singleton()->scriptEditorWindowX; }
    virtual Settings::Property<int>* windowSettingY() { return &Settings::singleton()->scriptEditorWindowY; }
    virtual Settings::Property<int>* windowSettingWidth() { return &Settings::singleton()->scriptEditorWindowW; }
    virtual Settings::Property<int>* windowSettingHeight() { return &Settings::singleton()->scriptEditorWindowH; }

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
    Glib::RefPtr<Gtk::TextBuffer::Tag> m_errorTag;
    Glib::RefPtr<Gtk::TextBuffer::Tag> m_warningTag;
    Glib::RefPtr<Gtk::TextBuffer::Tag> m_readOnlyTag;
    Gtk::TextView m_textView;
    Gtk::Button m_applyButton;
    Gtk::Button m_cancelButton;

    gig::Script* m_script;
#if USE_LS_SCRIPTVM
    LinuxSampler::ScriptVM* m_vm;
    std::vector<LinuxSampler::ParserIssue> m_issues;
#endif

    bool m_ignoreEraseEvents;

    void onButtonCancel();
    void onButtonApply();
    void onWindowHide();
    void onTextInserted(const Gtk::TextBuffer::iterator& it, const Glib::ustring& txt, int length);
    void onTextErased(const Gtk::TextBuffer::iterator& itStart, const Gtk::TextBuffer::iterator& itEnd);
    void onModifiedChanged();
#if USE_LS_SCRIPTVM
    void removeIssueAnchors();
    void updateSyntaxHighlightingByVM();
    void updateParserIssuesByVM();
    LinuxSampler::ScriptVM* GetScriptVM();
#endif
};

#endif // GIGEDIT_SCRIPTEDITOR_H
