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

static Glib::RefPtr<Gdk::Pixbuf> createIcon(std::string name, const Glib::RefPtr<Gdk::Screen>& screen) {
    const int targetH = 16;
    Glib::RefPtr<Gtk::IconTheme> theme = Gtk::IconTheme::get_for_screen(screen);
    int w = 0;
    int h = 0; // ignored
    Gtk::IconSize::lookup(Gtk::ICON_SIZE_SMALL_TOOLBAR, w, h);
    if (!theme->has_icon(name))
        return Glib::RefPtr<Gdk::Pixbuf>();
    Glib::RefPtr<Gdk::Pixbuf> pixbuf = theme->load_icon(name, w, Gtk::ICON_LOOKUP_GENERIC_FALLBACK);
    if (pixbuf->get_height() != targetH) {
        pixbuf = pixbuf->scale_simple(targetH, targetH, Gdk::INTERP_BILINEAR);
    }
    return pixbuf;
}

static Glib::RefPtr<Gdk::Pixbuf> createIcon(std::vector<std::string> alternativeNames, const Glib::RefPtr<Gdk::Screen>& screen) {
    for (int i = 0; i < alternativeNames.size(); ++i) {
        Glib::RefPtr<Gdk::Pixbuf> buf = createIcon(alternativeNames[i], screen);
        if (buf) return buf;
    }
    return Glib::RefPtr<Gdk::Pixbuf>();
}

ScriptEditor::ScriptEditor() :
    m_statusLabel("",  Gtk::ALIGN_START),
    m_applyButton(_("_Apply"), true),
    m_cancelButton(_("_Cancel"), true)
{
    m_script = NULL;
#if USE_LS_SCRIPTVM
    m_vm = NULL;
#endif

    // depending on GTK version and installed themes, there may be different
    // icons, and different names for them, so for each type of icon we use,
    // we provide a list of possible icon names, the first one found to be
    // installed on the local system from the list will be used and loaded for
    // the respective purpose (so order matters in those lists)
    //
    // (see https://developer.gnome.org/gtkmm/stable/namespaceGtk_1_1Stock.html for
    // available icon names)
    std::vector<std::string> errorIconNames;
    errorIconNames.push_back("dialog-error");
    errorIconNames.push_back("media-record");
    errorIconNames.push_back("process-stop");

    std::vector<std::string> warningIconNames;
    warningIconNames.push_back("dialog-warning-symbolic");
    warningIconNames.push_back("dialog-warning");

    std::vector<std::string> successIconNames;
    successIconNames.push_back("emblem-default");
    successIconNames.push_back("tools-check-spelling");

    m_errorIcon = createIcon(errorIconNames, get_screen());
    m_warningIcon = createIcon(warningIconNames, get_screen());
    m_successIcon = createIcon(successIconNames, get_screen());

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

    // create menu
    m_actionGroup = Gtk::ActionGroup::create();
    m_actionGroup->add(Gtk::Action::create("MenuScript", _("_Script")));
    m_actionGroup->add(Gtk::Action::create("Apply", _("_Apply")),
                       Gtk::AccelKey("<control>s"),
                       sigc::mem_fun(*this, &ScriptEditor::onButtonApply));
    m_actionGroup->add(Gtk::Action::create("Close", _("_Close")),
                       Gtk::AccelKey("<control>q"),
                       sigc::mem_fun(*this, &ScriptEditor::onButtonCancel));
    m_actionGroup->add(Gtk::Action::create("MenuEditor", _("_Editor")));
    m_actionGroup->add(Gtk::Action::create("ChangeFont", _("_Font Size ...")),
                       sigc::mem_fun(*this, &ScriptEditor::onMenuChangeFontSize));
    m_uiManager = Gtk::UIManager::create();
    m_uiManager->insert_action_group(m_actionGroup);
    add_accel_group(m_uiManager->get_accel_group());
    m_uiManager->add_ui_from_string(
        "<ui>"
        "  <menubar name='MenuBar'>"
        "    <menu action='MenuScript'>"
        "      <menuitem action='Apply'/>"
        "      <separator/>"
        "      <menuitem action='Close'/>"
        "    </menu>"
        "    <menu action='MenuEditor'>"
        "      <menuitem action='ChangeFont'/>"
        "    </menu>"
        "  </menubar>"
        "</ui>"
    );

    m_textBuffer = Gtk::TextBuffer::create(m_tagTable);
    m_textView.set_buffer(m_textBuffer);
    setFontSize(currentFontSize(), false);
    m_scrolledWindow.add(m_textView);
    m_scrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    Gtk::Widget* menuBar = m_uiManager->get_widget("/MenuBar");
    m_vbox.pack_start(*menuBar, Gtk::PACK_SHRINK);
    m_vbox.pack_start(m_scrolledWindow);

    m_buttonBox.set_layout(Gtk::BUTTONBOX_END);
    m_buttonBox.pack_start(m_applyButton);
    m_buttonBox.pack_start(m_cancelButton);
    m_applyButton.set_can_default();
    m_applyButton.set_sensitive(false);
    m_applyButton.grab_focus();

#if GTKMM_MAJOR_VERSION >= 3
    m_statusImage.set_margin_left(6);
    m_statusImage.set_margin_right(6);
#else
    m_statusHBox.set_spacing(6);
#endif

    m_statusHBox.pack_start(m_statusImage, Gtk::PACK_SHRINK);
    m_statusHBox.pack_start(m_statusLabel);
    m_statusHBox.show_all_children();

    m_footerHBox.pack_start(m_statusHBox);
    m_footerHBox.pack_start(m_buttonBox, Gtk::PACK_SHRINK);

    m_vbox.pack_start(m_footerHBox, Gtk::PACK_SHRINK);

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

    signal_delete_event().connect(
        sigc::mem_fun(*this, &ScriptEditor::onWindowDelete)
    );

    show_all_children();
}

ScriptEditor::~ScriptEditor() {
    printf("ScriptEditor destruct\n");
#if USE_LS_SCRIPTVM
    if (m_vm) delete m_vm;
#endif
}

int ScriptEditor::currentFontSize() const {
#if defined(__APPLE__)
    const int defaultFontSize = 14;
#else
    const int defaultFontSize = 10;
#endif
    const int settingFontSize = Settings::singleton()->scriptEditorFontSize;
    const int fontSize = (settingFontSize > 0) ? settingFontSize : defaultFontSize;
    return fontSize;
}

void ScriptEditor::setFontSize(int size, bool save) {
    //printf("setFontSize(%d,%d)\n", size, save);
    Pango::FontDescription fdesc;
    fdesc.set_family("monospace");
    fdesc.set_size(size * PANGO_SCALE);
#if GTKMM_MAJOR_VERSION < 3
    m_textView.modify_font(fdesc);
#else
    m_textView.override_font(fdesc);
#endif
    if (save) Settings::singleton()->scriptEditorFontSize = size;
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
    //printf("onTextInserted()\n");
#if USE_LS_SCRIPTVM
    m_textBuffer->remove_all_tags(m_textBuffer->begin(), m_textBuffer->end());
    updateSyntaxHighlightingByVM();
    updateParserIssuesByVM();
    updateStatusBar();
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

static void getIteratorsForIssue(Glib::RefPtr<Gtk::TextBuffer>& txtbuf, const LinuxSampler::ParserIssue& issue, Gtk::TextBuffer::iterator& start, Gtk::TextBuffer::iterator& end) {
    start = txtbuf->get_iter_at_line_index(issue.firstLine - 1, issue.firstColumn - 1);
    end = start;
    end.forward_lines(issue.lastLine - issue.firstLine);
    end.forward_chars(
        (issue.lastLine != issue.firstLine)
            ? issue.lastColumn - 1
            : issue.lastColumn - issue.firstColumn + 1
    );
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
    Gtk::TextBuffer::iterator itStart, itEnd;
    getIteratorsForIssue(txtbuf, issue, itStart, itEnd);
    txtbuf->apply_tag(tag, itStart, itEnd);
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

void ScriptEditor::updateParserIssuesByVM() {
    GetScriptVM();
    const std::string s = m_textBuffer->get_text();
    LinuxSampler::VMParserContext* parserContext = m_vm->loadScript(s);
    m_issues = parserContext->issues();
    m_errors = parserContext->errors();
    m_warnings = parserContext->warnings();

    for (int i = 0; i < m_issues.size(); ++i) {
        const LinuxSampler::ParserIssue& issue = m_issues[i];

        if (issue.isErr()) {
            applyCodeTag(m_textBuffer, issue, m_errorTag);
        } else if (issue.isWrn()) {
            applyCodeTag(m_textBuffer, issue, m_warningTag);
        }
    }

    delete parserContext;
}

void ScriptEditor::updateIssueTooltip(GdkEventMotion* e) {
    int x, y;
    m_textView.window_to_buffer_coords(Gtk::TEXT_WINDOW_TEXT, int(e->x), int(e->y), x, y);

    Gtk::TextBuffer::iterator it;
    m_textView.get_iter_at_location(it, x, y);
    
    const int line = it.get_line();
    const int column = it.get_line_offset();

    //printf("mouse at l%d c%d\n", line, column);

    for (int i = 0; i < m_issues.size(); ++i) {
        const LinuxSampler::ParserIssue& issue = m_issues[i];
        const int firstLine   = issue.firstLine - 1;
        const int firstColumn = issue.firstColumn - 1;
        const int lastLine    = issue.lastLine - 1;
        const int lastColumn  = issue.lastColumn - 1;
        if (firstLine <= line && line <= lastLine &&
            (firstLine != line || firstColumn <= column) &&
            (lastLine  != line || lastColumn  >= column))
        {
            m_textView.set_tooltip_markup(
                (issue.isErr() ? "<span foreground=\"#ff9393\">ERROR:</span> " : "<span foreground=\"#c4950c\">Warning:</span> ") +
                issue.txt
            );
            return;
        }
    }

    m_textView.set_tooltip_markup("");
}

static std::string warningsCountTxt(const std::vector<LinuxSampler::ParserIssue> warnings) {
    std::string txt = "<span foreground=\"#c4950c\">" + ToString(warnings.size());
    txt += (warnings.size() == 1) ? " Warning" : " Warnings";
    txt += "</span>";
    return txt;
}

static std::string errorsCountTxt(const std::vector<LinuxSampler::ParserIssue> errors) {
    std::string txt = "<span foreground=\"#c40c0c\">" + ToString(errors.size());
    txt += (errors.size() == 1) ? " Error" : " Errors";
    txt += "</span>";
    return txt;
}

void ScriptEditor::updateStatusBar() {
    // update status text
    std::string txt;
    if (m_issues.empty()) {
        txt = "No issues with this script.";
    } else {
        const char* txtWontLoad = ". Sampler won't load instruments using this script!";
        txt = "There ";
        txt += (m_errors.size() <= 1 && m_warnings.size() <= 1) ? "is " : "are ";
        if (m_errors.empty()) {
            txt += warningsCountTxt(m_warnings) + ". Script will load, but might not behave as expected!";
        } else if (m_warnings.empty()) {
            txt += errorsCountTxt(m_errors) + txtWontLoad;
        } else {
            txt += errorsCountTxt(m_errors) + " and " +
                   warningsCountTxt(m_warnings) + txtWontLoad;
        }
    }
    m_statusLabel.set_markup(txt);

    // update status icon
    m_statusImage.set(
        m_issues.empty() ? m_successIcon : !m_errors.empty() ? m_errorIcon : m_warningIcon
    );
}

#endif // USE_LS_SCRIPTVM

void ScriptEditor::onTextErased(const Gtk::TextBuffer::iterator& itStart, const Gtk::TextBuffer::iterator& itEnd) {
    //printf("erased\n");
#if USE_LS_SCRIPTVM
    m_textBuffer->remove_all_tags(m_textBuffer->begin(), m_textBuffer->end());
    updateSyntaxHighlightingByVM();
    updateParserIssuesByVM();
    updateStatusBar();
#else
    Gtk::TextBuffer::iterator itStart2 = itStart;
    if (itStart2.inside_word() || itStart2.ends_word())
        itStart2.backward_word_start();
    
    Gtk::TextBuffer::iterator itEnd2 = itEnd;
    if (itEnd2.inside_word()) itEnd2.forward_word_end();

    m_textBuffer->remove_all_tags(itStart2, itEnd2);
#endif // USE_LS_SCRIPTVM
}

bool ScriptEditor::on_motion_notify_event(GdkEventMotion* e) {
#if USE_LS_SCRIPTVM
    //TODO: event throttling would be a good idea here
    updateIssueTooltip(e);
#endif
    return ManagedWindow::on_motion_notify_event(e);
}

void ScriptEditor::onMenuChangeFontSize() {
    //TODO: for GTKMM >= 3.2 class Gtk::FontChooser could be used instead
    Gtk::Dialog dialog(_("Font Size"), true /*modal*/);
    Gtk::HBox hbox;
    hbox.set_spacing(6);

    Gtk::Label label(_("Editor's Font Size:"), Gtk::ALIGN_START);
    hbox.pack_start(label, Gtk::PACK_SHRINK);

    Gtk::SpinButton spinButton;
    spinButton.set_range(4, 80);
    spinButton.set_increments(1, 10);
    spinButton.set_value(currentFontSize());
    hbox.pack_start(spinButton);

    dialog.get_vbox()->pack_start(hbox);
    dialog.add_button(_("_OK"), 0);
    dialog.add_button(_("_Cancel"), 1);

    dialog.show_all_children();

    if (!dialog.run()) { // OK selected ...
        const int newFontSize = spinButton.get_value_as_int();
        if (newFontSize >= 4)
            setFontSize(newFontSize, true);
    }
}

bool ScriptEditor::onWindowDelete(GdkEventAny* e) {
    //printf("onWindowDelete\n");

    if (!isModified()) return false; // propagate event further (which will close this window)

    gchar* msg = g_strdup_printf(_("Apply changes to instrument script \"%s\" before closing?"),
                                 m_script->Name.c_str());
    Gtk::MessageDialog dialog(*this, msg, false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_NONE);
    g_free(msg);
    dialog.set_secondary_text(_("If you close without applying, your changes will be lost."));
    dialog.add_button(_("Close _Without Applying"), Gtk::RESPONSE_NO);
    dialog.add_button(_("_Cancel"), Gtk::RESPONSE_CANCEL);
    dialog.add_button(_("_Apply"), Gtk::RESPONSE_YES);
    dialog.set_default_response(Gtk::RESPONSE_YES);
    int response = dialog.run();
    dialog.hide();

    // user decided to close script editor without saving
    if (response == Gtk::RESPONSE_NO)
        return false; // propagate event further (which will close this window)

    // user cancelled dialog, thus don't close script editor
    if (response == Gtk::RESPONSE_CANCEL) {
        show();
        return true; // drop event (prevents closing this window)
    }

    // user wants to apply the changes, afterwards close window
    if (response == Gtk::RESPONSE_YES) {
        onButtonApply();
        return false; // propagate event further (which will close this window)
    }

    // should never ever make it to this point actually
    return false;
}

bool ScriptEditor::isModified() const {
    return m_textBuffer->get_modified();
}

void ScriptEditor::onModifiedChanged() {
    m_applyButton.set_sensitive(isModified());
#if USE_LS_SCRIPTVM
    updateStatusBar();
#endif
}

void ScriptEditor::onButtonCancel() {
    bool dropEvent = onWindowDelete(NULL);
    if (dropEvent) return;
    hide();
}

void ScriptEditor::onButtonApply() {
    signal_script_to_be_changed.emit(m_script);
    m_script->SetScriptAsText(m_textBuffer->get_text());
    signal_script_changed.emit(m_script);
    m_textBuffer->set_modified(false);
}

void ScriptEditor::onWindowHide() {
    delete this; // this is the end, my friend
}
