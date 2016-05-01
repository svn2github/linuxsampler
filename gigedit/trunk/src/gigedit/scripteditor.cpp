/*
    Copyright (c) 2014-2016 Christian Schoenebeck
    
    This file is part of "gigedit" and released under the terms of the
    GNU General Public License version 2.
*/

#include "scripteditor.h"
#include "global.h"

#if !USE_LS_SCRIPTVM

static const std::string _keywords[] = {
    "on", "end", "declare", "while", "if", "or", "and", "not", "else", "case",
    "select", "to", "const", "polyphonic", "mod"
};
static int _keywordsSz = sizeof(_keywords) / sizeof(std::string);

static const std::string _eventNames[] = {
    "init", "note", "release", "controller"
};
static int _eventNamesSz = sizeof(_eventNames) / sizeof(std::string); 

static bool isKeyword(const Glib::ustring& s) {
    for (int i = 0; i < _keywordsSz; ++i)
        if (_keywords[i] == s) return true;
    return false;
}

static bool isEvent(const Glib::ustring& s) {
    for (int i = 0; i < _eventNamesSz; ++i)
        if (_eventNames[i] == s) return true;
    return false;
}

#endif // !USE_LS_SCRIPTVM

ScriptEditor::ScriptEditor() :
    m_applyButton(_("_Apply"), true),
    m_cancelButton(_("_Cancel"), true)
{
    m_script = NULL;
#if USE_LS_SCRIPTVM
    m_vm = NULL;
#endif
    m_ignoreEraseEvents = false;

    add(m_vbox);

    m_tagTable = Gtk::TextBuffer::TagTable::create();

    m_keywordTag = Gtk::TextBuffer::Tag::create();
    m_keywordTag->property_foreground() = "#000000"; // black
    m_keywordTag->property_weight() = PANGO_WEIGHT_BOLD;
    m_tagTable->add(m_keywordTag);

    m_eventTag = Gtk::TextBuffer::Tag::create();
    m_eventTag->property_foreground() = "#07c0cf"; // cyan 1
    m_eventTag->property_weight() = PANGO_WEIGHT_BOLD;
    m_tagTable->add(m_eventTag);
    
    m_variableTag = Gtk::TextBuffer::Tag::create();
    m_variableTag->property_foreground() = "#790cc4"; // magenta
    m_tagTable->add(m_variableTag);
    
    m_functionTag = Gtk::TextBuffer::Tag::create();
    m_functionTag->property_foreground() = "#1ba1dd"; // cyan 2
    m_tagTable->add(m_functionTag);
    
    m_numberTag = Gtk::TextBuffer::Tag::create();
    m_numberTag->property_foreground() = "#c4950c"; // yellow
    m_tagTable->add(m_numberTag);

    m_stringTag = Gtk::TextBuffer::Tag::create();
    m_stringTag->property_foreground() = "#c40c0c"; // red
    m_tagTable->add(m_stringTag);

    m_commentTag = Gtk::TextBuffer::Tag::create();
    m_commentTag->property_foreground() = "#9c9c9c"; // gray
    m_tagTable->add(m_commentTag);

    m_preprocTag = Gtk::TextBuffer::Tag::create();
    m_preprocTag->property_foreground() = "#2f8a33"; // green
    m_tagTable->add(m_preprocTag);

    m_errorTag = Gtk::TextBuffer::Tag::create();
    m_errorTag->property_background() = "#ff9393"; // red
    m_tagTable->add(m_errorTag);

    m_warningTag = Gtk::TextBuffer::Tag::create();
    m_warningTag->property_background() = "#fffd7c"; // yellow
    m_tagTable->add(m_warningTag);

    m_readOnlyTag = Gtk::TextBuffer::Tag::create();
    m_readOnlyTag->property_editable() = false;
    m_tagTable->add(m_readOnlyTag);

    m_textBuffer = Gtk::TextBuffer::create(m_tagTable);
    m_textView.set_buffer(m_textBuffer);
    {
        Pango::FontDescription fdesc;
        fdesc.set_family("monospace");
#if defined(__APPLE__)
        fdesc.set_size(12 * PANGO_SCALE);
#else
        fdesc.set_size(10 * PANGO_SCALE);
#endif
#if GTKMM_MAJOR_VERSION < 3
        m_textView.modify_font(fdesc);
#else
        m_textView.override_font(fdesc);
#endif
    }
    m_scrolledWindow.add(m_textView);
    m_scrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    m_vbox.pack_start(m_scrolledWindow);

    m_buttonBox.set_layout(Gtk::BUTTONBOX_END);
    m_buttonBox.pack_start(m_applyButton);
    m_buttonBox.pack_start(m_cancelButton);
    m_applyButton.set_can_default();
    m_applyButton.set_sensitive(false);
    m_applyButton.grab_focus();
    m_vbox.pack_start(m_buttonBox, Gtk::PACK_SHRINK);

    m_applyButton.signal_clicked().connect(
        sigc::mem_fun(*this, &ScriptEditor::onButtonApply)
    );

    m_cancelButton.signal_clicked().connect(
        sigc::mem_fun(*this, &ScriptEditor::onButtonCancel)
    );
    
    m_textBuffer->signal_insert().connect(
        sigc::mem_fun(*this, &ScriptEditor::onTextInserted)
    );
    
    m_textBuffer->signal_erase().connect(
        sigc::mem_fun(*this, &ScriptEditor::onTextErased)
    );
    
    m_textBuffer->signal_modified_changed().connect(
        sigc::mem_fun(*this, &ScriptEditor::onModifiedChanged)
    );
    
    signal_hide().connect(
        sigc::mem_fun(*this, &ScriptEditor::onWindowHide)
    );

    show_all_children();

    resize(460,300);
}

ScriptEditor::~ScriptEditor() {
    printf("ScriptEditor destruct\n");
#if USE_LS_SCRIPTVM
    if (m_vm) delete m_vm;
#endif
}

void ScriptEditor::setScript(gig::Script* script) {
    m_script = script;
    if (!script) {
        set_title(_("No Script"));
        return;
    }

    set_title(std::string(_("Instrument Script")) + " - \"" + script->Name + "\"");
    
    std::string txt = script->GetScriptAsText();
    //printf("text : '%s'\n", txt.c_str());
    m_textBuffer->set_text(txt);
    m_textBuffer->set_modified(false);
}

void ScriptEditor::onTextInserted(const Gtk::TextBuffer::iterator& itEnd, const Glib::ustring& txt, int length) {
    printf("onTextInserted()\n");
    fflush(stdout);
#if USE_LS_SCRIPTVM
    removeIssueAnchors();
    m_textBuffer->remove_all_tags(m_textBuffer->begin(), m_textBuffer->end());
    updateSyntaxHighlightingByVM();
    updateParserIssuesByVM();
#else
    //printf("inserted %d\n", length);
    Gtk::TextBuffer::iterator itStart = itEnd;
    itStart.backward_chars(length);

    Gtk::TextBuffer::iterator it = itStart;
    it.backward_word_start();

    bool eofReached = false;
    while (it <= itEnd) {
        Gtk::TextBuffer::iterator itWordStart = it;
        if (!it.forward_word_end()) {
            eofReached = true;
            it = itEnd;
        }

        Glib::ustring s = m_textBuffer->get_text(itWordStart, it, false);
        //printf("{%s}\n", s.c_str());
        if (isKeyword(s))
            m_textBuffer->apply_tag(m_keywordTag, itWordStart, it);
        else if (isEvent(s)) {
            // check if previous word is "on"
            Gtk::TextBuffer::iterator itPreviousWordStart = itWordStart;
            if (itPreviousWordStart.backward_word_start()) {
                Gtk::TextBuffer::iterator itPreviousWordEnd = itPreviousWordStart;
                itPreviousWordEnd.forward_word_end();
                if (m_textBuffer->get_text(itPreviousWordStart, itPreviousWordEnd, false) == "on") {
                    m_textBuffer->apply_tag(m_eventTag, itWordStart, it);
                }
            }
        }

        if (eofReached) break;

        while (!it.inside_word())
            if (!it.forward_char())
                goto EOF_REACHED;
    }
    
    EOF_REACHED:
    ;
    
#endif // USE_LS_SCRIPTVM
}

#if USE_LS_SCRIPTVM

LinuxSampler::ScriptVM* ScriptEditor::GetScriptVM() {
    if (!m_vm) m_vm = LinuxSampler::ScriptVMFactory::Create("gig");
    return m_vm;
}

static void applyCodeTag(Glib::RefPtr<Gtk::TextBuffer>& txtbuf, const LinuxSampler::VMSourceToken& token, Glib::RefPtr<Gtk::TextBuffer::Tag>& tag) {
    Gtk::TextBuffer::iterator itStart =
        txtbuf->get_iter_at_line_index(token.firstLine(), token.firstColumn());
    Gtk::TextBuffer::iterator itEnd = itStart;
    const int length = token.text().length();
    itEnd.forward_chars(length);
    txtbuf->apply_tag(tag, itStart, itEnd);
}

static void applyCodeTag(Glib::RefPtr<Gtk::TextBuffer>& txtbuf, const LinuxSampler::ParserIssue& issue, Glib::RefPtr<Gtk::TextBuffer::Tag>& tag) {
    Gtk::TextBuffer::iterator itStart =
        txtbuf->get_iter_at_line_index(issue.firstLine - 1, issue.firstColumn - 1);
    Gtk::TextBuffer::iterator itEnd = itStart;
    itEnd.forward_lines(issue.lastLine - issue.firstLine);
    itEnd.forward_chars(
        (issue.lastLine != issue.firstLine)
            ? issue.lastColumn - 1
            : issue.lastColumn - issue.firstColumn + 1
    );
    txtbuf->apply_tag(tag, itStart, itEnd);
}

void ScriptEditor::removeIssueAnchors() {
    m_ignoreEraseEvents = true; // avoid endless recursion
    
    for (int i = 0; i < m_issues.size(); ++i) {
        const LinuxSampler::ParserIssue& issue = m_issues[i];
        printf("erase anchor at l%d c%d\n", issue.firstLine - 1, issue.firstColumn - 1);
        fflush(stdout);
        Gtk::TextBuffer::iterator iter = m_textBuffer->get_iter_at_line_index(issue.firstLine - 1, issue.firstColumn - 1);
        Gtk::TextBuffer::iterator iterEnd = iter;
        iterEnd.forward_chars(1);
        m_textBuffer->erase(iter, iterEnd);
    }
    
    m_ignoreEraseEvents = false; // back to normal
}

void ScriptEditor::updateSyntaxHighlightingByVM() {
    GetScriptVM();
    const std::string s = m_textBuffer->get_text();
    std::vector<LinuxSampler::VMSourceToken> tokens = m_vm->syntaxHighlighting(s);

    for (int i = 0; i < tokens.size(); ++i) {
        const LinuxSampler::VMSourceToken& token = tokens[i];

        if (token.isKeyword()) {
            applyCodeTag(m_textBuffer, token, m_keywordTag);
        } else if (token.isVariableName()) {
            applyCodeTag(m_textBuffer, token, m_variableTag);
        } else if (token.isIdentifier()) {
            if (token.isEventHandlerName()) {
                applyCodeTag(m_textBuffer, token, m_eventTag);
            } else { // a function ...
                applyCodeTag(m_textBuffer, token, m_functionTag);
            }
        } else if (token.isNumberLiteral()) {
            applyCodeTag(m_textBuffer, token, m_numberTag);
        } else if (token.isStringLiteral()) {
            applyCodeTag(m_textBuffer, token, m_stringTag);
        } else if (token.isComment()) {
            applyCodeTag(m_textBuffer, token, m_commentTag);
        } else if (token.isPreprocessor()) {
            applyCodeTag(m_textBuffer, token, m_preprocTag);
        } else if (token.isNewLine()) {
        }
    }
}

static Glib::RefPtr<Gdk::Pixbuf> createIcon(std::string name, const Glib::RefPtr<Gdk::Screen>& screen) {
    const int targetH = 9;
    Glib::RefPtr<Gtk::IconTheme> theme = Gtk::IconTheme::get_for_screen(screen);
    int w = 0;
    int h = 0; // ignored
    Gtk::IconSize::lookup(Gtk::ICON_SIZE_SMALL_TOOLBAR, w, h);
    Glib::RefPtr<Gdk::Pixbuf> pixbuf = theme->load_icon(name, w, Gtk::ICON_LOOKUP_GENERIC_FALLBACK);
    if (pixbuf->get_height() != targetH) {
        pixbuf = pixbuf->scale_simple(targetH, targetH, Gdk::INTERP_BILINEAR);
    }
    return pixbuf;
}

void ScriptEditor::updateParserIssuesByVM() {
    GetScriptVM();
    const std::string s = m_textBuffer->get_text();
    LinuxSampler::VMParserContext* parserContext = m_vm->loadScript(s);
    m_issues = parserContext->issues();

    for (int i = 0; i < m_issues.size(); ++i) {
        const LinuxSampler::ParserIssue& issue = m_issues[i];

        if (issue.isErr()) {
            applyCodeTag(m_textBuffer, issue, m_errorTag);
        } else if (issue.isWrn()) {
            applyCodeTag(m_textBuffer, issue, m_warningTag);
        }
    }

    for (int i = m_issues.size() - 1; i >= 0; --i) {
        const LinuxSampler::ParserIssue& issue = m_issues[i];

        if (issue.isErr() || issue.isWrn()) {
            Glib::RefPtr<Gdk::Pixbuf> pixbuf = createIcon(issue.isErr() ? "dialog-error" : "dialog-warning-symbolic", get_screen());
            Gtk::Image* image = Gtk::manage(new Gtk::Image(pixbuf));
            image->show();
            Gtk::TextBuffer::iterator iter =
                m_textBuffer->get_iter_at_line_index(issue.firstLine - 1, issue.firstColumn - 1);
            Glib::RefPtr<Gtk::TextChildAnchor> anchor = m_textBuffer->create_child_anchor(iter);
            m_textView.add_child_at_anchor(*image, anchor);
            
            iter =
                m_textBuffer->get_iter_at_line_index(issue.firstLine - 1, issue.firstColumn - 1);
            Gtk::TextBuffer::iterator itEnd = iter;
            itEnd.forward_char();

            // prevent that the user can erase the icon with backspace key
            m_textBuffer->apply_tag(m_readOnlyTag, iter, itEnd);
        }
    }

    delete parserContext;
}

#endif // USE_LS_SCRIPTVM

void ScriptEditor::onTextErased(const Gtk::TextBuffer::iterator& itStart, const Gtk::TextBuffer::iterator& itEnd) {
    //printf("erased\n");
    if (m_ignoreEraseEvents) return;

#if USE_LS_SCRIPTVM
    removeIssueAnchors();
    m_textBuffer->remove_all_tags(m_textBuffer->begin(), m_textBuffer->end());
    updateSyntaxHighlightingByVM();
    updateParserIssuesByVM();
#else
    Gtk::TextBuffer::iterator itStart2 = itStart;
    if (itStart2.inside_word() || itStart2.ends_word())
        itStart2.backward_word_start();
    
    Gtk::TextBuffer::iterator itEnd2 = itEnd;
    if (itEnd2.inside_word()) itEnd2.forward_word_end();

    m_textBuffer->remove_all_tags(itStart2, itEnd2);
#endif // USE_LS_SCRIPTVM
}

void ScriptEditor::onModifiedChanged() {
    m_applyButton.set_sensitive( m_textBuffer->get_modified() );
}

void ScriptEditor::onButtonCancel() {
    hide();
}

void ScriptEditor::onButtonApply() {
    m_script->SetScriptAsText(m_textBuffer->get_text());
    m_textBuffer->set_modified(false);
}

void ScriptEditor::onWindowHide() {
    delete this; // this is the end, my friend
}
