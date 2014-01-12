/*                                                         -*- c++ -*-
 * Copyright (C) 2013-2014 Andreas Persson
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

#include "midirules.h"

#include <gtkmm/stock.h>

#include "global.h"

MidiRules::MidiRules() :
    label(_("Midi rule:")),
    unknown(_("unknown")),
    quit_button(Gtk::Stock::CLOSE)
{
    set_title(_("Midi Rules"));
    set_border_width(6);

    add(vbox);

    hbox.set_border_width(6);
    hbox.set_spacing(6);
    hbox.pack_start(label, Gtk::PACK_SHRINK);
    hbox.pack_start(combo, Gtk::PACK_SHRINK);
    const char* choices[] = { _("none"), _("Controller trigger"),
                              _("Legato"), 0 };
    for (int i = 0 ; choices[i] ; i++) {
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 24) || GTKMM_MAJOR_VERSION < 2
        combo.append_text(choices[i]);
#else
        combo.append(choices[i]);
#endif
    }
    combo.signal_changed().connect(
        sigc::mem_fun(*this, &MidiRules::combo_changed));
    vbox.pack_start(hbox, Gtk::PACK_SHRINK);

    box.set_border_width(6);
    vbox.pack_start(box);

    button_box.set_border_width(6);
    button_box.set_layout(Gtk::BUTTONBOX_END);
    button_box.pack_start(quit_button);
    quit_button.set_can_default();
    quit_button.grab_focus();
    quit_button.signal_clicked().connect(
        sigc::mem_fun(*this, &MidiRules::hide));
    vbox.pack_start(button_box, Gtk::PACK_SHRINK);

    legato.signal_changed().connect(sig_changed.make_slot());
    ctrl_trigger.signal_changed().connect(sig_changed.make_slot());

    show_all_children();
}

void MidiRules::combo_changed() {
    if (update_model) return;

    int rowno = combo.get_active_row_number();

    if (remove_unknown_from_combo()) {
        rowno--;
    }

    gig::MidiRule* rule = m->GetMidiRule(0);
    switch (rowno) {
    case NONE:
        if (rule) {
            m->DeleteMidiRule(0);
            set_instrument(m);
        }
        break;
    case CTRL_TRIGGER:
        if (!dynamic_cast<gig::MidiRuleCtrlTrigger*>(rule)) {
            m->AddMidiRuleCtrlTrigger();
            set_instrument(m);
        }
        break;
    case LEGATO:
        if (!dynamic_cast<gig::MidiRuleLegato*>(rule)) {
            m->AddMidiRuleLegato();
            set_instrument(m);
        }
        break;
    }
    sig_changed();
}

void MidiRules::set_instrument(gig::Instrument* instrument) {
    m = instrument;
    update_model++;

    std::vector<Widget*> children = box.get_children();
    if (children.size() == 1) {
        box.remove(*children[0]);
    }

    gig::MidiRule* rule = instrument->GetMidiRule(0);
    int active = -1;
    if (!rule) {
        active = NONE;
    } else if (gig::MidiRuleLegato* r =
        dynamic_cast<gig::MidiRuleLegato*>(rule)) {
        active = LEGATO;
        box.add(legato);
        legato.set_rule(r);
    } else if (gig::MidiRuleCtrlTrigger* r =
               dynamic_cast<gig::MidiRuleCtrlTrigger*>(rule)) {
        active = CTRL_TRIGGER;
        box.add(ctrl_trigger);
        ctrl_trigger.set_rule(r);
    } else {
        if (combo.get_model()->children().size() == NUMBER_OF_RULES) {
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 24) || GTKMM_MAJOR_VERSION < 2
            combo.prepend_text(unknown);
#else
            combo.prepend(unknown);
#endif
        }
        combo.set_active(0);
    }
    if (active != -1) {
        remove_unknown_from_combo();
        combo.set_active(active);
    }
    show_all_children();
    update_model--;
}

bool MidiRules::remove_unknown_from_combo() {
    if (combo.get_model()->children().size() == NUMBER_OF_RULES + 1) {
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
        combo.remove_text(unknown);
#else
        combo.remove_text(0);
#endif
        return true;
    }
    return false;
}


MidiRuleCtrlTrigger::MidiRuleCtrlTrigger() :
    table(2, 1),
    eControllerNumber(_("Controller"))
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
    , add_button(Gtk::Stock::ADD),
    remove_button(Gtk::Stock::REMOVE)
#endif
{
    connect(eControllerNumber, &gig::MidiRuleCtrlTrigger::ControllerNumber);

    set_spacing(6);

    scrolled_window.set_size_request(-1, 120);

    list_store = Gtk::ListStore::create(columns);
    tree_view.set_model(list_store);
    list_store->signal_row_changed().connect(
        sigc::mem_fun(*this, &MidiRuleCtrlTrigger::row_changed));
    list_store->signal_row_inserted().connect(
        sigc::mem_fun(*this, &MidiRuleCtrlTrigger::row_inserted));
    list_store->signal_row_deleted().connect(
        sigc::mem_fun(*this, &MidiRuleCtrlTrigger::row_deleted));

    append_num_column(_("Trigger point"), columns.trigger_point);
    tree_view.append_column_editable(_("Descending"), columns.descending);
    append_num_column(_("Vel sensitivity"), columns.vel_sensitivity, 1, 100);
    append_note_column(_("Key"), columns.key);
    tree_view.append_column_editable(_("Note off"), columns.note_off);
    tree_view.append_column_editable(_("Switch"), columns.switch_logic);

    int cols_count = append_num_column(_("Velocity"), columns.velocity);
    Gtk::TreeViewColumn* col = tree_view.get_column(cols_count - 1);
    col->add_attribute(*col->get_first_cell(), "visible", columns.switch_logic);
    cols_count = tree_view.append_column_editable(_("Override pedal"),
                                                  columns.override_pedal);
    col = tree_view.get_column(cols_count - 1);
    col->add_attribute(*col->get_first_cell(), "visible", columns.note_off);

    tree_view.get_selection()->signal_changed().connect(
        sigc::mem_fun(*this, &MidiRuleCtrlTrigger::sel_changed));

    scrolled_window.add(tree_view);
    scrolled_window.set_shadow_type(Gtk::SHADOW_IN);
    scrolled_window.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);

    table.set_col_spacings(5);
    table.add(eControllerNumber);
    pack_start(table, Gtk::PACK_SHRINK);

    vbox.add(scrolled_window);

#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
    vbox.set_spacing(6);
    toolbar.set_layout(Gtk::BUTTONBOX_START);
    toolbar.set_homogeneous();
    toolbar.set_spacing(6);
#else
    toolbar.set_toolbar_style(Gtk::TOOLBAR_ICONS);
    toolbar.set_show_arrow(false);
    toolbar.set_icon_size(Gtk::IconSize(1));
    toolbar.get_style_context()->add_class("inline-toolbar");

    add_button.set_icon_name("list-add-symbolic");
    remove_button.set_icon_name("list-remove-symbolic");
#endif

    add_button.signal_clicked().connect(
        sigc::mem_fun(*this, &MidiRuleCtrlTrigger::add_row));
    toolbar.add(add_button);

    remove_button.signal_clicked().connect(
        sigc::mem_fun(*this, &MidiRuleCtrlTrigger::remove_row));
    toolbar.add(remove_button);

    vbox.pack_start(toolbar, Gtk::PACK_SHRINK);
    add(vbox);
}

int MidiRuleCtrlTrigger::append_num_column(
    const char* title,
    const Gtk::TreeModelColumn<int>& column,
    int lower, int upper) {
    Gtk::CellRendererSpin* renderer = Gtk::manage(new Gtk::CellRendererSpin());
    renderer->property_editable() = true;
    renderer->signal_editing_started().connect(
        sigc::bind(
            sigc::mem_fun(*this, &MidiRuleCtrlTrigger::num_editing_started),
            renderer));
    renderer->signal_edited().connect(
        sigc::bind(
            sigc::mem_fun(*this, &MidiRuleCtrlTrigger::num_edited),
            column));
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
    renderer->property_adjustment() = new Gtk::Adjustment(lower, lower, upper);
#else
    renderer->property_adjustment() =
        Gtk::Adjustment::create(lower, lower, upper);
#endif

    int cols_count = tree_view.append_column(title, *renderer);
    Gtk::TreeViewColumn* col = tree_view.get_column(cols_count - 1);
    col->add_attribute(*renderer, "text", column);
    col->set_min_width(92);
    return cols_count;
}

int MidiRuleCtrlTrigger::append_note_column(
    const char* title,
    const Gtk::TreeModelColumn<Glib::ustring>& column) {
    Gtk::CellRendererSpin* renderer = Gtk::manage(new Gtk::CellRendererSpin());
    renderer->property_editable() = true;
    renderer->signal_editing_started().connect(
        sigc::bind(
            sigc::mem_fun(*this, &MidiRuleCtrlTrigger::note_editing_started),
            renderer));
    renderer->signal_edited().connect(
        sigc::bind(
            sigc::mem_fun(*this, &MidiRuleCtrlTrigger::note_edited),
            column));
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
    renderer->property_adjustment() = new Gtk::Adjustment(0, 0, 127);
#else
    renderer->property_adjustment() = Gtk::Adjustment::create(0, 0, 127);
#endif

    int cols_count = tree_view.append_column(title, *renderer);
    Gtk::TreeViewColumn* col = tree_view.get_column(cols_count - 1);
    col->add_attribute(*renderer, "text", column);
    col->set_min_width(98);
    return cols_count;
}

void MidiRuleCtrlTrigger::set_rule(gig::MidiRuleCtrlTrigger* r) {
    update_model++;
    update(r);
    list_store->clear();
    for (int i = 0 ; i < r->Triggers ; i++) {
        Gtk::TreeModel::Row row = *list_store->append();
        row[columns.trigger_point] = r->pTriggers[i].TriggerPoint;
        row[columns.descending] = r->pTriggers[i].Descending;
        row[columns.vel_sensitivity] = r->pTriggers[i].VelSensitivity;
        row[columns.key] = note_str(r->pTriggers[i].Key);
        row[columns.note_off] = r->pTriggers[i].NoteOff;
        row[columns.switch_logic] = r->pTriggers[i].Velocity != 255;
        if (r->pTriggers[i].Velocity != 255) {
            row[columns.velocity] = r->pTriggers[i].Velocity;
        }
        row[columns.override_pedal] = r->pTriggers[i].OverridePedal;
    }
    sel_changed();
    add_button.set_sensitive();
    if (r->Triggers == 32) add_button.set_sensitive(false);
    update_model--;
}

void MidiRuleCtrlTrigger::num_editing_started(
    Gtk::CellEditable* editable,
    const Glib::ustring& path,
    Gtk::CellRendererSpin* renderer) {
    int lower = renderer->property_adjustment().get_value()->get_lower();
    int upper = renderer->property_adjustment().get_value()->get_upper();
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
    renderer->property_adjustment() = new Gtk::Adjustment(lower, lower, upper);
#else
    renderer->property_adjustment() =
        Gtk::Adjustment::create(lower, lower, upper);
#endif
    Gtk::SpinButton* spin_button = dynamic_cast<Gtk::SpinButton*>(editable);
    if (spin_button) {
        spin_button->set_numeric();
    }
}

void MidiRuleCtrlTrigger::note_editing_started(
    Gtk::CellEditable* editable,
    const Glib::ustring& path,
    Gtk::CellRendererSpin* renderer) {
    int value = note_value(renderer->property_text());
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
    renderer->property_adjustment() = new Gtk::Adjustment(0, 0, 127);
#else
    renderer->property_adjustment() = Gtk::Adjustment::create(0, 0, 127);
#endif
    Gtk::SpinButton* spin_button = dynamic_cast<Gtk::SpinButton*>(editable);
    if (spin_button) {
        spin_button->get_adjustment()->set_value(value);
        spin_button_show_notes(*spin_button);
    }
}

void MidiRuleCtrlTrigger::num_edited(
    const Glib::ustring& path,
    const Glib::ustring& new_text,
    const Gtk::TreeModelColumn<int>& column) {
    Gtk::TreeModel::Row row = *list_store->get_iter(path);

    Gtk::TreeModel::Path cpath;
    Gtk::TreeViewColumn* col;
    tree_view.get_cursor(cpath, col);

    int lower = 0;
    int upper = 127;
    const Gtk::CellRenderer* r = col->get_first_cell();
    if (const Gtk::CellRendererSpin* renderer =
        dynamic_cast<const Gtk::CellRendererSpin*>(r)) {
        lower = renderer->property_adjustment().get_value()->get_lower();
        upper = renderer->property_adjustment().get_value()->get_upper();
    }

    row[column] = std::max(lower, std::min(atoi(new_text.c_str()), upper));
}

void MidiRuleCtrlTrigger::note_edited(
    const Glib::ustring& path,
    const Glib::ustring& new_text,
    const Gtk::TreeModelColumn<Glib::ustring>& column) {
    Gtk::TreeModel::Row row = *list_store->get_iter(path);

    row[column] = note_str(note_value(new_text));
}

void MidiRuleCtrlTrigger::sel_changed() {
    Gtk::TreeModel::iterator it = tree_view.get_selection()->get_selected();
    remove_button.set_sensitive();
    if (!it) remove_button.set_sensitive(false);
}

void MidiRuleCtrlTrigger::add_row() {
    Gtk::TreeModel::Path path;
    Gtk::TreeViewColumn* col;
    tree_view.get_cursor(path, col);
    if (!path.empty()) tree_view.set_cursor(path);

    Gtk::TreeModel::iterator it = list_store->append();
    Gtk::TreeModel::Row row = *it;

    update_model++;
    row[columns.trigger_point] = 64;
    row[columns.descending] = false;
    row[columns.vel_sensitivity] = 50;
    row[columns.key] = note_str(60);
    row[columns.note_off] = false;
    row[columns.switch_logic] = false;
    row[columns.override_pedal] = false;
    update_model--;

    tree_view.get_selection()->select(row);
    path = list_store->get_path(it);
    tree_view.scroll_to_row(path);
    tree_view.set_cursor(path);
}

void MidiRuleCtrlTrigger::remove_row() {
    Gtk::TreeModel::Path cpath;
    Gtk::TreeViewColumn* col;
    tree_view.get_cursor(cpath, col);
    if (!cpath.empty()) tree_view.set_cursor(cpath);

    Gtk::TreeModel::iterator it = tree_view.get_selection()->get_selected();
    if (it) {
        Gtk::TreePath path = list_store->get_path(it);
        list_store->erase(it);

        it = tree_view.get_selection()->get_selected();
        if (!it) {
            int i = path[0];
            int n = list_store->children().size();
            if (n) {
                if (i >= n) i = n - 1;
                path[0] = i;
                tree_view.get_selection()->select(path);
            }
        }
    }
}

void MidiRuleCtrlTrigger::row_changed(const Gtk::TreeModel::Path& path,
                                      const Gtk::TreeModel::iterator& iter) {
    if (update_model) return;

    Gtk::TreeModel::Row row = *iter;
    int i = path[0];

    if (m->pTriggers[i].Velocity == 255 && row[columns.switch_logic]) {
        update_model++;
        row[columns.velocity] = 100;
        update_model--;
    }

    int key = note_value(row[columns.key]);

    if (m->pTriggers[i].TriggerPoint != row[columns.trigger_point] ||
        m->pTriggers[i].Descending != row[columns.descending] ||
        m->pTriggers[i].VelSensitivity != row[columns.vel_sensitivity] ||
        m->pTriggers[i].Key != key ||
        m->pTriggers[i].NoteOff != row[columns.note_off] ||
        (m->pTriggers[i].Velocity != 255) != row[columns.switch_logic] ||
        m->pTriggers[i].Velocity != row[columns.velocity] ||
        m->pTriggers[i].OverridePedal != row[columns.override_pedal])
    {
        m->pTriggers[i].TriggerPoint = row[columns.trigger_point];
        m->pTriggers[i].Descending = row[columns.descending];
        m->pTriggers[i].VelSensitivity = row[columns.vel_sensitivity];
        m->pTriggers[i].Key = key;
        m->pTriggers[i].NoteOff = row[columns.note_off];
        m->pTriggers[i].Velocity =
            row[columns.switch_logic] ? row[columns.velocity] : 255;
        m->pTriggers[i].OverridePedal = row[columns.override_pedal];
        sig_changed();
    }
}

void MidiRuleCtrlTrigger::row_inserted(const Gtk::TreeModel::Path& path,
                                       const Gtk::TreeModel::iterator& iter) {
    if (update_model) return;
    Gtk::TreeModel::Row row = *iter;
    int i = m->Triggers++;
    m->pTriggers[i].TriggerPoint = 64;
    m->pTriggers[i].Descending = false;
    m->pTriggers[i].VelSensitivity = 50;
    m->pTriggers[i].Key = 60;
    m->pTriggers[i].NoteOff = false;
    m->pTriggers[i].Velocity = 255;
    m->pTriggers[i].OverridePedal = false;
    add_button.set_sensitive();
    if (m->Triggers == 32) add_button.set_sensitive(false);
    sig_changed();
}

void MidiRuleCtrlTrigger::row_deleted(const Gtk::TreeModel::Path& path) {
    if (update_model) return;
    for (int i = path[0] + 1 ; i < m->Triggers ; i++) {
        m->pTriggers[i - 1] = m->pTriggers[i];
    }
    m->Triggers--;
    add_button.set_sensitive();
    sig_changed();
}



MidiRuleLegato::MidiRuleLegato() :
    Table(2, 1),
    eBypassUseController(_("Bypass use controller")),
    eBypassKey(_("Bypass key")),
    eBypassController(_("Bypass controller")),
    eThresholdTime(_("Threshold time"), 10, 500),
    eReleaseTime(_("Release time"), 10, 500),
    eKeyRangeLow(_("Key range low")),
    eKeyRangeHigh(_("Key range high")),
    eReleaseTriggerKey(_("Release trigger key")),
    eAltSustain1Key(_("Alt sustain 1 key")),
    eAltSustain2Key(_("Alt sustain 2 key"))
{
    connect(eBypassUseController, &gig::MidiRuleLegato::BypassUseController);
    connect(eBypassKey, &gig::MidiRuleLegato::BypassKey);
    connect(eBypassController, &gig::MidiRuleLegato::BypassController);
    connect(eThresholdTime, &gig::MidiRuleLegato::ThresholdTime);
    connect(eReleaseTime, &gig::MidiRuleLegato::ReleaseTime);
    connect(eKeyRangeLow, eKeyRangeHigh, &gig::MidiRuleLegato::KeyRange);
    connect(eReleaseTriggerKey, &gig::MidiRuleLegato::ReleaseTriggerKey);
    connect(eAltSustain1Key, &gig::MidiRuleLegato::AltSustain1Key);
    connect(eAltSustain2Key, &gig::MidiRuleLegato::AltSustain2Key);

    set_col_spacings(5);

    add(eBypassUseController);
    add(eBypassKey);
    add(eBypassController);
    add(eThresholdTime);
    add(eReleaseTime);
    add(eKeyRangeLow);
    add(eKeyRangeHigh);
    add(eReleaseTriggerKey);
    add(eAltSustain1Key);
    add(eAltSustain2Key);

    eBypassUseController.signal_value_changed().connect(
        sigc::mem_fun(*this, &MidiRuleLegato::BypassUseController_toggled));
}

void MidiRuleLegato::BypassUseController_toggled() {
    bool useController = eBypassUseController.get_value();
    eBypassKey.set_sensitive(!useController);
    eBypassController.set_sensitive(useController);
}

void MidiRuleLegato::set_rule(gig::MidiRuleLegato* r) {
    update_model++;
    update(r);
    BypassUseController_toggled();
    update_model--;
}
