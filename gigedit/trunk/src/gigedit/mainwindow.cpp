/*
 * Copyright (C) 2006-2015 Andreas Persson
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with program; see the file COPYING. If not, write to the Free
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA.
 */

#include <iostream>
#include <cstring>

#include <glibmm/convert.h>
#include <glibmm/dispatcher.h>
#include <glibmm/miscutils.h>
#include <glibmm/stringutils.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/stock.h>
#include <gtkmm/targetentry.h>
#include <gtkmm/main.h>
#include <gtkmm/toggleaction.h>
#if GTKMM_MAJOR_VERSION < 3
#include "wrapLabel.hh"
#endif

#include "global.h"
#include "compat.h"

#include <stdio.h>
#include <sndfile.h>
#include <assert.h>

#include "mainwindow.h"
#include "Settings.h"
#include "CombineInstrumentsDialog.h"
#include "scripteditor.h"
#include "scriptslots.h"
#include "ReferencesView.h"
#include "../../gfx/status_attached.xpm"
#include "../../gfx/status_detached.xpm"


MainWindow::MainWindow() :
    m_DimRegionChooser(*this),
    dimreg_label(_("Changes apply to:")),
    dimreg_all_regions(_("all regions")),
    dimreg_all_dimregs(_("all dimension splits")),
    dimreg_stereo(_("both channels"))
{
//    set_border_width(5);
//    set_default_size(400, 200);


    add(m_VBox);

    // Handle selection
    m_TreeView.get_selection()->signal_changed().connect(
        sigc::mem_fun(*this, &MainWindow::on_sel_change));

    // m_TreeView.set_reorderable();

    m_TreeView.signal_button_press_event().connect_notify(
        sigc::mem_fun(*this, &MainWindow::on_button_release));

    // Add the TreeView tab, inside a ScrolledWindow, with the button underneath:
    m_ScrolledWindow.add(m_TreeView);
//    m_ScrolledWindow.set_size_request(200, 600);
    m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    m_ScrolledWindowSamples.add(m_TreeViewSamples);
    m_ScrolledWindowSamples.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    m_ScrolledWindowScripts.add(m_TreeViewScripts);
    m_ScrolledWindowScripts.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);


    m_TreeViewNotebook.set_size_request(300);

    m_HPaned.add1(m_TreeViewNotebook);
    dimreg_hbox.add(dimreg_label);
    dimreg_hbox.add(dimreg_all_regions);
    dimreg_hbox.add(dimreg_all_dimregs);
    dimreg_stereo.set_active();
    dimreg_hbox.add(dimreg_stereo);
    dimreg_vbox.add(dimreg_edit);
    dimreg_vbox.pack_start(dimreg_hbox, Gtk::PACK_SHRINK);
    m_HPaned.add2(dimreg_vbox);

    dimreg_label.set_tooltip_text(_("To automatically apply your changes above globally to the entire instrument, check all 3 check boxes on the right."));
    dimreg_all_regions.set_tooltip_text(_("If checked: all changes you perform above will automatically be applied to all regions of this instrument as well."));
    dimreg_all_dimregs.set_tooltip_text(_("If checked: all changes you perform above will automatically be applied as well to all dimension splits of the region selected below."));
    dimreg_stereo.set_tooltip_text(_("If checked: all changes you perform above will automatically be applied to both audio channel splits (only if a \"stereo\" dimension is defined below)."));

    m_TreeViewNotebook.append_page(m_ScrolledWindowSamples, _("Samples"));
    m_TreeViewNotebook.append_page(m_ScrolledWindow, _("Instruments"));
    m_TreeViewNotebook.append_page(m_ScrolledWindowScripts, _("Scripts"));

    actionGroup = Gtk::ActionGroup::create();

    actionGroup->add(Gtk::Action::create("MenuFile", _("_File")));
    actionGroup->add(Gtk::Action::create("New", Gtk::Stock::NEW),
                     sigc::mem_fun(
                         *this, &MainWindow::on_action_file_new));
    Glib::RefPtr<Gtk::Action> action =
        Gtk::Action::create("Open", Gtk::Stock::OPEN);
    action->property_label() = action->property_label() + "...";
    actionGroup->add(action,
                     sigc::mem_fun(
                         *this, &MainWindow::on_action_file_open));
    actionGroup->add(Gtk::Action::create("Save", Gtk::Stock::SAVE),
                     sigc::mem_fun(
                         *this, &MainWindow::on_action_file_save));
    action = Gtk::Action::create("SaveAs", Gtk::Stock::SAVE_AS);
    action->property_label() = action->property_label() + "...";
    actionGroup->add(action,
                     Gtk::AccelKey("<shift><control>s"),
                     sigc::mem_fun(
                         *this, &MainWindow::on_action_file_save_as));
    actionGroup->add(Gtk::Action::create("Properties",
                                         Gtk::Stock::PROPERTIES),
                     sigc::mem_fun(
                         *this, &MainWindow::on_action_file_properties));
    actionGroup->add(Gtk::Action::create("InstrProperties",
                                         Gtk::Stock::PROPERTIES),
                     sigc::mem_fun(
                         *this, &MainWindow::show_instr_props));
    actionGroup->add(Gtk::Action::create("MidiRules",
                                         _("_Midi Rules...")),
                     sigc::mem_fun(
                         *this, &MainWindow::show_midi_rules));
    actionGroup->add(Gtk::Action::create("ScriptSlots",
                                         _("_Script Slots...")),
                     sigc::mem_fun(
                         *this, &MainWindow::show_script_slots));
    actionGroup->add(Gtk::Action::create("Quit", Gtk::Stock::QUIT),
                     sigc::mem_fun(
                         *this, &MainWindow::on_action_quit));
    actionGroup->add(
        Gtk::Action::create("MenuSample", _("_Sample")),
        sigc::mem_fun(*this, &MainWindow::show_samples_tab)
    );
    actionGroup->add(
        Gtk::Action::create("MenuInstrument", _("_Instrument")),
        sigc::mem_fun(*this, &MainWindow::show_intruments_tab)
    );
    actionGroup->add(
        Gtk::Action::create("MenuScript", _("S_cript")),
        sigc::mem_fun(*this, &MainWindow::show_scripts_tab)
    );
    actionGroup->add(Gtk::Action::create("AllInstruments", _("_Select")));

    actionGroup->add(Gtk::Action::create("MenuEdit", _("_Edit")));

    Glib::RefPtr<Gtk::ToggleAction> toggle_action =
        Gtk::ToggleAction::create("CopySampleUnity", _("Copy Sample's _Unity Note"));
    toggle_action->set_active(true);
    actionGroup->add(toggle_action);

    toggle_action =
        Gtk::ToggleAction::create("CopySampleTune", _("Copy Sample's _Fine Tune"));
    toggle_action->set_active(true);
    actionGroup->add(toggle_action);

    toggle_action =
        Gtk::ToggleAction::create("CopySampleLoop", _("Copy Sample's _Loop Points"));
    toggle_action->set_active(true);
    actionGroup->add(toggle_action);


    actionGroup->add(Gtk::Action::create("MenuView", _("_View")));
    toggle_action =
        Gtk::ToggleAction::create("Statusbar", _("_Statusbar"));
    toggle_action->set_active(true);
    actionGroup->add(toggle_action,
                     sigc::mem_fun(
                         *this, &MainWindow::on_action_view_status_bar));

    action = Gtk::Action::create("MenuHelp", Gtk::Stock::HELP);
    actionGroup->add(Gtk::Action::create("MenuHelp",
                                         action->property_label()));
    actionGroup->add(Gtk::Action::create("About", Gtk::Stock::ABOUT),
                     sigc::mem_fun(
                         *this, &MainWindow::on_action_help_about));
    actionGroup->add(
        Gtk::Action::create("AddInstrument", _("Add _Instrument")),
        sigc::mem_fun(*this, &MainWindow::on_action_add_instrument)
    );
    actionGroup->add(
        Gtk::Action::create("DupInstrument", _("_Duplicate Instrument")),
        sigc::mem_fun(*this, &MainWindow::on_action_duplicate_instrument)
    );
    actionGroup->add(
        Gtk::Action::create("RemoveInstrument", Gtk::Stock::REMOVE),
        sigc::mem_fun(*this, &MainWindow::on_action_remove_instrument)
    );


    actionGroup->add(Gtk::Action::create("MenuSettings", _("_Settings")));
    
    toggle_action =
        Gtk::ToggleAction::create("WarnUserOnExtensions", _("Show warning on format _extensions"));
    toggle_action->set_active(Settings::singleton()->warnUserOnExtensions);
    actionGroup->add(
        toggle_action,
        sigc::mem_fun(*this, &MainWindow::on_action_warn_user_on_extensions)
    );

    toggle_action =
        Gtk::ToggleAction::create("SyncSamplerInstrumentSelection", _("Synchronize sampler's instrument selection"));
    toggle_action->set_active(Settings::singleton()->syncSamplerInstrumentSelection);
    actionGroup->add(
        toggle_action,
        sigc::mem_fun(*this, &MainWindow::on_action_sync_sampler_instrument_selection)
    );


    actionGroup->add(Gtk::Action::create("MenuTools", _("_Tools")));

    actionGroup->add(
        Gtk::Action::create("CombineInstruments", _("_Combine Instruments...")),
        sigc::mem_fun(*this, &MainWindow::on_action_combine_instruments)
    );

    actionGroup->add(
        Gtk::Action::create("MergeFiles", _("_Merge Files...")),
        sigc::mem_fun(*this, &MainWindow::on_action_merge_files)
    );


    // sample right-click popup actions
    actionGroup->add(
        Gtk::Action::create("SampleProperties", Gtk::Stock::PROPERTIES),
        sigc::mem_fun(*this, &MainWindow::on_action_sample_properties)
    );
    actionGroup->add(
        Gtk::Action::create("AddGroup", _("Add _Group")),
        sigc::mem_fun(*this, &MainWindow::on_action_add_group)
    );
    actionGroup->add(
        Gtk::Action::create("AddSample", _("Add _Sample(s)...")),
        sigc::mem_fun(*this, &MainWindow::on_action_add_sample)
    );
    actionGroup->add(
        Gtk::Action::create("RemoveSample", Gtk::Stock::REMOVE),
        sigc::mem_fun(*this, &MainWindow::on_action_remove_sample)
    );
    actionGroup->add(
        Gtk::Action::create("ShowSampleRefs", _("Show References...")),
        sigc::mem_fun(*this, &MainWindow::on_action_view_references)
    );
    actionGroup->add(
        Gtk::Action::create("ReplaceAllSamplesInAllGroups",
                            _("Replace All Samples in All Groups...")),
        sigc::mem_fun(*this, &MainWindow::on_action_replace_all_samples_in_all_groups)
    );
    
    // script right-click popup actions
    actionGroup->add(
        Gtk::Action::create("AddScriptGroup", _("Add _Group")),
        sigc::mem_fun(*this, &MainWindow::on_action_add_script_group)
    );
    actionGroup->add(
        Gtk::Action::create("AddScript", _("Add _Script")),
        sigc::mem_fun(*this, &MainWindow::on_action_add_script)
    );
    actionGroup->add(
        Gtk::Action::create("EditScript", _("_Edit Script...")),
        sigc::mem_fun(*this, &MainWindow::on_action_edit_script)
    );
    actionGroup->add(
        Gtk::Action::create("RemoveScript", Gtk::Stock::REMOVE),
        sigc::mem_fun(*this, &MainWindow::on_action_remove_script)
    );

    uiManager = Gtk::UIManager::create();
    uiManager->insert_action_group(actionGroup);
    add_accel_group(uiManager->get_accel_group());

    Glib::ustring ui_info =
        "<ui>"
        "  <menubar name='MenuBar'>"
        "    <menu action='MenuFile'>"
        "      <menuitem action='New'/>"
        "      <menuitem action='Open'/>"
        "      <separator/>"
        "      <menuitem action='Save'/>"
        "      <menuitem action='SaveAs'/>"
        "      <separator/>"
        "      <menuitem action='Properties'/>"
        "      <separator/>"
        "      <menuitem action='Quit'/>"
        "    </menu>"
        "    <menu action='MenuEdit'>"
        "      <menuitem action='CopySampleUnity'/>"
        "      <menuitem action='CopySampleTune'/>"
        "      <menuitem action='CopySampleLoop'/>"
        "    </menu>"
        "    <menu action='MenuSample'>"
        "      <menuitem action='SampleProperties'/>"
        "      <menuitem action='AddGroup'/>"
        "      <menuitem action='AddSample'/>"
        "      <menuitem action='ShowSampleRefs'/>"
        "      <menuitem action='ReplaceAllSamplesInAllGroups' />"
        "      <separator/>"
        "      <menuitem action='RemoveSample'/>"
        "    </menu>"
        "    <menu action='MenuInstrument'>"
        "      <menu action='AllInstruments'>"
        "      </menu>"
        "      <separator/>"
        "      <menuitem action='InstrProperties'/>"
        "      <menuitem action='MidiRules'/>"
        "      <menuitem action='ScriptSlots'/>"
        "      <menuitem action='AddInstrument'/>"
        "      <menuitem action='DupInstrument'/>"
        "      <separator/>"
        "      <menuitem action='RemoveInstrument'/>"
        "    </menu>"
        "    <menu action='MenuScript'>"
        "      <menuitem action='AddScriptGroup'/>"
        "      <menuitem action='AddScript'/>"
        "      <menuitem action='EditScript'/>"
        "      <separator/>"
        "      <menuitem action='RemoveScript'/>"
        "    </menu>"
        "    <menu action='MenuView'>"
        "      <menuitem action='Statusbar'/>"
        "    </menu>"
        "    <menu action='MenuTools'>"
        "      <menuitem action='CombineInstruments'/>"
        "      <menuitem action='MergeFiles'/>"
        "    </menu>"
        "    <menu action='MenuSettings'>"
        "      <menuitem action='WarnUserOnExtensions'/>"
        "      <menuitem action='SyncSamplerInstrumentSelection'/>"
        "    </menu>"
        "    <menu action='MenuHelp'>"
        "      <menuitem action='About'/>"
        "    </menu>"
        "  </menubar>"
        "  <popup name='PopupMenu'>"
        "    <menuitem action='InstrProperties'/>"
        "    <menuitem action='MidiRules'/>"
        "    <menuitem action='ScriptSlots'/>"
        "    <menuitem action='AddInstrument'/>"
        "    <menuitem action='DupInstrument'/>"
        "    <separator/>"
        "    <menuitem action='RemoveInstrument'/>"
        "  </popup>"
        "  <popup name='SamplePopupMenu'>"
        "    <menuitem action='SampleProperties'/>"
        "    <menuitem action='AddGroup'/>"
        "    <menuitem action='AddSample'/>"
        "    <menuitem action='ShowSampleRefs'/>"
        "    <menuitem action='ReplaceAllSamplesInAllGroups' />"
        "    <separator/>"
        "    <menuitem action='RemoveSample'/>"
        "  </popup>"
        "  <popup name='ScriptPopupMenu'>"
        "    <menuitem action='AddScriptGroup'/>"
        "    <menuitem action='AddScript'/>"
        "    <menuitem action='EditScript'/>"
        "    <separator/>"
        "    <menuitem action='RemoveScript'/>"
        "  </popup>"
        "</ui>";
    uiManager->add_ui_from_string(ui_info);

    popup_menu = dynamic_cast<Gtk::Menu*>(uiManager->get_widget("/PopupMenu"));
    
    // Set tooltips for menu items (for some reason, setting a tooltip on the
    // respective Gtk::Action objects above will simply be ignored, no matter
    // if using Gtk::Action::set_tooltip() or passing the tooltip string on
    // Gtk::Action::create()).
    {
        Gtk::MenuItem* item = dynamic_cast<Gtk::MenuItem*>(
            uiManager->get_widget("/MenuBar/MenuEdit/CopySampleUnity"));
        item->set_tooltip_text(_("Used when dragging a sample to a region's sample reference field. You may disable this for example if you want to replace an existing sample in a region with a new sample, but don't want that the region's current unity note setting will be altered by this action."));
    }
    {
        Gtk::MenuItem* item = dynamic_cast<Gtk::MenuItem*>(
            uiManager->get_widget("/MenuBar/MenuEdit/CopySampleTune"));
        item->set_tooltip_text(_("Used when dragging a sample to a region's sample reference field. You may disable this for example if you want to replace an existing sample in a region with a new sample, but don't want that the region's current sample playback tuning will be altered by this action."));
    }
    {
        Gtk::MenuItem* item = dynamic_cast<Gtk::MenuItem*>(
            uiManager->get_widget("/MenuBar/MenuEdit/CopySampleLoop"));
        item->set_tooltip_text(_("Used when dragging a sample to a region's sample reference field. You may disable this for example if you want to replace an existing sample in a region with a new sample, but don't want that the region's current loop informations to be altered by this action."));
    }
    {
        Gtk::MenuItem* item = dynamic_cast<Gtk::MenuItem*>(
            uiManager->get_widget("/MenuBar/MenuSettings/WarnUserOnExtensions"));
        item->set_tooltip_text(_("If checked, a warning will be shown whenever you try to use a feature which is based on a LinuxSampler extension ontop of the original gig format, which would not work with the Gigasampler/GigaStudio application."));
    }
    {
        Gtk::MenuItem* item = dynamic_cast<Gtk::MenuItem*>(
            uiManager->get_widget("/MenuBar/MenuSettings/SyncSamplerInstrumentSelection"));
        item->set_tooltip_text(_("If checked, the sampler's current instrument will automatically be switched whenever another instrument was selected in gigedit (only available in live-mode)."));
    }
    {
        Gtk::MenuItem* item = dynamic_cast<Gtk::MenuItem*>(
            uiManager->get_widget("/MenuBar/MenuTools/CombineInstruments"));
        item->set_tooltip_text(_("Create combi sounds out of individual sounds of this .gig file."));
    }
    {
        Gtk::MenuItem* item = dynamic_cast<Gtk::MenuItem*>(
            uiManager->get_widget("/MenuBar/MenuTools/MergeFiles"));
        item->set_tooltip_text(_("Add instruments and samples of other .gig files to this .gig file."));
    }


    instrument_menu = static_cast<Gtk::MenuItem*>(
        uiManager->get_widget("/MenuBar/MenuInstrument/AllInstruments"))->get_submenu();

    Gtk::Widget* menuBar = uiManager->get_widget("/MenuBar");
    m_VBox.pack_start(*menuBar, Gtk::PACK_SHRINK);
    m_VBox.pack_start(m_HPaned);
    m_VBox.pack_start(m_RegionChooser, Gtk::PACK_SHRINK);
    m_VBox.pack_start(m_RegionChooser.m_VirtKeybPropsBox, Gtk::PACK_SHRINK);
    m_VBox.pack_start(m_DimRegionChooser, Gtk::PACK_SHRINK);
    m_VBox.pack_start(m_StatusBar, Gtk::PACK_SHRINK);

    set_file_is_shared(false);

    // Status Bar:
    m_StatusBar.pack_start(m_AttachedStateLabel, Gtk::PACK_SHRINK);
    m_StatusBar.pack_start(m_AttachedStateImage, Gtk::PACK_SHRINK);
    m_StatusBar.show();

    m_RegionChooser.signal_region_selected().connect(
        sigc::mem_fun(*this, &MainWindow::region_changed) );
    m_DimRegionChooser.signal_dimregion_selected().connect(
        sigc::mem_fun(*this, &MainWindow::dimreg_changed) );


    // Create the Tree model:
    m_refTreeModel = Gtk::ListStore::create(m_Columns);
    m_TreeView.set_model(m_refTreeModel);
    m_TreeView.set_tooltip_text(_("Right click here for actions on instruments & MIDI Rules."));
    instrument_name_connection = m_refTreeModel->signal_row_changed().connect(
        sigc::mem_fun(*this, &MainWindow::instrument_name_changed)
    );

    // Add the TreeView's view columns:
    m_TreeView.append_column_editable("Instrument", m_Columns.m_col_name);
    m_TreeView.set_headers_visible(false);

    // create samples treeview (including its data model)
    m_refSamplesTreeModel = SamplesTreeStore::create(m_SamplesModel);
    m_TreeViewSamples.set_model(m_refSamplesTreeModel);
    m_TreeViewSamples.set_tooltip_text(_("To actually use a sample, drag it from this list view to \"Sample\" -> \"Sample:\" on the region's settings pane on the right.\n\nRight click here for more actions on samples."));
    // m_TreeViewSamples.set_reorderable();
    m_TreeViewSamples.append_column_editable(_("Name"), m_SamplesModel.m_col_name);
    m_TreeViewSamples.append_column(_("Referenced"), m_SamplesModel.m_col_refcount);
    {
        Gtk::TreeViewColumn* column = m_TreeViewSamples.get_column(0);
        Gtk::CellRendererText* cellrenderer =
            dynamic_cast<Gtk::CellRendererText*>(column->get_first_cell());
        column->add_attribute(
            cellrenderer->property_foreground(), m_SamplesModel.m_color
        );
    }
    {
        Gtk::TreeViewColumn* column = m_TreeViewSamples.get_column(1);
        Gtk::CellRendererText* cellrenderer =
            dynamic_cast<Gtk::CellRendererText*>(column->get_first_cell());
        column->add_attribute(
            cellrenderer->property_foreground(), m_SamplesModel.m_color
        );
    }
    m_TreeViewSamples.set_headers_visible(true);
    m_TreeViewSamples.signal_button_press_event().connect_notify(
        sigc::mem_fun(*this, &MainWindow::on_sample_treeview_button_release)
    );
    m_refSamplesTreeModel->signal_row_changed().connect(
        sigc::mem_fun(*this, &MainWindow::sample_name_changed)
    );

    // create scripts treeview (including its data model)
    m_refScriptsTreeModel = ScriptsTreeStore::create(m_ScriptsModel);
    m_TreeViewScripts.set_model(m_refScriptsTreeModel);
    m_TreeViewScripts.set_tooltip_text(_(
        "Use CTRL + double click for editing a script."
        "\n\n"
        "Note: instrument scripts are a LinuxSampler extension of the gig "
        "format. This feature will not work with the GigaStudio software!"
    ));
    // m_TreeViewScripts.set_reorderable();
    m_TreeViewScripts.append_column_editable("Samples", m_ScriptsModel.m_col_name);
    m_TreeViewScripts.set_headers_visible(false);
    m_TreeViewScripts.signal_button_press_event().connect_notify(
        sigc::mem_fun(*this, &MainWindow::on_script_treeview_button_release)
    );
    //FIXME: why the heck does this double click signal_row_activated() only fired while CTRL key is pressed ?
    m_TreeViewScripts.signal_row_activated().connect(
        sigc::mem_fun(*this, &MainWindow::script_double_clicked)
    );
    m_refScriptsTreeModel->signal_row_changed().connect(
        sigc::mem_fun(*this, &MainWindow::script_name_changed)
    );

    // establish drag&drop between scripts tree view and ScriptSlots window
    std::vector<Gtk::TargetEntry> drag_target_gig_script;
    drag_target_gig_script.push_back(Gtk::TargetEntry("gig::Script"));
    m_TreeViewScripts.drag_source_set(drag_target_gig_script);
    m_TreeViewScripts.signal_drag_begin().connect(
        sigc::mem_fun(*this, &MainWindow::on_scripts_treeview_drag_begin)
    );
    m_TreeViewScripts.signal_drag_data_get().connect(
        sigc::mem_fun(*this, &MainWindow::on_scripts_treeview_drag_data_get)
    );

    // establish drag&drop between samples tree view and dimension region 'Sample' text entry
    std::vector<Gtk::TargetEntry> drag_target_gig_sample;
    drag_target_gig_sample.push_back(Gtk::TargetEntry("gig::Sample"));
    m_TreeViewSamples.drag_source_set(drag_target_gig_sample);
    m_TreeViewSamples.signal_drag_begin().connect(
        sigc::mem_fun(*this, &MainWindow::on_sample_treeview_drag_begin)
    );
    m_TreeViewSamples.signal_drag_data_get().connect(
        sigc::mem_fun(*this, &MainWindow::on_sample_treeview_drag_data_get)
    );
    dimreg_edit.wSample->drag_dest_set(drag_target_gig_sample);
    dimreg_edit.wSample->signal_drag_data_received().connect(
        sigc::mem_fun(*this, &MainWindow::on_sample_label_drop_drag_data_received)
    );
    dimreg_edit.signal_dimreg_changed().connect(
        sigc::hide(sigc::mem_fun(*this, &MainWindow::file_changed)));
    m_RegionChooser.signal_instrument_changed().connect(
        sigc::mem_fun(*this, &MainWindow::file_changed));
    m_DimRegionChooser.signal_region_changed().connect(
        sigc::mem_fun(*this, &MainWindow::file_changed));
    instrumentProps.signal_changed().connect(
        sigc::mem_fun(*this, &MainWindow::file_changed));
    propDialog.signal_changed().connect(
        sigc::mem_fun(*this, &MainWindow::file_changed));
    midiRules.signal_changed().connect(
        sigc::mem_fun(*this, &MainWindow::file_changed));

    dimreg_edit.signal_dimreg_to_be_changed().connect(
        dimreg_to_be_changed_signal.make_slot());
    dimreg_edit.signal_dimreg_changed().connect(
        dimreg_changed_signal.make_slot());
    dimreg_edit.signal_sample_ref_changed().connect(
        sample_ref_changed_signal.make_slot());
    sample_ref_changed_signal.connect(
        sigc::mem_fun(*this, &MainWindow::on_sample_ref_changed)
    );
    samples_to_be_removed_signal.connect(
        sigc::mem_fun(*this, &MainWindow::on_samples_to_be_removed)
    );

    dimreg_edit.signal_select_sample().connect(
        sigc::mem_fun(*this, &MainWindow::select_sample)
    );

    m_RegionChooser.signal_instrument_struct_to_be_changed().connect(
        sigc::hide(
            sigc::bind(
                file_structure_to_be_changed_signal.make_slot(),
                sigc::ref(this->file)
            )
        )
    );
    m_RegionChooser.signal_instrument_struct_changed().connect(
        sigc::hide(
            sigc::bind(
                file_structure_changed_signal.make_slot(),
                sigc::ref(this->file)
            )
        )
    );
    m_RegionChooser.signal_region_to_be_changed().connect(
        region_to_be_changed_signal.make_slot());
    m_RegionChooser.signal_region_changed_signal().connect(
        region_changed_signal.make_slot());

    note_on_signal.connect(
        sigc::mem_fun(m_RegionChooser, &RegionChooser::on_note_on_event));
    note_off_signal.connect(
        sigc::mem_fun(m_RegionChooser, &RegionChooser::on_note_off_event));

    dimreg_all_regions.signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::update_dimregs));
    dimreg_all_dimregs.signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::dimreg_all_dimregs_toggled));
    dimreg_stereo.signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::update_dimregs));

    file = 0;
    file_is_changed = false;

    show_all_children();

    // start with a new gig file by default
    on_action_file_new();

    // select 'Instruments' tab by default
    // (gtk allows this only if the tab childs are visible, thats why it's here)
    m_TreeViewNotebook.set_current_page(1); 
}

MainWindow::~MainWindow()
{
}

bool MainWindow::on_delete_event(GdkEventAny* event)
{
    return !file_is_shared && file_is_changed && !close_confirmation_dialog();
}

void MainWindow::on_action_quit()
{
    if (!file_is_shared && file_is_changed && !close_confirmation_dialog()) return;
    hide();
}

void MainWindow::region_changed()
{
    m_DimRegionChooser.set_region(m_RegionChooser.get_region());
}

gig::Instrument* MainWindow::get_instrument()
{
    gig::Instrument* instrument = 0;
    Gtk::TreeModel::const_iterator it =
        m_TreeView.get_selection()->get_selected();
    if (it) {
        Gtk::TreeModel::Row row = *it;
        instrument = row[m_Columns.m_col_instr];
    }
    return instrument;
}

void MainWindow::add_region_to_dimregs(gig::Region* region, bool stereo, bool all_dimregs)
{
    if (all_dimregs) {
        for (int i = 0 ; i < region->DimensionRegions ; i++) {
            if (region->pDimensionRegions[i]) {
                dimreg_edit.dimregs.insert(region->pDimensionRegions[i]);
            }
        }
    } else {
        m_DimRegionChooser.get_dimregions(region, stereo, dimreg_edit.dimregs);
    }
}

void MainWindow::update_dimregs()
{
    dimreg_edit.dimregs.clear();
    bool all_regions = dimreg_all_regions.get_active();
    bool stereo = dimreg_stereo.get_active();
    bool all_dimregs = dimreg_all_dimregs.get_active();

    if (all_regions) {
        gig::Instrument* instrument = get_instrument();
        if (instrument) {
            for (gig::Region* region = instrument->GetFirstRegion() ;
                 region ;
                 region = instrument->GetNextRegion()) {
                add_region_to_dimregs(region, stereo, all_dimregs);
            }
        }
    } else {
        gig::Region* region = m_RegionChooser.get_region();
        if (region) {
            add_region_to_dimregs(region, stereo, all_dimregs);
        }
    }
}

void MainWindow::dimreg_all_dimregs_toggled()
{
    dimreg_stereo.set_sensitive(!dimreg_all_dimregs.get_active());
    update_dimregs();
}

void MainWindow::dimreg_changed()
{
    update_dimregs();
    dimreg_edit.set_dim_region(m_DimRegionChooser.get_main_dimregion());
}

void MainWindow::on_sel_change()
{
    // select item in instrument menu
    Gtk::TreeModel::iterator it = m_TreeView.get_selection()->get_selected();
    if (it) {
        Gtk::TreePath path(it);
        int index = path[0];
        const std::vector<Gtk::Widget*> children =
            instrument_menu->get_children();
        static_cast<Gtk::RadioMenuItem*>(children[index])->set_active();
    }

    m_RegionChooser.set_instrument(get_instrument());

    if (Settings::singleton()->syncSamplerInstrumentSelection) {
        switch_sampler_instrument_signal.emit(get_instrument());
    }
}

void loader_progress_callback(gig::progress_t* progress)
{
    Loader* loader = static_cast<Loader*>(progress->custom);
    loader->progress_callback(progress->factor);
}

void Loader::progress_callback(float fraction)
{
    {
        Glib::Threads::Mutex::Lock lock(progressMutex);
        progress = fraction;
    }
    progress_dispatcher();
}

void Loader::thread_function()
{
    printf("thread_function self=%x\n", Glib::Threads::Thread::self());
    printf("Start %s\n", filename.c_str());
    try {
        RIFF::File* riff = new RIFF::File(filename);
        gig = new gig::File(riff);
        gig::progress_t progress;
        progress.callback = loader_progress_callback;
        progress.custom = this;

        gig->GetInstrument(0, &progress);
        printf("End\n");
        finished_dispatcher();
    } catch (RIFF::Exception e) {
        error_message = e.Message;
        error_dispatcher.emit();
    } catch (...) {
        error_message = _("Unknown exception occurred");
        error_dispatcher.emit();
    }
}

Loader::Loader(const char* filename)
    : filename(filename), thread(0), progress(0.f)
{
}

void Loader::launch()
{
#ifdef OLD_THREADS
    thread = Glib::Thread::create(sigc::mem_fun(*this, &Loader::thread_function), true);
#else
    thread = Glib::Threads::Thread::create(sigc::mem_fun(*this, &Loader::thread_function));
#endif
    printf("launch thread=%x\n", thread);
}

float Loader::get_progress()
{
    float res;
    {
        Glib::Threads::Mutex::Lock lock(progressMutex);
        res = progress;
    }
    return res;
}

Glib::Dispatcher& Loader::signal_progress()
{
    return progress_dispatcher;
}

Glib::Dispatcher& Loader::signal_finished()
{
    return finished_dispatcher;
}

Glib::Dispatcher& Loader::signal_error()
{
    return error_dispatcher;
}

void saver_progress_callback(gig::progress_t* progress)
{
    Saver* saver = static_cast<Saver*>(progress->custom);
    saver->progress_callback(progress->factor);
}

void Saver::progress_callback(float fraction)
{
    {
        Glib::Threads::Mutex::Lock lock(progressMutex);
        progress = fraction;
    }
    progress_dispatcher.emit();
}

void Saver::thread_function()
{
    printf("thread_function self=%x\n", Glib::Threads::Thread::self());
    printf("Start %s\n", filename.c_str());
    try {
        gig::progress_t progress;
        progress.callback = saver_progress_callback;
        progress.custom = this;

        // if no filename was provided, that means "save", if filename was provided means "save as"
        if (filename.empty()) {
            gig->Save(&progress);
        } else {
            gig->Save(filename, &progress);
        }

        printf("End\n");
        finished_dispatcher.emit();
    } catch (RIFF::Exception e) {
        error_message = e.Message;
        error_dispatcher.emit();
    } catch (...) {
        error_message = _("Unknown exception occurred");
        error_dispatcher.emit();
    }
}

Saver::Saver(gig::File* file, Glib::ustring filename)
    : gig(file), filename(filename), thread(0), progress(0.f)
{
}

void Saver::launch()
{
#ifdef OLD_THREADS
    thread = Glib::Thread::create(sigc::mem_fun(*this, &Saver::thread_function), true);
#else
    thread = Glib::Threads::Thread::create(sigc::mem_fun(*this, &Saver::thread_function));
#endif
    printf("launch thread=%x\n", thread);
}

float Saver::get_progress()
{
    float res;
    {
        Glib::Threads::Mutex::Lock lock(progressMutex);
        res = progress;
    }
    return res;
}

Glib::Dispatcher& Saver::signal_progress()
{
    return progress_dispatcher;
}

Glib::Dispatcher& Saver::signal_finished()
{
    return finished_dispatcher;
}

Glib::Dispatcher& Saver::signal_error()
{
    return error_dispatcher;
}

ProgressDialog::ProgressDialog(const Glib::ustring& title, Gtk::Window& parent)
    : Gtk::Dialog(title, parent, true)
{
    get_vbox()->pack_start(progressBar);
    show_all_children();
    resize(600,50);
}

// Clear all GUI elements / controls. This method is typically called
// before a new .gig file is to be created or to be loaded.
void MainWindow::__clear() {
    // forget all samples that ought to be imported
    m_SampleImportQueue.clear();
    // clear the samples and instruments tree views
    m_refTreeModel->clear();
    m_refSamplesTreeModel->clear();
    m_refScriptsTreeModel->clear();
    // remove all entries from "Instrument" menu
    while (!instrument_menu->get_children().empty()) {
        remove_instrument_from_menu(0);
    }
    // free libgig's gig::File instance
    if (file && !file_is_shared) delete file;
    file = NULL;
    set_file_is_shared(false);
}

void MainWindow::__refreshEntireGUI() {
    // clear the samples and instruments tree views
    m_refTreeModel->clear();
    m_refSamplesTreeModel->clear();
    m_refScriptsTreeModel->clear();
    // remove all entries from "Instrument" menu
    while (!instrument_menu->get_children().empty()) {
        remove_instrument_from_menu(0);
    }

    if (!this->file) return;

    load_gig(
        this->file, this->file->pInfo->Name.c_str(), this->file_is_shared
    );
}

void MainWindow::on_action_file_new()
{
    if (!file_is_shared && file_is_changed && !close_confirmation_dialog()) return;

    if (file_is_shared && !leaving_shared_mode_dialog()) return;

    // clear all GUI elements
    __clear();
    // create a new .gig file (virtually yet)
    gig::File* pFile = new gig::File;
    // already add one new instrument by default
    gig::Instrument* pInstrument = pFile->AddInstrument();
    pInstrument->pInfo->Name = gig_from_utf8(_("Unnamed Instrument"));
    // update GUI with that new gig::File
    load_gig(pFile, 0 /*no file name yet*/);
}

bool MainWindow::close_confirmation_dialog()
{
    gchar* msg = g_strdup_printf(_("Save changes to \"%s\" before closing?"),
                                 Glib::filename_display_basename(filename).c_str());
    Gtk::MessageDialog dialog(*this, msg, false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_NONE);
    g_free(msg);
    dialog.set_secondary_text(_("If you close without saving, your changes will be lost."));
    dialog.add_button(_("Close _Without Saving"), Gtk::RESPONSE_NO);
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button(file_has_name ? Gtk::Stock::SAVE : Gtk::Stock::SAVE_AS, Gtk::RESPONSE_YES);
    dialog.set_default_response(Gtk::RESPONSE_YES);
    int response = dialog.run();
    dialog.hide();

    // user decided to exit app without saving
    if (response == Gtk::RESPONSE_NO) return true;

    // user cancelled dialog, thus don't close app
    if (response == Gtk::RESPONSE_CANCEL) return false;

    // TODO: the following return valid is disabled and hard coded instead for
    // now, due to the fact that saving with progress bar is now implemented
    // asynchronously, as a result the app does not close automatically anymore
    // after saving the file has completed
    //
    //   if (response == Gtk::RESPONSE_YES) return file_save();
    //   return response != Gtk::RESPONSE_CANCEL;
    //
    if (response == Gtk::RESPONSE_YES) file_save();
    return false; // always prevent closing the app for now (see comment above)
}

bool MainWindow::leaving_shared_mode_dialog() {
    Glib::ustring msg = _("Detach from sampler and proceed working stand-alone?");
    Gtk::MessageDialog dialog(*this, msg, false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_NONE);
    dialog.set_secondary_text(
        _("If you proceed to work on another instrument file, it won't be "
          "used by the sampler until you tell the sampler explicitly to "
          "load it."));
    dialog.add_button(_("_Yes, Detach"), Gtk::RESPONSE_YES);
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.set_default_response(Gtk::RESPONSE_CANCEL);
    int response = dialog.run();
    dialog.hide();
    return response == Gtk::RESPONSE_YES;
}

void MainWindow::on_action_file_open()
{
    if (!file_is_shared && file_is_changed && !close_confirmation_dialog()) return;

    if (file_is_shared && !leaving_shared_mode_dialog()) return;

    Gtk::FileChooserDialog dialog(*this, _("Open file"));
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
    dialog.set_default_response(Gtk::RESPONSE_OK);
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
    Gtk::FileFilter filter;
    filter.add_pattern("*.gig");
#else
    Glib::RefPtr<Gtk::FileFilter> filter = Gtk::FileFilter::create();
    filter->add_pattern("*.gig");
#endif
    dialog.set_filter(filter);
    if (current_gig_dir != "") {
        dialog.set_current_folder(current_gig_dir);
    }
    if (dialog.run() == Gtk::RESPONSE_OK) {
        std::string filename = dialog.get_filename();
        printf("filename=%s\n", filename.c_str());
        printf("on_action_file_open self=%x\n", Glib::Threads::Thread::self());
        load_file(filename.c_str());
        current_gig_dir = Glib::path_get_dirname(filename);
    }
}

void MainWindow::load_file(const char* name)
{
    __clear();

    progress_dialog = new ProgressDialog( //FIXME: memory leak!
        _("Loading") +  Glib::ustring(" '") +
        Glib::filename_display_basename(name) + "' ...",
        *this
    );
    progress_dialog->show_all();
    loader = new Loader(name); //FIXME: memory leak!
    loader->signal_progress().connect(
        sigc::mem_fun(*this, &MainWindow::on_loader_progress));
    loader->signal_finished().connect(
        sigc::mem_fun(*this, &MainWindow::on_loader_finished));
    loader->signal_error().connect(
        sigc::mem_fun(*this, &MainWindow::on_loader_error));
    loader->launch();
}

void MainWindow::load_instrument(gig::Instrument* instr) {
    if (!instr) {
        Glib::ustring txt = "Provided instrument is NULL!\n";
        Gtk::MessageDialog msg(*this, txt, false, Gtk::MESSAGE_ERROR);
        msg.run();
        Gtk::Main::quit();
    }
    // clear all GUI elements
    __clear();
    // load the instrument
    gig::File* pFile = (gig::File*) instr->GetParent();
    load_gig(pFile, 0 /*file name*/, true /*shared instrument*/);
    // automatically select the given instrument
    int i = 0;
    for (gig::Instrument* instrument = pFile->GetFirstInstrument(); instrument;
         instrument = pFile->GetNextInstrument(), ++i)
    {
        if (instrument == instr) {
            // select item in "instruments" tree view
            m_TreeView.get_selection()->select(Gtk::TreePath(ToString(i)));
            // make sure the selected item in the "instruments" tree view is
            // visible (scroll to it)
            m_TreeView.scroll_to_row(Gtk::TreePath(ToString(i)));
            // select item in instrument menu
            {
                const std::vector<Gtk::Widget*> children =
                    instrument_menu->get_children();
                static_cast<Gtk::RadioMenuItem*>(children[i])->set_active();
            }
            // update region chooser and dimension region chooser
            m_RegionChooser.set_instrument(instr);
            break;
        }
    }
}

void MainWindow::on_loader_progress()
{
    progress_dialog->set_fraction(loader->get_progress());
}

void MainWindow::on_loader_finished()
{
    printf("Loader finished!\n");
    printf("on_loader_finished self=%x\n", Glib::Threads::Thread::self());
    load_gig(loader->gig, loader->filename.c_str());
    progress_dialog->hide();
}

void MainWindow::on_loader_error()
{
    Glib::ustring txt = _("Could not load file: ") + loader->error_message;
    Gtk::MessageDialog msg(*this, txt, false, Gtk::MESSAGE_ERROR);
    msg.run();
    progress_dialog->hide();
}

void MainWindow::on_action_file_save()
{
    file_save();
}

bool MainWindow::check_if_savable()
{
    if (!file) return false;

    if (!file->GetFirstSample()) {
        Gtk::MessageDialog(*this, _("The file could not be saved "
                                    "because it contains no samples"),
                           false, Gtk::MESSAGE_ERROR).run();
        return false;
    }

    for (gig::Instrument* instrument = file->GetFirstInstrument() ; instrument ;
         instrument = file->GetNextInstrument()) {
        if (!instrument->GetFirstRegion()) {
            Gtk::MessageDialog(*this, _("The file could not be saved "
                                        "because there are instruments "
                                        "that have no regions"),
                               false, Gtk::MESSAGE_ERROR).run();
            return false;
        }
    }
    return true;
}

bool MainWindow::file_save()
{
    if (!check_if_savable()) return false;
    if (!file_is_shared && !file_has_name) return file_save_as();

    std::cout << "Saving file\n" << std::flush;
    file_structure_to_be_changed_signal.emit(this->file);

    progress_dialog = new ProgressDialog( //FIXME: memory leak!
        _("Saving") +  Glib::ustring(" '") +
        Glib::filename_display_basename(this->filename) + "' ...",
        *this
    );
    progress_dialog->show_all();
    saver = new Saver(this->file); //FIXME: memory leak!
    saver->signal_progress().connect(
        sigc::mem_fun(*this, &MainWindow::on_saver_progress));
    saver->signal_finished().connect(
        sigc::mem_fun(*this, &MainWindow::on_saver_finished));
    saver->signal_error().connect(
        sigc::mem_fun(*this, &MainWindow::on_saver_error));
    saver->launch();

    return true;
}

void MainWindow::on_saver_progress()
{
    progress_dialog->set_fraction(saver->get_progress());
}

void MainWindow::on_saver_error()
{
    file_structure_changed_signal.emit(this->file);
    Glib::ustring txt = _("Could not save file: ") + saver->error_message;
    Gtk::MessageDialog msg(*this, txt, false, Gtk::MESSAGE_ERROR);
    msg.run();
}

void MainWindow::on_saver_finished()
{
    this->file = saver->gig;
    this->filename = saver->filename;
    current_gig_dir = Glib::path_get_dirname(filename);
    set_title(Glib::filename_display_basename(filename));
    file_has_name = true;
    file_is_changed = false;
    std::cout << "Saving file done. Importing queued samples now ...\n" << std::flush;
    __import_queued_samples();
    std::cout << "Importing queued samples done.\n" << std::flush;

    file_structure_changed_signal.emit(this->file);

    load_gig(this->file, this->filename.c_str());
    progress_dialog->hide();
}

void MainWindow::on_action_file_save_as()
{
    if (!check_if_savable()) return;
    file_save_as();
}

bool MainWindow::file_save_as()
{
    Gtk::FileChooserDialog dialog(*this, _("Save as"), Gtk::FILE_CHOOSER_ACTION_SAVE);
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);
    dialog.set_default_response(Gtk::RESPONSE_OK);
    dialog.set_do_overwrite_confirmation();

#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
    Gtk::FileFilter filter;
    filter.add_pattern("*.gig");
#else
    Glib::RefPtr<Gtk::FileFilter> filter = Gtk::FileFilter::create();
    filter->add_pattern("*.gig");
#endif
    dialog.set_filter(filter);

    // set initial dir and filename of the Save As dialog
    // and prepare that initial filename as a copy of the gig
    {
        std::string basename = Glib::path_get_basename(filename);
        std::string dir = Glib::path_get_dirname(filename);
        basename = std::string(_("copy_of_")) + basename;
        Glib::ustring copyFileName = Glib::build_filename(dir, basename);
        if (Glib::path_is_absolute(filename)) {
            dialog.set_filename(copyFileName);
        } else {
            if (current_gig_dir != "") dialog.set_current_folder(current_gig_dir);
        }
        dialog.set_current_name(Glib::filename_display_basename(copyFileName));
    }

    // show warning in the dialog
    Gtk::HBox descriptionArea;
    descriptionArea.set_spacing(15);
    Gtk::Image warningIcon(Gtk::Stock::DIALOG_WARNING, Gtk::IconSize(Gtk::ICON_SIZE_DIALOG));
    descriptionArea.pack_start(warningIcon, Gtk::PACK_SHRINK);
#if GTKMM_MAJOR_VERSION < 3
    view::WrapLabel description;
#else
    Gtk::Label description;
    description.set_line_wrap();
#endif
    description.set_markup(
        _("\n<b>CAUTION:</b> You <b>MUST</b> use the "
          "<span style=\"italic\">\"Save\"</span> dialog instead of "
          "<span style=\"italic\">\"Save As...\"</span> if you want to save "
          "to the same .gig file. Using "
          "<span style=\"italic\">\"Save As...\"</span> for writing to the "
          "same .gig file will end up in corrupted sample wave data!\n")
    );
    descriptionArea.pack_start(description);
    dialog.get_vbox()->pack_start(descriptionArea, Gtk::PACK_SHRINK);
    descriptionArea.show_all();

    if (dialog.run() == Gtk::RESPONSE_OK) {
        std::string filename = dialog.get_filename();
        if (!Glib::str_has_suffix(filename, ".gig")) {
            filename += ".gig";
        }
        printf("filename=%s\n", filename.c_str());

        progress_dialog = new ProgressDialog( //FIXME: memory leak!
            _("Saving") +  Glib::ustring(" '") +
            Glib::filename_display_basename(filename) + "' ...",
            *this
        );
        progress_dialog->show_all();

        saver = new Saver(file, filename); //FIXME: memory leak!
        saver->signal_progress().connect(
            sigc::mem_fun(*this, &MainWindow::on_saver_progress));
        saver->signal_finished().connect(
            sigc::mem_fun(*this, &MainWindow::on_saver_finished));
        saver->signal_error().connect(
            sigc::mem_fun(*this, &MainWindow::on_saver_error));
        saver->launch();

        return true;
    }
    return false;
}

// actually write the sample(s)' data to the gig file
void MainWindow::__import_queued_samples() {
    std::cout << "Starting sample import\n" << std::flush;
    Glib::ustring error_files;
    printf("Samples to import: %d\n", m_SampleImportQueue.size());
    for (std::list<SampleImportItem>::iterator iter = m_SampleImportQueue.begin();
         iter != m_SampleImportQueue.end(); ) {
        printf("Importing sample %s\n",(*iter).sample_path.c_str());
        SF_INFO info;
        info.format = 0;
        SNDFILE* hFile = sf_open((*iter).sample_path.c_str(), SFM_READ, &info);
        sf_command(hFile, SFC_SET_SCALE_FLOAT_INT_READ, 0, SF_TRUE);
        try {
            if (!hFile) throw std::string(_("could not open file"));
            // determine sample's bit depth
            int bitdepth;
            switch (info.format & 0xff) {
                case SF_FORMAT_PCM_S8:
                case SF_FORMAT_PCM_16:
                case SF_FORMAT_PCM_U8:
                    bitdepth = 16;
                    break;
                case SF_FORMAT_PCM_24:
                case SF_FORMAT_PCM_32:
                case SF_FORMAT_FLOAT:
                case SF_FORMAT_DOUBLE:
                    bitdepth = 24;
                    break;
                default:
                    sf_close(hFile); // close sound file
                    throw std::string(_("format not supported")); // unsupported subformat (yet?)
            }

            const int bufsize = 10000;
            switch (bitdepth) {
                case 16: {
                    short* buffer = new short[bufsize * info.channels];
                    sf_count_t cnt = info.frames;
                    while (cnt) {
                        // libsndfile does the conversion for us (if needed)
                        int n = sf_readf_short(hFile, buffer, bufsize);
                        // write from buffer directly (physically) into .gig file
                        iter->gig_sample->Write(buffer, n);
                        cnt -= n;
                    }
                    delete[] buffer;
                    break;
                }
                case 24: {
                    int* srcbuf = new int[bufsize * info.channels];
                    uint8_t* dstbuf = new uint8_t[bufsize * 3 * info.channels];
                    sf_count_t cnt = info.frames;
                    while (cnt) {
                        // libsndfile returns 32 bits, convert to 24
                        int n = sf_readf_int(hFile, srcbuf, bufsize);
                        int j = 0;
                        for (int i = 0 ; i < n * info.channels ; i++) {
                            dstbuf[j++] = srcbuf[i] >> 8;
                            dstbuf[j++] = srcbuf[i] >> 16;
                            dstbuf[j++] = srcbuf[i] >> 24;
                        }
                        // write from buffer directly (physically) into .gig file
                        iter->gig_sample->Write(dstbuf, n);
                        cnt -= n;
                    }
                    delete[] srcbuf;
                    delete[] dstbuf;
                    break;
                }
            }
            // cleanup
            sf_close(hFile);
            // let the sampler re-cache the sample if needed
            sample_changed_signal.emit(iter->gig_sample);
            // on success we remove the sample from the import queue,
            // otherwise keep it, maybe it works the next time ?
            std::list<SampleImportItem>::iterator cur = iter;
            ++iter;
            m_SampleImportQueue.erase(cur);
        } catch (std::string what) {
            // remember the files that made trouble (and their cause)
            if (!error_files.empty()) error_files += "\n";
            error_files += (*iter).sample_path += " (" + what + ")";
            ++iter;
        }
    }
    // show error message box when some sample(s) could not be imported
    if (!error_files.empty()) {
        Glib::ustring txt = _("Could not import the following sample(s):\n") + error_files;
        Gtk::MessageDialog msg(*this, txt, false, Gtk::MESSAGE_ERROR);
        msg.run();
    }
}

void MainWindow::on_action_file_properties()
{
    propDialog.show();
    propDialog.deiconify();
}

void MainWindow::on_action_warn_user_on_extensions() {
    Settings::singleton()->warnUserOnExtensions =
        !Settings::singleton()->warnUserOnExtensions;
}

void MainWindow::on_action_sync_sampler_instrument_selection() {
    Settings::singleton()->syncSamplerInstrumentSelection =
        !Settings::singleton()->syncSamplerInstrumentSelection;
}

void MainWindow::on_action_help_about()
{
    Gtk::AboutDialog dialog;
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION >= 12) || GTKMM_MAJOR_VERSION > 2
    dialog.set_program_name("Gigedit");
#else
    dialog.set_name("Gigedit");
#endif
    dialog.set_version(VERSION);
    dialog.set_copyright("Copyright (C) 2006-2015 Andreas Persson");
    const std::string sComment =
        _("Built " __DATE__ "\nUsing ") +
        ::gig::libraryName() + " " + ::gig::libraryVersion() + "\n\n" +
        _(
            "Gigedit is released under the GNU General Public License.\n"
            "\n"
            "This program is distributed WITHOUT ANY WARRANTY; So better "
            "backup your Gigasampler/GigaStudio files before editing them with "
            "this application.\n"
            "\n"
            "Please report bugs to: http://bugs.linuxsampler.org"
        );
    dialog.set_comments(sComment.c_str());
    dialog.set_website("http://www.linuxsampler.org");
    dialog.set_website_label("http://www.linuxsampler.org");
    dialog.run();
}

PropDialog::PropDialog()
    : eFileFormat(_("File Format")),
      eName(_("Name")),
      eCreationDate(_("Creation date")),
      eComments(_("Comments")),
      eProduct(_("Product")),
      eCopyright(_("Copyright")),
      eArtists(_("Artists")),
      eGenre(_("Genre")),
      eKeywords(_("Keywords")),
      eEngineer(_("Engineer")),
      eTechnician(_("Technician")),
      eSoftware(_("Software")),
      eMedium(_("Medium")),
      eSource(_("Source")),
      eSourceForm(_("Source form")),
      eCommissioned(_("Commissioned")),
      eSubject(_("Subject")),
      quitButton(Gtk::Stock::CLOSE),
      table(2, 1),
      m_file(NULL)
{
    set_title(_("File Properties"));
    eName.set_width_chars(50);

    connect(eName, &DLS::Info::Name);
    connect(eCreationDate, &DLS::Info::CreationDate);
    connect(eComments, &DLS::Info::Comments);
    connect(eProduct, &DLS::Info::Product);
    connect(eCopyright, &DLS::Info::Copyright);
    connect(eArtists, &DLS::Info::Artists);
    connect(eGenre, &DLS::Info::Genre);
    connect(eKeywords, &DLS::Info::Keywords);
    connect(eEngineer, &DLS::Info::Engineer);
    connect(eTechnician, &DLS::Info::Technician);
    connect(eSoftware, &DLS::Info::Software);
    connect(eMedium, &DLS::Info::Medium);
    connect(eSource, &DLS::Info::Source);
    connect(eSourceForm, &DLS::Info::SourceForm);
    connect(eCommissioned, &DLS::Info::Commissioned);
    connect(eSubject, &DLS::Info::Subject);

    table.add(eFileFormat);
    table.add(eName);
    table.add(eCreationDate);
    table.add(eComments);
    table.add(eProduct);
    table.add(eCopyright);
    table.add(eArtists);
    table.add(eGenre);
    table.add(eKeywords);
    table.add(eEngineer);
    table.add(eTechnician);
    table.add(eSoftware);
    table.add(eMedium);
    table.add(eSource);
    table.add(eSourceForm);
    table.add(eCommissioned);
    table.add(eSubject);

    table.set_col_spacings(5);
    add(vbox);
    table.set_border_width(5);
    vbox.add(table);
    vbox.pack_start(buttonBox, Gtk::PACK_SHRINK);
    buttonBox.set_layout(Gtk::BUTTONBOX_END);
    buttonBox.set_border_width(5);
    buttonBox.show();
    buttonBox.pack_start(quitButton);
    quitButton.set_can_default();
    quitButton.grab_focus();
    quitButton.signal_clicked().connect(
        sigc::mem_fun(*this, &PropDialog::hide));
    eFileFormat.signal_value_changed().connect(
        sigc::mem_fun(*this, &PropDialog::onFileFormatChanged));

    quitButton.show();
    vbox.show();
    show_all_children();
}

void PropDialog::set_file(gig::File* file)
{
    m_file = file;

    // update file format version combo box
    const std::string sGiga = "Gigasampler/GigaStudio v";
    const int major = file->pVersion->major;
    std::vector<std::string> txts;
    std::vector<int> values;
    txts.push_back(sGiga + "2"); values.push_back(2);
    txts.push_back(sGiga + "3/v4"); values.push_back(3);
    if (major != 2 && major != 3) {
        txts.push_back(sGiga + ToString(major)); values.push_back(major);
    }
    std::vector<const char*> texts;
    for (int i = 0; i < txts.size(); ++i) texts.push_back(txts[i].c_str());
    texts.push_back(NULL); values.push_back(0);
    eFileFormat.set_choices(&texts[0], &values[0]);
    eFileFormat.set_value(major);
}

void PropDialog::onFileFormatChanged() {
    const int major = eFileFormat.get_value();
    if (m_file) m_file->pVersion->major = major;
}

void PropDialog::set_info(DLS::Info* info)
{
    update(info);
}


void InstrumentProps::set_Name(const gig::String& name)
{
    m->pInfo->Name = name;
}

void InstrumentProps::update_name()
{
    update_model++;
    eName.set_value(m->pInfo->Name);
    update_model--;
}

void InstrumentProps::set_IsDrum(bool value)
{
    m->IsDrum = value;
}

void InstrumentProps::set_MIDIBank(uint16_t value)
{
    m->MIDIBank = value;
}

void InstrumentProps::set_MIDIProgram(uint32_t value)
{
    m->MIDIProgram = value;
}

InstrumentProps::InstrumentProps() :
    quitButton(Gtk::Stock::CLOSE),
    table(2,1),
    eName(_("Name")),
    eIsDrum(_("Is drum")),
    eMIDIBank(_("MIDI bank"), 0, 16383),
    eMIDIProgram(_("MIDI program")),
    eAttenuation(_("Attenuation"), 0, 96, 0, 1),
    eGainPlus6(_("Gain +6dB"), eAttenuation, -6),
    eEffectSend(_("Effect send"), 0, 65535),
    eFineTune(_("Fine tune"), -8400, 8400),
    ePitchbendRange(_("Pitchbend range"), 0, 12),
    ePianoReleaseMode(_("Piano release mode")),
    eDimensionKeyRangeLow(_("Keyswitching range low")),
    eDimensionKeyRangeHigh(_("Keyswitching range high"))
{
    set_title(_("Instrument Properties"));

    eDimensionKeyRangeLow.set_tip(
        _("start of the keyboard area which should switch the "
          "\"keyswitching\" dimension")
    );
    eDimensionKeyRangeHigh.set_tip(
        _("end of the keyboard area which should switch the "
          "\"keyswitching\" dimension")
    );

    connect(eName, &InstrumentProps::set_Name);
    connect(eIsDrum, &InstrumentProps::set_IsDrum);
    connect(eMIDIBank, &InstrumentProps::set_MIDIBank);
    connect(eMIDIProgram, &InstrumentProps::set_MIDIProgram);
    connect(eAttenuation, &gig::Instrument::Attenuation);
    connect(eGainPlus6, &gig::Instrument::Attenuation);
    connect(eEffectSend, &gig::Instrument::EffectSend);
    connect(eFineTune, &gig::Instrument::FineTune);
    connect(ePitchbendRange, &gig::Instrument::PitchbendRange);
    connect(ePianoReleaseMode, &gig::Instrument::PianoReleaseMode);
    connect(eDimensionKeyRangeLow, eDimensionKeyRangeHigh,
            &gig::Instrument::DimensionKeyRange);

    eName.signal_value_changed().connect(sig_name_changed.make_slot());

    table.set_col_spacings(5);

    table.add(eName);
    table.add(eIsDrum);
    table.add(eMIDIBank);
    table.add(eMIDIProgram);
    table.add(eAttenuation);
    table.add(eGainPlus6);
    table.add(eEffectSend);
    table.add(eFineTune);
    table.add(ePitchbendRange);
    table.add(ePianoReleaseMode);
    table.add(eDimensionKeyRangeLow);
    table.add(eDimensionKeyRangeHigh);

    add(vbox);
    table.set_border_width(5);
    vbox.pack_start(table);
    table.show();
    vbox.pack_start(buttonBox, Gtk::PACK_SHRINK);
    buttonBox.set_layout(Gtk::BUTTONBOX_END);
    buttonBox.set_border_width(5);
    buttonBox.show();
    buttonBox.pack_start(quitButton);
    quitButton.set_can_default();
    quitButton.grab_focus();

    quitButton.signal_clicked().connect(
        sigc::mem_fun(*this, &InstrumentProps::hide));

    quitButton.show();
    vbox.show();
    show_all_children();
}

void InstrumentProps::set_instrument(gig::Instrument* instrument)
{
    update(instrument);

    update_model++;
    eName.set_value(instrument->pInfo->Name);
    eIsDrum.set_value(instrument->IsDrum);
    eMIDIBank.set_value(instrument->MIDIBank);
    eMIDIProgram.set_value(instrument->MIDIProgram);
    update_model--;
}


void MainWindow::file_changed()
{
    if (file && !file_is_changed) {
        set_title("*" + get_title());
        file_is_changed = true;
    }
}

void MainWindow::updateSampleRefCountMap(gig::File* gig) {
    sample_ref_count.clear();
    
    if (!gig) return;

    for (gig::Instrument* instrument = gig->GetFirstInstrument(); instrument;
         instrument = gig->GetNextInstrument())
    {
        for (gig::Region* rgn = instrument->GetFirstRegion(); rgn;
             rgn = instrument->GetNextRegion())
        {
            for (int i = 0; i < 256; ++i) {
                if (!rgn->pDimensionRegions[i]) continue;
                if (rgn->pDimensionRegions[i]->pSample) {
                    sample_ref_count[rgn->pDimensionRegions[i]->pSample]++;
                }
            }
        }
    }
}

void MainWindow::load_gig(gig::File* gig, const char* filename, bool isSharedInstrument)
{
    file = 0;
    set_file_is_shared(isSharedInstrument);

    this->filename = filename ? filename : _("Unsaved Gig File");
    set_title(Glib::filename_display_basename(this->filename));
    file_has_name = filename;
    file_is_changed = false;

    propDialog.set_file(gig);
    propDialog.set_info(gig->pInfo);

    instrument_name_connection.block();
    for (gig::Instrument* instrument = gig->GetFirstInstrument() ; instrument ;
         instrument = gig->GetNextInstrument()) {
        Glib::ustring name(gig_to_utf8(instrument->pInfo->Name));

        Gtk::TreeModel::iterator iter = m_refTreeModel->append();
        Gtk::TreeModel::Row row = *iter;
        row[m_Columns.m_col_name] = name;
        row[m_Columns.m_col_instr] = instrument;

        add_instrument_to_menu(name);
    }
    instrument_name_connection.unblock();
    uiManager->get_widget("/MenuBar/MenuInstrument/AllInstruments")->show();

    updateSampleRefCountMap(gig);

    for (gig::Group* group = gig->GetFirstGroup(); group; group = gig->GetNextGroup()) {
        if (group->Name != "") {
            Gtk::TreeModel::iterator iterGroup = m_refSamplesTreeModel->append();
            Gtk::TreeModel::Row rowGroup = *iterGroup;
            rowGroup[m_SamplesModel.m_col_name]   = gig_to_utf8(group->Name);
            rowGroup[m_SamplesModel.m_col_group]  = group;
            rowGroup[m_SamplesModel.m_col_sample] = NULL;
            for (gig::Sample* sample = group->GetFirstSample();
                 sample; sample = group->GetNextSample()) {
                Gtk::TreeModel::iterator iterSample =
                    m_refSamplesTreeModel->append(rowGroup.children());
                Gtk::TreeModel::Row rowSample = *iterSample;
                rowSample[m_SamplesModel.m_col_name] =
                    gig_to_utf8(sample->pInfo->Name);
                rowSample[m_SamplesModel.m_col_sample] = sample;
                rowSample[m_SamplesModel.m_col_group]  = NULL;
                int refcount = sample_ref_count.count(sample) ? sample_ref_count[sample] : 0;
                rowSample[m_SamplesModel.m_col_refcount] = ToString(refcount) + " " + _("Refs.");
                rowSample[m_SamplesModel.m_color] = refcount ? "black" : "red";
            }
        }
    }
    
    for (int i = 0; gig->GetScriptGroup(i); ++i) {
        gig::ScriptGroup* group = gig->GetScriptGroup(i);

        Gtk::TreeModel::iterator iterGroup = m_refScriptsTreeModel->append();
        Gtk::TreeModel::Row rowGroup = *iterGroup;
        rowGroup[m_ScriptsModel.m_col_name]   = gig_to_utf8(group->Name);
        rowGroup[m_ScriptsModel.m_col_group]  = group;
        rowGroup[m_ScriptsModel.m_col_script] = NULL;
        for (int s = 0; group->GetScript(s); ++s) {
            gig::Script* script = group->GetScript(s);

            Gtk::TreeModel::iterator iterScript =
                m_refScriptsTreeModel->append(rowGroup.children());
            Gtk::TreeModel::Row rowScript = *iterScript;
            rowScript[m_ScriptsModel.m_col_name] = gig_to_utf8(script->Name);
            rowScript[m_ScriptsModel.m_col_script] = script;
            rowScript[m_ScriptsModel.m_col_group]  = NULL;
        }
    }
    // unfold all sample groups & script groups by default
    m_TreeViewSamples.expand_all();
    m_TreeViewScripts.expand_all();

    file = gig;

    // select the first instrument
    m_TreeView.get_selection()->select(Gtk::TreePath("0"));

    instr_props_set_instrument();
    gig::Instrument* instrument = get_instrument();
    if (instrument) {
        midiRules.set_instrument(instrument);
    }
}

bool MainWindow::instr_props_set_instrument()
{
    instrumentProps.signal_name_changed().clear();

    Gtk::TreeModel::const_iterator it =
        m_TreeView.get_selection()->get_selected();
    if (it) {
        Gtk::TreeModel::Row row = *it;
        gig::Instrument* instrument = row[m_Columns.m_col_instr];

        instrumentProps.set_instrument(instrument);

        // make sure instrument tree is updated when user changes the
        // instrument name in instrument properties window
        instrumentProps.signal_name_changed().connect(
            sigc::bind(
                sigc::mem_fun(*this, 
                              &MainWindow::instr_name_changed_by_instr_props),
                it));
    } else {
        instrumentProps.hide();
    }
    return it;
}

void MainWindow::show_instr_props()
{
    if (instr_props_set_instrument()) {
        instrumentProps.show();
        instrumentProps.deiconify();
    }
}

void MainWindow::instr_name_changed_by_instr_props(Gtk::TreeModel::iterator& it)
{
    Gtk::TreeModel::Row row = *it;
    Glib::ustring name = row[m_Columns.m_col_name];

    gig::Instrument* instrument = row[m_Columns.m_col_instr];
    Glib::ustring gigname(gig_to_utf8(instrument->pInfo->Name));
    if (gigname != name) {
        row[m_Columns.m_col_name] = gigname;
    }
}

void MainWindow::show_midi_rules()
{
    if (gig::Instrument* instrument = get_instrument())
    {
        midiRules.set_instrument(instrument);
        midiRules.show();
        midiRules.deiconify();
    }
}

void MainWindow::show_script_slots() {
    if (!file) return;
    // get selected instrument
    Glib::RefPtr<Gtk::TreeSelection> sel = m_TreeView.get_selection();
    Gtk::TreeModel::iterator it = sel->get_selected();
    if (!it) return;
    Gtk::TreeModel::Row row = *it;
    gig::Instrument* instrument = row[m_Columns.m_col_instr];
    if (!instrument) return;

    ScriptSlots* window = new ScriptSlots;
    window->setInstrument(instrument);
    //window->reparent(*this);
    window->show();
}

void MainWindow::on_action_view_status_bar() {
    Gtk::CheckMenuItem* item =
        dynamic_cast<Gtk::CheckMenuItem*>(uiManager->get_widget("/MenuBar/MenuView/Statusbar"));
    if (!item) {
        std::cerr << "/MenuBar/MenuView/Statusbar == NULL\n";
        return;
    }
    if (item->get_active()) m_StatusBar.show();
    else                    m_StatusBar.hide();
}

bool MainWindow::is_copy_samples_unity_note_enabled() const {
    Gtk::CheckMenuItem* item =
        dynamic_cast<Gtk::CheckMenuItem*>(uiManager->get_widget("/MenuBar/MenuEdit/CopySampleUnity"));
    if (!item) {
        std::cerr << "/MenuBar/MenuEdit/CopySampleUnity == NULL\n";
        return true;
    }
    return item->get_active();
}

bool MainWindow::is_copy_samples_fine_tune_enabled() const {
    Gtk::CheckMenuItem* item =
        dynamic_cast<Gtk::CheckMenuItem*>(uiManager->get_widget("/MenuBar/MenuEdit/CopySampleTune"));
    if (!item) {
        std::cerr << "/MenuBar/MenuEdit/CopySampleTune == NULL\n";
        return true;
    }
    return item->get_active();
}

bool MainWindow::is_copy_samples_loop_enabled() const {
    Gtk::CheckMenuItem* item =
        dynamic_cast<Gtk::CheckMenuItem*>(uiManager->get_widget("/MenuBar/MenuEdit/CopySampleLoop"));
    if (!item) {
        std::cerr << "/MenuBar/MenuEdit/CopySampleLoop == NULL\n";
        return true;
    }
    return item->get_active();
}

void MainWindow::on_button_release(GdkEventButton* button)
{
    if (button->type == GDK_2BUTTON_PRESS) {
        show_instr_props();
    } else if (button->type == GDK_BUTTON_PRESS && button->button == 3) {
        // gig v2 files have no midi rules
        const bool bEnabled = !(file->pVersion && file->pVersion->major == 2);
        static_cast<Gtk::MenuItem*>(
            uiManager->get_widget("/MenuBar/MenuInstrument/MidiRules"))->set_sensitive(
                bEnabled
            );
        static_cast<Gtk::MenuItem*>(
            uiManager->get_widget("/PopupMenu/MidiRules"))->set_sensitive(
                bEnabled
            );
        popup_menu->popup(button->button, button->time);
    }
}

void MainWindow::on_instrument_selection_change(Gtk::RadioMenuItem* item) {
    if (item->get_active()) {
        const std::vector<Gtk::Widget*> children =
            instrument_menu->get_children();
        std::vector<Gtk::Widget*>::const_iterator it =
            find(children.begin(), children.end(), item);
        if (it != children.end()) {
            int index = it - children.begin();
            m_TreeView.get_selection()->select(Gtk::TreePath(ToString(index)));

            m_RegionChooser.set_instrument(file->GetInstrument(index));
        }
    }
}

void MainWindow::select_sample(gig::Sample* sample) {
    Glib::RefPtr<Gtk::TreeModel> model = m_TreeViewSamples.get_model();
    for (int g = 0; g < model->children().size(); ++g) {
        Gtk::TreeModel::Row rowGroup = model->children()[g];
        for (int s = 0; s < rowGroup.children().size(); ++s) {
            Gtk::TreeModel::Row rowSample = rowGroup.children()[s];
            if (rowSample[m_SamplesModel.m_col_sample] == sample) {
                show_samples_tab();
                m_TreeViewSamples.get_selection()->select(rowGroup.children()[s]);
                Gtk::TreePath path(
                    m_TreeViewSamples.get_selection()->get_selected()
                );
                m_TreeViewSamples.scroll_to_row(path);
                return;
            }
        }
    }
}

void MainWindow::on_sample_treeview_button_release(GdkEventButton* button) {
    if (button->type == GDK_BUTTON_PRESS && button->button == 3) {
        Gtk::Menu* sample_popup =
            dynamic_cast<Gtk::Menu*>(uiManager->get_widget("/SamplePopupMenu"));
        // update enabled/disabled state of sample popup items
        Glib::RefPtr<Gtk::TreeSelection> sel = m_TreeViewSamples.get_selection();
        Gtk::TreeModel::iterator it = sel->get_selected();
        bool group_selected  = false;
        bool sample_selected = false;
        if (it) {
            Gtk::TreeModel::Row row = *it;
            group_selected  = row[m_SamplesModel.m_col_group];
            sample_selected = row[m_SamplesModel.m_col_sample];
        }
        
            
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/SamplePopupMenu/SampleProperties"))->
            set_sensitive(group_selected || sample_selected);
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/SamplePopupMenu/AddSample"))->
            set_sensitive(group_selected || sample_selected);
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/SamplePopupMenu/AddGroup"))->
            set_sensitive(file);
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/SamplePopupMenu/ShowSampleRefs"))->
            set_sensitive(sample_selected);
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/SamplePopupMenu/RemoveSample"))->
            set_sensitive(group_selected || sample_selected);
        // show sample popup
        sample_popup->popup(button->button, button->time);

        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/MenuBar/MenuSample/SampleProperties"))->
            set_sensitive(group_selected || sample_selected);
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/MenuBar/MenuSample/AddSample"))->
            set_sensitive(group_selected || sample_selected);
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/MenuBar/MenuSample/AddGroup"))->
            set_sensitive(file);
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/MenuBar/MenuSample/ShowSampleRefs"))->
            set_sensitive(sample_selected);
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/MenuBar/MenuSample/RemoveSample"))->
            set_sensitive(group_selected || sample_selected);
    }
}

void MainWindow::on_script_treeview_button_release(GdkEventButton* button) {
    if (button->type == GDK_BUTTON_PRESS && button->button == 3) {
        Gtk::Menu* script_popup =
            dynamic_cast<Gtk::Menu*>(uiManager->get_widget("/ScriptPopupMenu"));
        // update enabled/disabled state of sample popup items
        Glib::RefPtr<Gtk::TreeSelection> sel = m_TreeViewScripts.get_selection();
        Gtk::TreeModel::iterator it = sel->get_selected();
        bool group_selected  = false;
        bool script_selected = false;
        if (it) {
            Gtk::TreeModel::Row row = *it;
            group_selected  = row[m_ScriptsModel.m_col_group];
            script_selected = row[m_ScriptsModel.m_col_script];
        }
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/ScriptPopupMenu/AddScript"))->
            set_sensitive(group_selected || script_selected);
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/ScriptPopupMenu/AddScriptGroup"))->
            set_sensitive(file);
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/ScriptPopupMenu/EditScript"))->
            set_sensitive(script_selected);    
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/ScriptPopupMenu/RemoveScript"))->
            set_sensitive(group_selected || script_selected);
        // show sample popup
        script_popup->popup(button->button, button->time);

        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/MenuBar/MenuScript/AddScript"))->
            set_sensitive(group_selected || script_selected);
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/MenuBar/MenuScript/AddScriptGroup"))->
            set_sensitive(file);
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/MenuBar/MenuScript/EditScript"))->
            set_sensitive(script_selected);    
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/MenuBar/MenuScript/RemoveScript"))->
            set_sensitive(group_selected || script_selected);
    }
}

Gtk::RadioMenuItem* MainWindow::add_instrument_to_menu(
    const Glib::ustring& name, int position) {

    Gtk::RadioMenuItem::Group instrument_group;
    const std::vector<Gtk::Widget*> children = instrument_menu->get_children();
    if (!children.empty()) {
        instrument_group =
            static_cast<Gtk::RadioMenuItem*>(children[0])->get_group();
    }
    Gtk::RadioMenuItem* item =
        new Gtk::RadioMenuItem(instrument_group, name);
    if (position < 0) {
        instrument_menu->append(*item);
    } else {
        instrument_menu->insert(*item, position);
    }
    item->show();
    item->signal_activate().connect(
        sigc::bind(
            sigc::mem_fun(*this, &MainWindow::on_instrument_selection_change),
            item));
    return item;
}

void MainWindow::remove_instrument_from_menu(int index) {
    const std::vector<Gtk::Widget*> children =
        instrument_menu->get_children();
    Gtk::Widget* child = children[index];
    instrument_menu->remove(*child);
    delete child;
}

void MainWindow::add_instrument(gig::Instrument* instrument) {
    const Glib::ustring name(gig_to_utf8(instrument->pInfo->Name));

    // update instrument tree view
    instrument_name_connection.block();
    Gtk::TreeModel::iterator iterInstr = m_refTreeModel->append();
    Gtk::TreeModel::Row rowInstr = *iterInstr;
    rowInstr[m_Columns.m_col_name] = name;
    rowInstr[m_Columns.m_col_instr] = instrument;
    instrument_name_connection.unblock();

    add_instrument_to_menu(name);

    m_TreeView.get_selection()->select(iterInstr);

    file_changed();
}

void MainWindow::on_action_add_instrument() {
    static int __instrument_indexer = 0;
    if (!file) return;
    gig::Instrument* instrument = file->AddInstrument();
    __instrument_indexer++;
    instrument->pInfo->Name = gig_from_utf8(_("Unnamed Instrument ") +
                                            ToString(__instrument_indexer));

    add_instrument(instrument);
}

void MainWindow::on_action_duplicate_instrument() {
    if (!file) return;

    // retrieve the currently selected instrument
    // (being the original instrument to be duplicated)
    Glib::RefPtr<Gtk::TreeSelection> sel = m_TreeView.get_selection();
    Gtk::TreeModel::iterator itSelection = sel->get_selected();
    if (!itSelection) return;
    Gtk::TreeModel::Row row = *itSelection;
    gig::Instrument* instrOrig = row[m_Columns.m_col_instr];
    if (!instrOrig) return;

    // duplicate the orginal instrument
    gig::Instrument* instrNew = file->AddDuplicateInstrument(instrOrig);
    instrNew->pInfo->Name =
        instrOrig->pInfo->Name + 
        gig_from_utf8(Glib::ustring(" (") + _("Copy") + ")");

    add_instrument(instrNew);
}

void MainWindow::on_action_remove_instrument() {
    if (!file) return;
    if (file_is_shared) {
        Gtk::MessageDialog msg(
            *this,
             _("You cannot delete an instrument from this file, since it's "
               "currently used by the sampler."),
             false, Gtk::MESSAGE_INFO
        );
        msg.run();
        return;
    }

    Glib::RefPtr<Gtk::TreeSelection> sel = m_TreeView.get_selection();
    Gtk::TreeModel::iterator it = sel->get_selected();
    if (it) {
        Gtk::TreeModel::Row row = *it;
        gig::Instrument* instr = row[m_Columns.m_col_instr];
        try {
            Gtk::TreePath path(it);
            int index = path[0];

            // remove instrument from the gig file
            if (instr) file->DeleteInstrument(instr);
            file_changed();

            remove_instrument_from_menu(index);

            // remove row from instruments tree view
            m_refTreeModel->erase(it);

#if GTKMM_MAJOR_VERSION < 3
            // select another instrument (in gtk3 this is done
            // automatically)
            if (!m_refTreeModel->children().empty()) {
                if (index == m_refTreeModel->children().size()) {
                    index--;
                }
                m_TreeView.get_selection()->select(
                    Gtk::TreePath(ToString(index)));
            }
#endif
            instr_props_set_instrument();
            instr = get_instrument();
            if (instr) {
                midiRules.set_instrument(instr);
            } else {
                midiRules.hide();
            }
        } catch (RIFF::Exception e) {
            Gtk::MessageDialog msg(*this, e.Message.c_str(), false, Gtk::MESSAGE_ERROR);
            msg.run();
        }
    }
}

void MainWindow::on_action_sample_properties() {
    //TODO: show a dialog where the selected sample's properties can be edited
    Gtk::MessageDialog msg(
        *this, _("Sorry, yet to be implemented!"), false, Gtk::MESSAGE_INFO
    );
    msg.run();
}

void MainWindow::on_action_add_script_group() {
    static int __script_indexer = 0;
    if (!file) return;
    gig::ScriptGroup* group = file->AddScriptGroup();
    group->Name = gig_from_utf8(_("Unnamed Group"));
    if (__script_indexer) group->Name += " " + ToString(__script_indexer);
    __script_indexer++;
    // update sample tree view
    Gtk::TreeModel::iterator iterGroup = m_refScriptsTreeModel->append();
    Gtk::TreeModel::Row rowGroup = *iterGroup;
    rowGroup[m_ScriptsModel.m_col_name] = gig_to_utf8(group->Name);
    rowGroup[m_ScriptsModel.m_col_script] = NULL;
    rowGroup[m_ScriptsModel.m_col_group] = group;
    file_changed();
}

void MainWindow::on_action_add_script() {
    if (!file) return;
    // get selected group
    Glib::RefPtr<Gtk::TreeSelection> sel = m_TreeViewScripts.get_selection();
    Gtk::TreeModel::iterator it = sel->get_selected();
    if (!it) return;
    Gtk::TreeModel::Row row = *it;
    gig::ScriptGroup* group = row[m_ScriptsModel.m_col_group];
    if (!group) { // not a group, but a script is selected (probably)
        gig::Script* script = row[m_ScriptsModel.m_col_script];
        if (!script) return;
        it = row.parent(); // resolve parent (that is the script's group)
        if (!it) return;
        row = *it;
        group = row[m_ScriptsModel.m_col_group];
        if (!group) return;
    }

    // add a new script to the .gig file
    gig::Script* script = group->AddScript();    
    Glib::ustring name = _("Unnamed Script");
    script->Name = gig_from_utf8(name);

    // add script to the tree view
    Gtk::TreeModel::iterator iterScript =
        m_refScriptsTreeModel->append(row.children());
    Gtk::TreeModel::Row rowScript = *iterScript;
    rowScript[m_ScriptsModel.m_col_name] = name;
    rowScript[m_ScriptsModel.m_col_script] = script;
    rowScript[m_ScriptsModel.m_col_group]  = NULL;

    // unfold group of new script item in treeview
    Gtk::TreeModel::Path path(iterScript);
    m_TreeViewScripts.expand_to_path(path);
}

void MainWindow::on_action_edit_script() {
    if (!file) return;
    // get selected script
    Glib::RefPtr<Gtk::TreeSelection> sel = m_TreeViewScripts.get_selection();
    Gtk::TreeModel::iterator it = sel->get_selected();
    if (!it) return;
    Gtk::TreeModel::Row row = *it;
    gig::Script* script = row[m_ScriptsModel.m_col_script];
    if (!script) return;

    ScriptEditor* editor = new ScriptEditor;
    editor->setScript(script);
    //editor->reparent(*this);
    editor->show();
}

void MainWindow::on_action_remove_script() {
    if (!file) return;
    Glib::RefPtr<Gtk::TreeSelection> sel = m_TreeViewScripts.get_selection();
    Gtk::TreeModel::iterator it = sel->get_selected();
    if (it) {
        Gtk::TreeModel::Row row = *it;
        gig::ScriptGroup* group = row[m_ScriptsModel.m_col_group];
        gig::Script* script     = row[m_ScriptsModel.m_col_script];
        Glib::ustring name      = row[m_ScriptsModel.m_col_name];
        try {
            // remove script group or script from the gig file
            if (group) {
                // notify everybody that we're going to remove these samples
//TODO:         scripts_to_be_removed_signal.emit(members);
                // delete the group in the .gig file including the
                // samples that belong to the group
                file->DeleteScriptGroup(group);
                // notify that we're done with removal
//TODO:         scripts_removed_signal.emit();
                file_changed();
            } else if (script) {
                // notify everybody that we're going to remove this sample
//TODO:         std::list<gig::Script*> lscripts;
//TODO:         lscripts.push_back(script);
//TODO:         scripts_to_be_removed_signal.emit(lscripts);
                // remove sample from the .gig file
                script->GetGroup()->DeleteScript(script);
                // notify that we're done with removal
//TODO:         scripts_removed_signal.emit();
                dimreg_changed();
                file_changed();
            }
            // remove respective row(s) from samples tree view
            m_refScriptsTreeModel->erase(it);
        } catch (RIFF::Exception e) {
            // pretend we're done with removal (i.e. to avoid dead locks)
//TODO:     scripts_removed_signal.emit();
            // show error message
            Gtk::MessageDialog msg(*this, e.Message.c_str(), false, Gtk::MESSAGE_ERROR);
            msg.run();
        }
    }
}

void MainWindow::on_action_add_group() {
    static int __sample_indexer = 0;
    if (!file) return;
    gig::Group* group = file->AddGroup();
    group->Name = gig_from_utf8(_("Unnamed Group"));
    if (__sample_indexer) group->Name += " " + ToString(__sample_indexer);
    __sample_indexer++;
    // update sample tree view
    Gtk::TreeModel::iterator iterGroup = m_refSamplesTreeModel->append();
    Gtk::TreeModel::Row rowGroup = *iterGroup;
    rowGroup[m_SamplesModel.m_col_name] = gig_to_utf8(group->Name);
    rowGroup[m_SamplesModel.m_col_sample] = NULL;
    rowGroup[m_SamplesModel.m_col_group] = group;
    file_changed();
}

void MainWindow::on_action_add_sample() {
    if (!file) return;
    // get selected group
    Glib::RefPtr<Gtk::TreeSelection> sel = m_TreeViewSamples.get_selection();
    Gtk::TreeModel::iterator it = sel->get_selected();
    if (!it) return;
    Gtk::TreeModel::Row row = *it;
    gig::Group* group = row[m_SamplesModel.m_col_group];
    if (!group) { // not a group, but a sample is selected (probably)
        gig::Sample* sample = row[m_SamplesModel.m_col_sample];
        if (!sample) return;
        it = row.parent(); // resolve parent (that is the sample's group)
        if (!it) return;
        row = *it;
        group = row[m_SamplesModel.m_col_group];
        if (!group) return;
    }
    // show 'browse for file' dialog
    Gtk::FileChooserDialog dialog(*this, _("Add Sample(s)"));
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
    dialog.set_select_multiple(true);

    // matches all file types supported by libsndfile
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
    Gtk::FileFilter soundfilter;
#else
    Glib::RefPtr<Gtk::FileFilter> soundfilter = Gtk::FileFilter::create();
#endif
    const char* const supportedFileTypes[] = {
        "*.wav", "*.WAV", "*.aiff", "*.AIFF", "*.aifc", "*.AIFC", "*.snd",
        "*.SND", "*.au", "*.AU", "*.paf", "*.PAF", "*.iff", "*.IFF",
        "*.svx", "*.SVX", "*.sf", "*.SF", "*.voc", "*.VOC", "*.w64",
        "*.W64", "*.pvf", "*.PVF", "*.xi", "*.XI", "*.htk", "*.HTK",
        "*.caf", "*.CAF", NULL
    };
    const char* soundfiles = _("Sound Files");
    const char* allfiles = _("All Files");
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
    for (int i = 0; supportedFileTypes[i]; i++)
        soundfilter.add_pattern(supportedFileTypes[i]);
    soundfilter.set_name(soundfiles);

    // matches every file
    Gtk::FileFilter allpassfilter;
    allpassfilter.add_pattern("*.*");
    allpassfilter.set_name(allfiles);
#else
    for (int i = 0; supportedFileTypes[i]; i++)
        soundfilter->add_pattern(supportedFileTypes[i]);
    soundfilter->set_name(soundfiles);

    // matches every file
    Glib::RefPtr<Gtk::FileFilter> allpassfilter = Gtk::FileFilter::create();
    allpassfilter->add_pattern("*.*");
    allpassfilter->set_name(allfiles);
#endif
    dialog.add_filter(soundfilter);
    dialog.add_filter(allpassfilter);
    if (current_sample_dir != "") {
        dialog.set_current_folder(current_sample_dir);
    }
    if (dialog.run() == Gtk::RESPONSE_OK) {
        current_sample_dir = dialog.get_current_folder();
        Glib::ustring error_files;
        std::vector<std::string> filenames = dialog.get_filenames();
        for (std::vector<std::string>::iterator iter = filenames.begin();
             iter != filenames.end(); ++iter) {
            printf("Adding sample %s\n",(*iter).c_str());
            // use libsndfile to retrieve file informations
            SF_INFO info;
            info.format = 0;
            SNDFILE* hFile = sf_open((*iter).c_str(), SFM_READ, &info);
            try {
                if (!hFile) throw std::string(_("could not open file"));
                int bitdepth;
                switch (info.format & 0xff) {
                    case SF_FORMAT_PCM_S8:
                    case SF_FORMAT_PCM_16:
                    case SF_FORMAT_PCM_U8:
                        bitdepth = 16;
                        break;
                    case SF_FORMAT_PCM_24:
                    case SF_FORMAT_PCM_32:
                    case SF_FORMAT_FLOAT:
                    case SF_FORMAT_DOUBLE:
                        bitdepth = 24;
                        break;
                    default:
                        sf_close(hFile); // close sound file
                        throw std::string(_("format not supported")); // unsupported subformat (yet?)
                }
                // add a new sample to the .gig file
                gig::Sample* sample = file->AddSample();
                // file name without path
                Glib::ustring filename = Glib::filename_display_basename(*iter);
                // remove file extension if there is one
                for (int i = 0; supportedFileTypes[i]; i++) {
                    if (Glib::str_has_suffix(filename, supportedFileTypes[i] + 1)) {
                        filename.erase(filename.length() - strlen(supportedFileTypes[i] + 1));
                        break;
                    }
                }
                sample->pInfo->Name = gig_from_utf8(filename);
                sample->Channels = info.channels;
                sample->BitDepth = bitdepth;
                sample->FrameSize = bitdepth / 8/*1 byte are 8 bits*/ * info.channels;
                sample->SamplesPerSecond = info.samplerate;
                sample->AverageBytesPerSecond = sample->FrameSize * sample->SamplesPerSecond;
                sample->BlockAlign = sample->FrameSize;
                sample->SamplesTotal = info.frames;

                SF_INSTRUMENT instrument;
                if (sf_command(hFile, SFC_GET_INSTRUMENT,
                               &instrument, sizeof(instrument)) != SF_FALSE)
                {
                    sample->MIDIUnityNote = instrument.basenote;
                    sample->FineTune      = instrument.detune;

                    if (instrument.loop_count && instrument.loops[0].mode != SF_LOOP_NONE) {
                        sample->Loops = 1;

                        switch (instrument.loops[0].mode) {
                        case SF_LOOP_FORWARD:
                            sample->LoopType = gig::loop_type_normal;
                            break;
                        case SF_LOOP_BACKWARD:
                            sample->LoopType = gig::loop_type_backward;
                            break;
                        case SF_LOOP_ALTERNATING:
                            sample->LoopType = gig::loop_type_bidirectional;
                            break;
                        }
                        sample->LoopStart = instrument.loops[0].start;
                        sample->LoopEnd = instrument.loops[0].end;
                        sample->LoopPlayCount = instrument.loops[0].count;
                        sample->LoopSize = sample->LoopEnd - sample->LoopStart + 1;
                    }
                }

                // schedule resizing the sample (which will be done
                // physically when File::Save() is called)
                sample->Resize(info.frames);
                // make sure sample is part of the selected group
                group->AddSample(sample);
                // schedule that physical resize and sample import
                // (data copying), performed when "Save" is requested
                SampleImportItem sched_item;
                sched_item.gig_sample  = sample;
                sched_item.sample_path = *iter;
                m_SampleImportQueue.push_back(sched_item);
                // add sample to the tree view
                Gtk::TreeModel::iterator iterSample =
                    m_refSamplesTreeModel->append(row.children());
                Gtk::TreeModel::Row rowSample = *iterSample;
                rowSample[m_SamplesModel.m_col_name] =
                    gig_to_utf8(sample->pInfo->Name);
                rowSample[m_SamplesModel.m_col_sample] = sample;
                rowSample[m_SamplesModel.m_col_group]  = NULL;
                // close sound file
                sf_close(hFile);
                file_changed();
            } catch (std::string what) { // remember the files that made trouble (and their cause)
                if (!error_files.empty()) error_files += "\n";
                error_files += *iter += " (" + what + ")";
            }
        }
        // show error message box when some file(s) could not be opened / added
        if (!error_files.empty()) {
            Glib::ustring txt = _("Could not add the following sample(s):\n") + error_files;
            Gtk::MessageDialog msg(*this, txt, false, Gtk::MESSAGE_ERROR);
            msg.run();
        }
    }
}

void MainWindow::on_action_replace_all_samples_in_all_groups()
{
    if (!file) return;
    Gtk::FileChooserDialog dialog(*this, _("Select Folder"),
                                  Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    const char* str =
        _("This is a very specific function. It tries to replace all samples "
          "in the current gig file by samples located in the chosen "
          "directory.\n\n"
          "It works like this: For each sample in the gig file, it tries to "
          "find a sample file in the selected directory with the same name as "
          "the sample in the gig file. Optionally, you can add a filename "
          "extension below, which will be added to the filename expected to be "
          "found. That is, assume you have a gig file with a sample called "
          "'Snare', if you enter '.wav' below (like it's done by default), it "
          "expects to find a sample file called 'Snare.wav' and will replace "
          "the sample in the gig file accordingly. If you don't need an "
          "extension, blank the field below. Any gig sample where no "
          "appropriate sample file could be found will be reported and left "
          "untouched.\n");
#if GTKMM_MAJOR_VERSION < 3
    view::WrapLabel description(str);
#else
    Gtk::Label description(str);
    description.set_line_wrap();
#endif
    Gtk::HBox entryArea;
    Gtk::Label entryLabel( _("Add filename extension: "), Gtk::ALIGN_START);
    Gtk::Entry postfixEntryBox;
    postfixEntryBox.set_text(".wav");
    entryArea.pack_start(entryLabel);
    entryArea.pack_start(postfixEntryBox);
    dialog.get_vbox()->pack_start(description, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(entryArea, Gtk::PACK_SHRINK);
    description.show();
    entryArea.show_all();
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button(_("Select"), Gtk::RESPONSE_OK);
    dialog.set_select_multiple(false);
    if (current_sample_dir != "") {
        dialog.set_current_folder(current_sample_dir);
    }
    if (dialog.run() == Gtk::RESPONSE_OK)
    {
        current_sample_dir = dialog.get_current_folder();
        Glib::ustring error_files;
        std::string folder = dialog.get_filename();
        for (gig::Sample* sample = file->GetFirstSample();
             sample; sample = file->GetNextSample())
        {
            std::string filename =
                folder + G_DIR_SEPARATOR_S +
                Glib::filename_from_utf8(gig_to_utf8(sample->pInfo->Name) +
                                         postfixEntryBox.get_text());
            SF_INFO info;
            info.format = 0;
            SNDFILE* hFile = sf_open(filename.c_str(), SFM_READ, &info);
            try
            {
                if (!hFile) throw std::string(_("could not open file"));
                int bitdepth;
                switch (info.format & 0xff) {
                    case SF_FORMAT_PCM_S8:
                    case SF_FORMAT_PCM_16:
                    case SF_FORMAT_PCM_U8:
                        bitdepth = 16;
                        break;
                    case SF_FORMAT_PCM_24:
                    case SF_FORMAT_PCM_32:
                    case SF_FORMAT_FLOAT:
                    case SF_FORMAT_DOUBLE:
                        bitdepth = 24;
                        break;
                    default:
                        sf_close(hFile);
                        throw std::string(_("format not supported"));
                }
                SampleImportItem sched_item;
                sched_item.gig_sample  = sample;
                sched_item.sample_path = filename;
                m_SampleImportQueue.push_back(sched_item);
                sf_close(hFile);
                file_changed();
            }
            catch (std::string what)
            {
                if (!error_files.empty()) error_files += "\n";
                error_files += Glib::filename_to_utf8(filename) + 
                    " (" + what + ")";
            }
        }
        // show error message box when some file(s) could not be opened / added
        if (!error_files.empty()) {
            Glib::ustring txt =
                _("Could not replace the following sample(s):\n") + error_files;
            Gtk::MessageDialog msg(*this, txt, false, Gtk::MESSAGE_ERROR);
            msg.run();
        }
    }
}

void MainWindow::on_action_remove_sample() {
    if (!file) return;
    Glib::RefPtr<Gtk::TreeSelection> sel = m_TreeViewSamples.get_selection();
    Gtk::TreeModel::iterator it = sel->get_selected();
    if (it) {
        Gtk::TreeModel::Row row = *it;
        gig::Group* group   = row[m_SamplesModel.m_col_group];
        gig::Sample* sample = row[m_SamplesModel.m_col_sample];
        Glib::ustring name  = row[m_SamplesModel.m_col_name];
        try {
            // remove group or sample from the gig file
            if (group) {
                // temporarily remember the samples that belong to
                // that group (we need that to clean the queue)
                std::list<gig::Sample*> members;
                for (gig::Sample* pSample = group->GetFirstSample();
                     pSample; pSample = group->GetNextSample()) {
                    members.push_back(pSample);
                }
                // notify everybody that we're going to remove these samples
                samples_to_be_removed_signal.emit(members);
                // delete the group in the .gig file including the
                // samples that belong to the group
                file->DeleteGroup(group);
                // notify that we're done with removal
                samples_removed_signal.emit();
                // if sample(s) were just previously added, remove
                // them from the import queue
                for (std::list<gig::Sample*>::iterator member = members.begin();
                     member != members.end(); ++member) {
                    for (std::list<SampleImportItem>::iterator iter = m_SampleImportQueue.begin();
                         iter != m_SampleImportQueue.end(); ++iter) {
                        if ((*iter).gig_sample == *member) {
                            printf("Removing previously added sample '%s' from group '%s'\n",
                                   (*iter).sample_path.c_str(), name.c_str());
                            m_SampleImportQueue.erase(iter);
                            break;
                        }
                    }
                }
                file_changed();
            } else if (sample) {
                // notify everybody that we're going to remove this sample
                std::list<gig::Sample*> lsamples;
                lsamples.push_back(sample);
                samples_to_be_removed_signal.emit(lsamples);
                // remove sample from the .gig file
                file->DeleteSample(sample);
                // notify that we're done with removal
                samples_removed_signal.emit();
                // if sample was just previously added, remove it from
                // the import queue
                for (std::list<SampleImportItem>::iterator iter = m_SampleImportQueue.begin();
                     iter != m_SampleImportQueue.end(); ++iter) {
                    if ((*iter).gig_sample == sample) {
                        printf("Removing previously added sample '%s'\n",
                               (*iter).sample_path.c_str());
                        m_SampleImportQueue.erase(iter);
                        break;
                    }
                }
                dimreg_changed();
                file_changed();
            }
            // remove respective row(s) from samples tree view
            m_refSamplesTreeModel->erase(it);
        } catch (RIFF::Exception e) {
            // pretend we're done with removal (i.e. to avoid dead locks)
            samples_removed_signal.emit();
            // show error message
            Gtk::MessageDialog msg(*this, e.Message.c_str(), false, Gtk::MESSAGE_ERROR);
            msg.run();
        }
    }
}

// see comment on on_sample_treeview_drag_begin()
void MainWindow::on_scripts_treeview_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context)
{
    first_call_to_drag_data_get = true;
}

void MainWindow::on_scripts_treeview_drag_data_get(const Glib::RefPtr<Gdk::DragContext>&,
                                                   Gtk::SelectionData& selection_data, guint, guint)
{
    if (!first_call_to_drag_data_get) return;
    first_call_to_drag_data_get = false;

    // get selected script
    gig::Script* script = NULL;
    Glib::RefPtr<Gtk::TreeSelection> sel = m_TreeViewScripts.get_selection();
    Gtk::TreeModel::iterator it = sel->get_selected();
    if (it) {
        Gtk::TreeModel::Row row = *it;
        script = row[m_ScriptsModel.m_col_script];
    }
    // pass the gig::Script as pointer
    selection_data.set(selection_data.get_target(), 0/*unused*/,
                       (const guchar*)&script,
                       sizeof(script)/*length of data in bytes*/);
}

// For some reason drag_data_get gets called two times for each
// drag'n'drop (at least when target is an Entry). This work-around
// makes sure the code in drag_data_get and drop_drag_data_received is
// only executed once, as drag_begin only gets called once.
void MainWindow::on_sample_treeview_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context)
{
    first_call_to_drag_data_get = true;
}

void MainWindow::on_sample_treeview_drag_data_get(const Glib::RefPtr<Gdk::DragContext>&,
                                                  Gtk::SelectionData& selection_data, guint, guint)
{
    if (!first_call_to_drag_data_get) return;
    first_call_to_drag_data_get = false;

    // get selected sample
    gig::Sample* sample = NULL;
    Glib::RefPtr<Gtk::TreeSelection> sel = m_TreeViewSamples.get_selection();
    Gtk::TreeModel::iterator it = sel->get_selected();
    if (it) {
        Gtk::TreeModel::Row row = *it;
        sample = row[m_SamplesModel.m_col_sample];
    }
    // pass the gig::Sample as pointer
    selection_data.set(selection_data.get_target(), 0/*unused*/, (const guchar*)&sample,
                       sizeof(sample)/*length of data in bytes*/);
}

void MainWindow::on_sample_label_drop_drag_data_received(
    const Glib::RefPtr<Gdk::DragContext>& context, int, int,
    const Gtk::SelectionData& selection_data, guint, guint time)
{
    gig::Sample* sample = *((gig::Sample**) selection_data.get_data());

    if (sample && selection_data.get_length() == sizeof(gig::Sample*)) {
        std::cout << "Drop received sample \"" <<
            sample->pInfo->Name << "\"" << std::endl;
        // drop success
        context->drop_reply(true, time);

        //TODO: we should better move most of the following code to DimRegionEdit::set_sample()

        // notify everybody that we're going to alter the region
        gig::Region* region = m_RegionChooser.get_region();
        region_to_be_changed_signal.emit(region);

        // find the samplechannel dimension
        gig::dimension_def_t* stereo_dimension = 0;
        for (int i = 0 ; i < region->Dimensions ; i++) {
            if (region->pDimensionDefinitions[i].dimension ==
                gig::dimension_samplechannel) {
                stereo_dimension = &region->pDimensionDefinitions[i];
                break;
            }
        }
        bool channels_changed = false;
        if (sample->Channels == 1 && stereo_dimension) {
            // remove the samplechannel dimension
/* commented out, because it makes it impossible building up an instrument from scratch using two separate L/R samples
            region->DeleteDimension(stereo_dimension);
            channels_changed = true;
            region_changed();
*/
        }
        dimreg_edit.set_sample(
            sample,
            is_copy_samples_unity_note_enabled(),
            is_copy_samples_fine_tune_enabled(),
            is_copy_samples_loop_enabled()
        );

        if (sample->Channels == 2 && !stereo_dimension) {
            // add samplechannel dimension
            gig::dimension_def_t dim;
            dim.dimension = gig::dimension_samplechannel;
            dim.bits = 1;
            dim.zones = 2;
            region->AddDimension(&dim);
            channels_changed = true;
            region_changed();
        }
        if (channels_changed) {
            // unmap all samples with wrong number of channels
            // TODO: maybe there should be a warning dialog for this
            for (int i = 0 ; i < region->DimensionRegions ; i++) {
                gig::DimensionRegion* d = region->pDimensionRegions[i];
                if (d->pSample && d->pSample->Channels != sample->Channels) {
                    gig::Sample* oldref = d->pSample;
                    d->pSample = NULL;
                    sample_ref_changed_signal.emit(oldref, NULL);
                }
            }
        }

        // notify we're done with altering
        region_changed_signal.emit(region);

        file_changed();

        return;
    }
    // drop failed
    context->drop_reply(false, time);
}

void MainWindow::sample_name_changed(const Gtk::TreeModel::Path& path,
                                     const Gtk::TreeModel::iterator& iter) {
    if (!iter) return;
    Gtk::TreeModel::Row row = *iter;
    Glib::ustring name  = row[m_SamplesModel.m_col_name];
    gig::Group* group   = row[m_SamplesModel.m_col_group];
    gig::Sample* sample = row[m_SamplesModel.m_col_sample];
    gig::String gigname(gig_from_utf8(name));
    if (group) {
        if (group->Name != gigname) {
            group->Name = gigname;
            printf("group name changed\n");
            file_changed();
        }
    } else if (sample) {
        if (sample->pInfo->Name != gigname) {
            sample->pInfo->Name = gigname;
            printf("sample name changed\n");
            file_changed();
        }
    }
}

void MainWindow::script_name_changed(const Gtk::TreeModel::Path& path,
                                     const Gtk::TreeModel::iterator& iter) {
    if (!iter) return;
    Gtk::TreeModel::Row row = *iter;
    Glib::ustring name      = row[m_ScriptsModel.m_col_name];
    gig::ScriptGroup* group = row[m_ScriptsModel.m_col_group];
    gig::Script* script     = row[m_ScriptsModel.m_col_script];
    gig::String gigname(gig_from_utf8(name));
    if (group) {
        if (group->Name != gigname) {
            group->Name = gigname;
            printf("script group name changed\n");
            file_changed();
        }
    } else if (script) {
        if (script->Name != gigname) {
            script->Name = gigname;
            printf("script name changed\n");
            file_changed();
        }
    }
}

void MainWindow::script_double_clicked(const Gtk::TreeModel::Path& path,
                                       Gtk::TreeViewColumn* column)
{
    Gtk::TreeModel::iterator iter = m_refScriptsTreeModel->get_iter(path);
    if (!iter) return;
    Gtk::TreeModel::Row row = *iter;
    gig::Script* script = row[m_ScriptsModel.m_col_script];
    if (!script) return;

    ScriptEditor* editor = new ScriptEditor;
    editor->setScript(script);
    //editor->reparent(*this);
    editor->show();
}

void MainWindow::instrument_name_changed(const Gtk::TreeModel::Path& path,
                                         const Gtk::TreeModel::iterator& iter) {
    if (!iter) return;
    Gtk::TreeModel::Row row = *iter;
    Glib::ustring name = row[m_Columns.m_col_name];

    // change name in instrument menu
    int index = path[0];
    const std::vector<Gtk::Widget*> children = instrument_menu->get_children();
    if (index < children.size()) {
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION >= 16) || GTKMM_MAJOR_VERSION > 2
        static_cast<Gtk::RadioMenuItem*>(children[index])->set_label(name);
#else
        remove_instrument_from_menu(index);
        Gtk::RadioMenuItem* item = add_instrument_to_menu(name, index);
        item->set_active();
#endif
    }

    // change name in gig
    gig::Instrument* instrument = row[m_Columns.m_col_instr];
    gig::String gigname(gig_from_utf8(name));
    if (instrument && instrument->pInfo->Name != gigname) {
        instrument->pInfo->Name = gigname;

        // change name in the instrument properties window
        if (instrumentProps.get_instrument() == instrument) {
            instrumentProps.update_name();
        }

        file_changed();
    }
}

void MainWindow::on_action_combine_instruments() {
    CombineInstrumentsDialog* d = new CombineInstrumentsDialog(*this, file);
    d->show_all();
    d->resize(500, 400);
    d->run();
    if (d->fileWasChanged()) {
        // update GUI with new instrument just created
        add_instrument(d->newCombinedInstrument());
    }
    delete d;
}

void MainWindow::on_action_view_references() {
    Glib::RefPtr<Gtk::TreeSelection> sel = m_TreeViewSamples.get_selection();
    Gtk::TreeModel::iterator it = sel->get_selected();
    if (!it) return;
    Gtk::TreeModel::Row row = *it;
    gig::Sample* sample = row[m_SamplesModel.m_col_sample];
    if (!sample) return;

    ReferencesView* d = new ReferencesView(*this);
    d->setSample(sample);
    d->show_all();
    d->resize(500, 400);
    d->run();
    delete d;
}

void MainWindow::mergeFiles(const std::vector<std::string>& filenames) {
    struct _Source {
        std::vector<RIFF::File*> riffs;
        std::vector<gig::File*> gigs;
        
        ~_Source() {
            for (int k = 0; k < gigs.size(); ++k) delete gigs[k];
            for (int k = 0; k < riffs.size(); ++k) delete riffs[k];
            riffs.clear();
            gigs.clear();
        }
    } sources;

    if (filenames.empty())
        throw RIFF::Exception(_("No files selected, so nothing done."));

    // first open all input files (to avoid output file corruption)
    int i;
    try {
        for (i = 0; i < filenames.size(); ++i) {
            const std::string& filename = filenames[i];
            printf("opening file=%s\n", filename.c_str());

            RIFF::File* riff = new RIFF::File(filename);
            sources.riffs.push_back(riff);

            gig::File* gig = new gig::File(riff);
            sources.gigs.push_back(gig);
        }
    } catch (RIFF::Exception e) {
        throw RIFF::Exception(
            _("Error occurred while opening '") +
            filenames[i] +
            "': " +
            e.Message
        );
    } catch (...) {
        throw RIFF::Exception(
            _("Unknown exception occurred while opening '") + 
            filenames[i] + "'"
        );
    }

    // now merge the opened .gig files to the main .gig file currently being
    // open in gigedit
    try {
        for (i = 0; i < filenames.size(); ++i) {
            const std::string& filename = filenames[i];
            printf("merging file=%s\n", filename.c_str());
            assert(i < sources.gigs.size());

            this->file->AddContentOf(sources.gigs[i]);
        }
    } catch (RIFF::Exception e) {
        throw RIFF::Exception(
            _("Error occurred while merging '") +
            filenames[i] +
            "': " +
            e.Message
        );
    } catch (...) {
        throw RIFF::Exception(
            _("Unknown exception occurred while merging '") + 
            filenames[i] + "'"
        );
    }

    // Finally save gig file persistently to disk ...
    //NOTE: requires that this gig file already has a filename !
    {
        std::cout << "Saving file\n" << std::flush;
        file_structure_to_be_changed_signal.emit(this->file);

        progress_dialog = new ProgressDialog( //FIXME: memory leak!
            _("Saving") +  Glib::ustring(" '") +
            Glib::filename_display_basename(this->filename) + "' ...",
            *this
        );
        progress_dialog->show_all();
        saver = new Saver(this->file); //FIXME: memory leak!
        saver->signal_progress().connect(
            sigc::mem_fun(*this, &MainWindow::on_saver_progress));
        saver->signal_finished().connect(
            sigc::mem_fun(*this, &MainWindow::on_saver_finished));
        saver->signal_error().connect(
            sigc::mem_fun(*this, &MainWindow::on_saver_error));
        saver->launch();
    }
}

void MainWindow::on_action_merge_files() {
    if (this->file->GetFileName().empty()) {
        Glib::ustring txt = _(
            "You seem to have a new .gig file open that has not been saved "
            "yet. You must save it somewhere before starting to merge it with "
            "other .gig files though, because during the merge operation the "
            "other files' sample data must be written on file level to the "
            "target .gig file."
        );
        Gtk::MessageDialog msg(*this, txt, false, Gtk::MESSAGE_ERROR);
        msg.run();
        return;
    }

    Gtk::FileChooserDialog dialog(*this, _("Merge .gig files"));
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button(_("Merge"), Gtk::RESPONSE_OK);
    dialog.set_default_response(Gtk::RESPONSE_CANCEL);
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
    Gtk::FileFilter filter;
    filter.add_pattern("*.gig");
#else
    Glib::RefPtr<Gtk::FileFilter> filter = Gtk::FileFilter::create();
    filter->add_pattern("*.gig");
#endif
    dialog.set_filter(filter);
    if (current_gig_dir != "") {
        dialog.set_current_folder(current_gig_dir);
    }
    dialog.set_select_multiple(true);

    // show warning in the file picker dialog
    Gtk::HBox descriptionArea;
    descriptionArea.set_spacing(15);
    Gtk::Image warningIcon(Gtk::Stock::DIALOG_WARNING, Gtk::IconSize(Gtk::ICON_SIZE_DIALOG));
    descriptionArea.pack_start(warningIcon, Gtk::PACK_SHRINK);
#if GTKMM_MAJOR_VERSION < 3
    view::WrapLabel description;
#else
    Gtk::Label description;
    description.set_line_wrap();
#endif
    description.set_markup(_(
        "\nSelect at least one .gig file that shall be merged to the .gig file "
        "currently being open in gigedit.\n\n"
        "<b>Please Note:</b> Merging with other files will modify your "
        "currently open .gig file on file level! And be aware that the current "
        "merge algorithm does not detect duplicate samples yet. So if you are "
        "merging files which are using equivalent sample data, those "
        "equivalent samples will currently be treated as separate samples and "
        "will accordingly be stored separately in the target .gig file!"
    ));
    descriptionArea.pack_start(description);
    dialog.get_vbox()->pack_start(descriptionArea, Gtk::PACK_SHRINK);
    descriptionArea.show_all();

    if (dialog.run() == Gtk::RESPONSE_OK) {
        printf("on_action_merge_files self=%x\n", Glib::Threads::Thread::self());
        std::vector<std::string> filenames = dialog.get_filenames();

        // merge the selected files to the currently open .gig file
        try {
            mergeFiles(filenames);
        } catch (RIFF::Exception e) {
            Gtk::MessageDialog msg(*this, e.Message, false, Gtk::MESSAGE_ERROR);
            msg.run();
        }

        // update GUI
        __refreshEntireGUI();        
    }
}

void MainWindow::set_file_is_shared(bool b) {
    this->file_is_shared = b;

    if (file_is_shared) {
        m_AttachedStateLabel.set_label(_("live-mode"));
        m_AttachedStateImage.set(
            Gdk::Pixbuf::create_from_xpm_data(status_attached_xpm)
        );
    } else {
        m_AttachedStateLabel.set_label(_("stand-alone"));
        m_AttachedStateImage.set(
            Gdk::Pixbuf::create_from_xpm_data(status_detached_xpm)
        );
    }

    {
        Gtk::MenuItem* item = dynamic_cast<Gtk::MenuItem*>(
            uiManager->get_widget("/MenuBar/MenuSettings/SyncSamplerInstrumentSelection"));
        if (item) item->set_sensitive(b);
    }
}

void MainWindow::on_sample_ref_count_incremented(gig::Sample* sample, int offset) {
    if (!sample) return;
    sample_ref_count[sample] += offset;
    const int refcount = sample_ref_count[sample];

    Glib::RefPtr<Gtk::TreeModel> model = m_TreeViewSamples.get_model();
    for (int g = 0; g < model->children().size(); ++g) {
        Gtk::TreeModel::Row rowGroup = model->children()[g];
        for (int s = 0; s < rowGroup.children().size(); ++s) {
            Gtk::TreeModel::Row rowSample = rowGroup.children()[s];
            if (rowSample[m_SamplesModel.m_col_sample] != sample) continue;
            rowSample[m_SamplesModel.m_col_refcount] = ToString(refcount) + " " + _("Refs.");
            rowSample[m_SamplesModel.m_color] = refcount ? "black" : "red";
        }
    }
}

void MainWindow::on_sample_ref_changed(gig::Sample* oldSample, gig::Sample* newSample) {
    on_sample_ref_count_incremented(oldSample, -1);
    on_sample_ref_count_incremented(newSample, +1);
}

void MainWindow::on_samples_to_be_removed(std::list<gig::Sample*> samples) {
    // just in case a new sample is added later with exactly the same memory
    // address, which would lead to incorrect refcount if not deleted here
    for (std::list<gig::Sample*>::const_iterator it = samples.begin();
         it != samples.end(); ++it)
    {
        sample_ref_count.erase(*it);
    }
}

void MainWindow::show_samples_tab() {
    m_TreeViewNotebook.set_current_page(0);
}

void MainWindow::show_intruments_tab() {
    m_TreeViewNotebook.set_current_page(1);
}

void MainWindow::show_scripts_tab() {
    m_TreeViewNotebook.set_current_page(2);
}

sigc::signal<void, gig::File*>& MainWindow::signal_file_structure_to_be_changed() {
    return file_structure_to_be_changed_signal;
}

sigc::signal<void, gig::File*>& MainWindow::signal_file_structure_changed() {
    return file_structure_changed_signal;
}

sigc::signal<void, std::list<gig::Sample*> >& MainWindow::signal_samples_to_be_removed() {
    return samples_to_be_removed_signal;
}

sigc::signal<void>& MainWindow::signal_samples_removed() {
    return samples_removed_signal;
}

sigc::signal<void, gig::Region*>& MainWindow::signal_region_to_be_changed() {
    return region_to_be_changed_signal;
}

sigc::signal<void, gig::Region*>& MainWindow::signal_region_changed() {
    return region_changed_signal;
}

sigc::signal<void, gig::Sample*>& MainWindow::signal_sample_changed() {
    return sample_changed_signal;
}

sigc::signal<void, gig::Sample*/*old*/, gig::Sample*/*new*/>& MainWindow::signal_sample_ref_changed() {
    return sample_ref_changed_signal;
}

sigc::signal<void, gig::DimensionRegion*>& MainWindow::signal_dimreg_to_be_changed() {
    return dimreg_to_be_changed_signal;
}

sigc::signal<void, gig::DimensionRegion*>& MainWindow::signal_dimreg_changed() {
    return dimreg_changed_signal;
}

sigc::signal<void, int/*key*/, int/*velocity*/>& MainWindow::signal_note_on() {
    return note_on_signal;
}

sigc::signal<void, int/*key*/, int/*velocity*/>& MainWindow::signal_note_off() {
    return note_off_signal;
}

sigc::signal<void, int/*key*/, int/*velocity*/>& MainWindow::signal_keyboard_key_hit() {
    return m_RegionChooser.signal_keyboard_key_hit();
}

sigc::signal<void, int/*key*/, int/*velocity*/>& MainWindow::signal_keyboard_key_released() {
    return m_RegionChooser.signal_keyboard_key_released();
}

sigc::signal<void, gig::Instrument*>& MainWindow::signal_switch_sampler_instrument() {
    return switch_sampler_instrument_signal;
}
