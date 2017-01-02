/*
    Copyright (c) 2014-2017 Christian Schoenebeck
    
    This file is part of "gigedit" and released under the terms of the
    GNU General Public License version 2.
*/

#ifndef GIGEDIT_SCRIPTEDITOR_H
#define GIGEDIT_SCRIPTEDITOR_H

#ifdef LIBGIG_HEADER_FILE
# include LIBGIG_HEADER_FILE(gig.h)
#else
# include <gig.h>
#endif

#include <gtkmm.h>
#if HAVE_CONFIG_H
# include <config.h>
#endif
#include "compat.h"
#include <gtkmm/uimanager.h>
#include <gtkmm/actiongroup.h>
#include "ManagedWindow.h"

// Should we use a very simple (and buggy) local NKSP syntax parser, or should
// we rather use the full featured NKSP syntax highlighting backend from
// liblinuxsampler for syntax highlighting of this text editor?
#if HAVE_LINUXSAMPLER
# define USE_LS_SCRIPTVM 1
#endif

#if USE_LS_SCRIPTVM
# ifdef LIBLINUXSAMPLER_HEADER_FILE
#  include LIBLINUXSAMPLER_HEADER_FILE(scriptvm/ScriptVM.h)
#  include LIBLINUXSAMPLER_HEADER_FILE(scriptvm/ScriptVMFactory.h)
# else
#  include <linuxsampler/scriptvm/ScriptVM.h>
#  include <linuxsampler/scriptvm/ScriptVMFactory.h>
# endif
#endif

class ScriptEditor : public ManagedWindow {
public:
    ScriptEditor();
   ~ScriptEditor();
    void setScript(gig::Script* script);

    sigc::signal<void, gig::Script*> signal_script_to_be_changed;
    sigc::signal<void, gig::Script*> signal_script_changed;

    // implementation for abstract methods of interface class "ManagedWindow"
    virtual Settings::Property<int>* windowSettingX() { return &Settings::singleton()->scriptEditorWindowX; }
    virtual Settings::Property<int>* windowSettingY() { return &Settings::singleton()->scriptEditorWindowY; }
    virtual Settings::Property<int>* windowSettingWidth() { return &Settings::singleton()->scriptEditorWindowW; }
    virtual Settings::Property<int>* windowSettingHeight() { return &Settings::singleton()->scriptEditorWindowH; }

protected:
    Gtk::VBox m_vbox;
    Gtk::HBox m_footerHBox;
    Gtk::HBox m_statusHBox;
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
    Gtk::TextView m_textView;
    Gtk::Image m_statusImage;
    Gtk::Label m_statusLabel;
    Gtk::Button m_applyButton;
    Gtk::Button m_cancelButton;

    Glib::RefPtr<Gdk::Pixbuf> m_warningIcon;
    Glib::RefPtr<Gdk::Pixbuf> m_errorIcon;
    Glib::RefPtr<Gdk::Pixbuf> m_successIcon;

    Glib::RefPtr<Gtk::ActionGroup> m_actionGroup;
    Glib::RefPtr<Gtk::UIManager> m_uiManager;

    gig::Script* m_script;
#if USE_LS_SCRIPTVM
    LinuxSampler::ScriptVM* m_vm;
    std::vector<LinuxSampler::ParserIssue> m_issues;
    std::vector<LinuxSampler::ParserIssue> m_errors;
    std::vector<LinuxSampler::ParserIssue> m_warnings;
#endif

    bool isModified() const;
    void onButtonCancel();
    void onButtonApply();
    void onWindowHide();
    void onTextInserted(const Gtk::TextBuffer::iterator& it, const Glib::ustring& txt, int length);
    void onTextErased(const Gtk::TextBuffer::iterator& itStart, const Gtk::TextBuffer::iterator& itEnd);
    void onModifiedChanged();
#if USE_LS_SCRIPTVM
    void updateSyntaxHighlightingByVM();
    void updateParserIssuesByVM();
    LinuxSampler::ScriptVM* GetScriptVM();
    void updateIssueTooltip(GdkEventMotion* e);
    void updateStatusBar();
#endif
    bool on_motion_notify_event(GdkEventMotion* e);
    bool onWindowDelete(GdkEventAny* e);
    void onMenuChangeFontSize();
    int  currentFontSize() const;
    void setFontSize(int size, bool save);
};

#endif // GIGEDIT_SCRIPTEDITOR_H
