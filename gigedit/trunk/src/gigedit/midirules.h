/*                                                         -*- c++ -*-
 * Copyright (C) 2013-2016 Andreas Persson
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef GIGEDIT_MIDIRULES_H
#define GIGEDIT_MIDIRULES_H

#include <gig.h>

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION >= 12) || GTKMM_MAJOR_VERSION > 2
#include <gtkmm/cellrendererspin.h>
#endif
#include <gtkmm/comboboxtext.h>
#include <gtkmm/label.h>
#include <gtkmm/liststore.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/separatortoolitem.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treeview.h>
#include <gtkmm/window.h>

#include "paramedit.h"
#include "compat.h"
#include "ManagedWindow.h"

class MidiRuleCtrlTrigger : public Gtk::VBox,
                            public PropEditor<gig::MidiRuleCtrlTrigger> {
public:
    MidiRuleCtrlTrigger();
    void set_rule(gig::MidiRuleCtrlTrigger* r);

protected:
    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        ModelColumns() {
            add(trigger_point);
            add(descending);
            add(vel_sensitivity);
            add(key);
            add(note_off);
            add(switch_logic);
            add(velocity);
            add(override_pedal);
        }

        Gtk::TreeModelColumn<int> trigger_point;
        Gtk::TreeModelColumn<bool> descending;
        Gtk::TreeModelColumn<int> vel_sensitivity;
        Gtk::TreeModelColumn<Glib::ustring> key;
        Gtk::TreeModelColumn<bool> note_off;
        Gtk::TreeModelColumn<bool> switch_logic;
        Gtk::TreeModelColumn<int> velocity;
        Gtk::TreeModelColumn<bool> override_pedal;
    } columns;

    int append_num_column(const char* title,
                          const Gtk::TreeModelColumn<int>& column,
                          int lower = 0, int upper = 127);
    int append_note_column(const char* title,
                           const Gtk::TreeModelColumn<Glib::ustring>& column);
    void num_editing_started(Gtk::CellEditable* editable,
                             const Glib::ustring& path,
                             Gtk::CellRendererSpin* renderer);
    void note_editing_started(Gtk::CellEditable* editable,
                              const Glib::ustring& path,
                              Gtk::CellRendererSpin* renderer);
    void num_edited(const Glib::ustring& path, const Glib::ustring& new_text,
                    const Gtk::TreeModelColumn<int>& column);
    void note_edited(const Glib::ustring& path, const Glib::ustring& new_text,
                     const Gtk::TreeModelColumn<Glib::ustring>& column);
    void row_changed(const Gtk::TreeModel::Path& path,
                     const Gtk::TreeModel::iterator& iter);
    void row_inserted(const Gtk::TreeModel::Path& path,
                      const Gtk::TreeModel::iterator& iter);
    void row_deleted(const Gtk::TreeModel::Path& path);

    Table table;
    NumEntryTemp<uint8_t> eControllerNumber;

    Gtk::VBox vbox;
    Glib::RefPtr<Gtk::ListStore> list_store;
    Gtk::TreeView tree_view;
    Gtk::ScrolledWindow scrolled_window;
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
    Gtk::HButtonBox toolbar;
    Gtk::Button add_button;
    Gtk::Button remove_button;
#else
    Gtk::Toolbar toolbar;
    Gtk::ToolButton add_button;
    Gtk::ToolButton remove_button;
#endif

    void sel_changed();
    void add_row();
    void remove_row();
};


class MidiRuleLegato : public Table,
                       public PropEditor<gig::MidiRuleLegato> {
public:
    MidiRuleLegato();
    void set_rule(gig::MidiRuleLegato* r);

protected:
    BoolEntry eBypassUseController;
    NoteEntry eBypassKey;
    NumEntryTemp<uint8_t> eBypassController;
    NumEntryTemp<uint16_t> eThresholdTime;
    NumEntryTemp<uint16_t> eReleaseTime;
    NoteEntry eKeyRangeLow;
    NoteEntry eKeyRangeHigh;
    NoteEntry eReleaseTriggerKey;
    NoteEntry eAltSustain1Key;
    NoteEntry eAltSustain2Key;

    void BypassUseController_toggled();
};


class MidiRules : public ManagedWindow,
                  public PropEditor<gig::Instrument> {
public:
    MidiRules();
    void set_instrument(gig::Instrument* instrument);

    // implementation for abstract methods of interface class "ManagedWindow"
    virtual Settings::Property<int>* windowSettingX() { return &Settings::singleton()->midiRulesWindowX; }
    virtual Settings::Property<int>* windowSettingY() { return &Settings::singleton()->midiRulesWindowY; }
    virtual Settings::Property<int>* windowSettingWidth() { return &Settings::singleton()->midiRulesWindowW; }
    virtual Settings::Property<int>* windowSettingHeight() { return &Settings::singleton()->midiRulesWindowH; }

protected:
    enum {
        NONE = 0,
        CTRL_TRIGGER,
        LEGATO,
        NUMBER_OF_RULES
    };

    Gtk::VBox vbox;

    Gtk::Label label;
    Gtk::ComboBoxText combo;
    Gtk::HBox hbox;

    Gtk::HBox box;

    MidiRuleCtrlTrigger ctrl_trigger;
    MidiRuleLegato legato;

    Gtk::HButtonBox button_box;
    Gtk::Button quit_button;

    const Glib::ustring unknown;

    void combo_changed();
    bool remove_unknown_from_combo();
};

#endif
