/*
    Copyright (c) 2014 Christian Schoenebeck
    
    This file is part of "gigedit" and released under the terms of the
    GNU General Public License version 2.
*/

#include "scriptslots.h"
#include "global.h"

ScriptSlots::ScriptSlots() :
    m_closeButton(_("_Close"), true)
{
    m_instrument = NULL;

    add(m_vbox);
    
    m_generalInfoLabel.set_text(_(
        "Each row (\"slot\") references one instrument script that shall be "
        "executed by the sampler for currently selected instrument. Slots are "
        "executed consecutively from top down."
    ));
    m_generalInfoLabel.set_line_wrap();
    m_vbox.pack_start(m_generalInfoLabel, Gtk::PACK_SHRINK);

    m_dragHintLabel.set_text(_(
        "Drag & drop a script from main window to this window to add a new "
        "script slot for this instrument."
    ));
    m_dragHintLabel.set_line_wrap();
    m_scrolledWindow.add(m_vboxSlots);
    m_scrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    m_vbox.pack_start(m_scrolledWindow);
    
    m_vbox.pack_start(m_dragHintLabel, Gtk::PACK_SHRINK);

    m_buttonBox.set_layout(Gtk::BUTTONBOX_END);
    m_buttonBox.pack_start(m_closeButton);
    m_closeButton.set_can_default();
    m_closeButton.grab_focus();
    m_vbox.pack_start(m_buttonBox, Gtk::PACK_SHRINK);

    m_closeButton.signal_clicked().connect(
        sigc::mem_fun(*this, &ScriptSlots::onButtonClose)
    );
    
    signal_hide().connect(
        sigc::mem_fun(*this, &ScriptSlots::onWindowHide)
    );

    // establish drag&drop between scripts tree view on main diwno and this
    // ScriptSlots window
    std::vector<Gtk::TargetEntry> drag_target_gig_script;
    drag_target_gig_script.push_back(Gtk::TargetEntry("gig::Script"));
    drag_dest_set(drag_target_gig_script);
    signal_drag_data_received().connect(
        sigc::mem_fun(*this, &ScriptSlots::onScriptDragNDropDataReceived)
    );

    show_all_children();

    resize(460,300);
}

ScriptSlots::~ScriptSlots() {
    //printf("ScriptSlots destruct\n");
    clearSlots();
}

void ScriptSlots::clearSlots() {
    for (int i = 0; i < m_slots.size(); ++i) {
        delete m_slots[i].deleteButton;
        delete m_slots[i].downButton;
        delete m_slots[i].upButton;
        delete m_slots[i].label;
        delete m_slots[i].hbox;
    }
    m_slots.clear();
}

void ScriptSlots::setInstrument(gig::Instrument* instrument) {
    m_instrument = instrument;
    if (!m_instrument) {
        set_title(_("No Instrument"));
        return;
    }

    set_title(std::string(_("Script Slots of Instrument")) + " - \"" + instrument->pInfo->Name + "\"");
    clearSlots();
    for (int i = 0; i < instrument->ScriptSlotCount(); ++i) {
        gig::Script* script = instrument->GetScriptOfSlot(i);
        if (!script) continue;
        //printf("script '%s'\n", script->Name.c_str());
        appendNewSlot(script);
    }
}

void ScriptSlots::refreshSlots() {
    clearSlots();
    setInstrument(m_instrument);
}

void ScriptSlots::onScriptDragNDropDataReceived(
    const Glib::RefPtr<Gdk::DragContext>& context, int, int,
    const Gtk::SelectionData& selection_data, guint, guint time)
{
    gig::Script* script = *((gig::Script**) selection_data.get_data());
    if (script && selection_data.get_length() == sizeof(gig::Script*)) {
        std::cout << "Drop received script \"" << script->Name << "\"" << std::endl;
        m_instrument->AddScriptSlot(script);
        appendNewSlot(script);
        // drop success
        context->drop_reply(true, time);
    } else {
        // drop failed
        context->drop_reply(false, time);
    }
}

void ScriptSlots::appendNewSlot(gig::Script* script) {
    static int slotID = 0;

    Row row;
    row.id = slotID++;
    row.hbox = new Gtk::HBox;
    row.label = new Gtk::Label;
    row.downButton = new Gtk::Button(_("_Down"), true);
    row.upButton = new Gtk::Button(_("_Up"), true);
    row.deleteButton = new Gtk::Button(_("_Delete"), true);
    row.script = script;

    row.hbox->pack_start(*row.label);
    row.hbox->pack_start(*row.downButton, Gtk::PACK_SHRINK);
    row.hbox->pack_start(*row.upButton, Gtk::PACK_SHRINK);
    row.hbox->pack_start(*row.deleteButton, Gtk::PACK_SHRINK);

    row.label->set_text(ToString(m_slots.size()+1) + ". \"" + script->Name + "\"");
    //row.label->set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_CENTER);
    
    row.upButton->signal_clicked().connect(
        sigc::bind(
            sigc::mem_fun(*this, &ScriptSlots::moveSlotUp), row.id
        )
    );
    row.downButton->signal_clicked().connect(
        sigc::bind(
            sigc::mem_fun(*this, &ScriptSlots::moveSlotDown), row.id
        )
    );
    row.deleteButton->signal_clicked().connect(
        sigc::bind(
            sigc::mem_fun(*this, &ScriptSlots::deleteSlot), row.id
        )
    );

    m_vboxSlots.add(*row.hbox);
    m_scrolledWindow.show_all_children();

    m_slots.push_back(row);
}

void ScriptSlots::moveSlotUp(int slotID) {
    for (int i = 0; i < m_instrument->ScriptSlotCount(); ++i) {
        if (m_slots[i].id == slotID) {
            if (i != 0) {
                m_instrument->SwapScriptSlots(i, i-1);
                refreshSlots();
            }
            break;
        }
    }
}

void ScriptSlots::moveSlotDown(int slotID) {
    for (int i = 0; i < m_instrument->ScriptSlotCount(); ++i) {
        if (m_slots[i].id == slotID) {
            if (i < m_instrument->ScriptSlotCount() - 1) {
                m_instrument->SwapScriptSlots(i, i+1);
                refreshSlots();
            }
            break;
        }
    }
}

void ScriptSlots::deleteSlot(int slotID) {
    for (int i = 0; i < m_instrument->ScriptSlotCount(); ++i) {
        if (m_slots[i].id == slotID) {
            m_instrument->RemoveScriptSlot(i);
            refreshSlots();
            break;
        }
    }
}

void ScriptSlots::onButtonClose() {
    hide();
}

void ScriptSlots::onWindowHide() {
    delete this; // this is the end, my friend
}

