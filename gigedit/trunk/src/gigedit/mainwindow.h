/*                                                         -*- c++ -*-
 * Copyright (C) 2006, 2007 Andreas Persson
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

#ifndef GIGEDIT_MAINWINDOW_H
#define GIGEDIT_MAINWINDOW_H

#include <gig.h>

#include <gtkmm/actiongroup.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/dialog.h>
#include <gtkmm/liststore.h>
#include <gtkmm/paned.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treestore.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/window.h>

#include <sstream>

#include "regionchooser.h"
#include "dimregionchooser.h"
#include "dimregionedit.h"

class MainWindow;

class PropDialog : public Gtk::Window {
public:
    PropDialog();
    void set_info(DLS::Info* info);
protected:
    Gtk::Table table;
    Gtk::Label label[16];
    Gtk::Entry entry[16];
};

class InstrumentProps : public Gtk::Window {
public:
    InstrumentProps();
    void set_instrument(gig::Instrument* instrument);
    sigc::signal<void>& signal_instrument_changed();
protected:
    Gtk::VBox vbox;
    Gtk::HButtonBox buttonBox;
    Gtk::Button quitButton;
    Gtk::Table table;
    StringEntry eName;
    BoolEntry eIsDrum;
    NumEntryTemp<uint16_t> eMIDIBank;
    NumEntryTemp<uint32_t> eMIDIProgram;
    NumEntryGain eAttenuation;
    BoolEntryPlus6 eGainPlus6;
    NumEntryTemp<uint16_t> eEffectSend;
    NumEntryTemp<int16_t> eFineTune;
    NumEntryTemp<uint16_t> ePitchbendRange;
    BoolEntry ePianoReleaseMode;
    NoteEntry eDimensionKeyRangeLow;
    NoteEntry eDimensionKeyRangeHigh;
    int rowno;
    void add_prop(BoolEntry& prop);
    void add_prop(BoolEntryPlus6& prop);
    void add_prop(LabelWidget& prop);
    void key_range_low_changed();
    void key_range_high_changed();
    sigc::signal<void> instrument_changed;
};

class LoadDialog : public Gtk::Dialog {
public:
    LoadDialog(const Glib::ustring& title, Gtk::Window& parent);
    void set_fraction(float fraction) { progressBar.set_fraction(fraction); }
protected:
    Gtk::ProgressBar progressBar;
};

class Loader : public sigc::trackable {
public:
    Loader(const char* filename);
    void launch();
    Glib::Dispatcher& signal_progress();
    Glib::Dispatcher& signal_finished();
    void progress_callback(float fraction);
    float get_progress();
    const char* filename;
    gig::File* gig;

private:
    Glib::Thread* thread;
    void thread_function();
    Glib::Dispatcher finished_dispatcher;
    Glib::Dispatcher progress_dispatcher;
    Glib::Mutex progressMutex;
    float progress;
};

class MainWindow : public Gtk::Window {
public:
    MainWindow();
    virtual ~MainWindow();
    void load_file(const char* name);
    void load_instrument(gig::Instrument* instr);
    void file_changed();
    sigc::signal<void, gig::File*>& signal_file_structure_to_be_changed();
    sigc::signal<void, gig::File*>& signal_file_structure_changed();
    sigc::signal<void, std::list<gig::Sample*> >& signal_samples_to_be_removed();
    sigc::signal<void>& signal_samples_removed();
    sigc::signal<void, gig::Region*>& signal_region_to_be_changed();
    sigc::signal<void, gig::Region*>& signal_region_changed();
    sigc::signal<void, gig::DimensionRegion*>& signal_dimreg_to_be_changed();
    sigc::signal<void, gig::DimensionRegion*>& signal_dimreg_changed();
    sigc::signal<void, gig::Sample*/*old*/, gig::Sample*/*new*/>& signal_sample_ref_changed();

protected:
    Glib::RefPtr<Gtk::ActionGroup> actionGroup;
    Glib::RefPtr<Gtk::UIManager> uiManager;

    RegionChooser m_RegionChooser;
    DimRegionChooser m_DimRegionChooser;

    PropDialog propDialog;
    InstrumentProps instrumentProps;

    sigc::signal<void, gig::File*> file_structure_to_be_changed_signal;
    sigc::signal<void, gig::File*> file_structure_changed_signal;
    sigc::signal<void, std::list<gig::Sample*> > samples_to_be_removed_signal;
    sigc::signal<void> samples_removed_signal;
    sigc::signal<void, gig::Region*> region_to_be_changed_signal;
    sigc::signal<void, gig::Region*> region_changed_signal;
    sigc::signal<void, gig::DimensionRegion*> dimreg_to_be_changed_signal;
    sigc::signal<void, gig::DimensionRegion*> dimreg_changed_signal;
    sigc::signal<void, gig::Sample*/*old*/, gig::Sample*/*new*/> sample_ref_changed_signal;

    void on_instrument_selection_change(int index);
    void on_sel_change();
    void region_changed();
    void dimreg_changed();
    void on_loader_progress();
    void on_loader_finished();

    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        ModelColumns() {
          add(m_col_name);
          add(m_col_instr);
        }

        Gtk::TreeModelColumn<Glib::ustring> m_col_name;
        Gtk::TreeModelColumn<gig::Instrument*> m_col_instr;
    } m_Columns;

    Gtk::VBox m_VBox;
    Gtk::HPaned m_HPaned;

    Gtk::ScrolledWindow m_ScrolledWindow;

    Gtk::TreeView m_TreeView;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

    class SamplesModel : public Gtk::TreeModel::ColumnRecord {
    public:
        SamplesModel() {
            add(m_col_name);
            add(m_col_sample);
            add(m_col_group);
        }

        Gtk::TreeModelColumn<Glib::ustring> m_col_name;
        Gtk::TreeModelColumn<gig::Sample*> m_col_sample;
        Gtk::TreeModelColumn<gig::Group*> m_col_group;
    } m_SamplesModel;

    class SamplesTreeStore : public Gtk::TreeStore {
    public:
        static Glib::RefPtr<SamplesTreeStore> create(const SamplesModel& columns) {
            return Glib::RefPtr<SamplesTreeStore>( new SamplesTreeStore(columns) );
        }
    protected:
        SamplesTreeStore(const SamplesModel& columns) : Gtk::TreeStore(columns) {}
    };

    Gtk::ScrolledWindow m_ScrolledWindowSamples;
    Gtk::TreeView m_TreeViewSamples;
    Glib::RefPtr<SamplesTreeStore> m_refSamplesTreeModel;

    DimRegionEdit dimreg_edit;

    Gtk::Notebook m_Notebook;
    Gtk::Notebook m_TreeViewNotebook;

    struct SampleImportItem {
        gig::Sample*  gig_sample;  // pointer to the gig::Sample to
                                   // which the sample data should be
                                   // imported to
        Glib::ustring sample_path; // file name of the sample to be
                                   // imported
    };
    std::list<SampleImportItem> m_SampleImportQueue;


    void on_action_file_new();
    void on_action_file_open();
    void on_action_file_save();
    void on_action_file_save_as();
    void on_action_file_properties();
    void on_action_quit();
    void show_instr_props();
    void on_action_help_about();

    // sample right-click popup actions
    void on_sample_treeview_button_release(GdkEventButton* button);
    void on_action_sample_properties();
    void on_action_add_group();
    void on_action_add_sample();
    void on_action_remove_sample();

    void on_action_add_instrument();
    void on_action_remove_instrument();

    LoadDialog* load_dialog;
    Loader* loader;
    void load_gig(gig::File* gig, const char* filename, bool isSharedInstrument = false);

    gig::File* file;
    bool file_is_shared;
    bool file_has_name;
    bool file_is_changed;
    std::string filename;
    std::string current_dir;

    bool file_save();
    bool file_save_as();
    bool check_if_savable();

    void on_button_release(GdkEventButton* button);
    void on_sample_treeview_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context);
    void on_sample_treeview_drag_data_get(const Glib::RefPtr<Gdk::DragContext>&,
                                          Gtk::SelectionData& selection_data, guint, guint);
    void on_sample_label_drop_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context,
                                                 int, int,
                                                 const Gtk::SelectionData& selection_data,
                                                 guint, guint time);

    void sample_name_changed(const Gtk::TreeModel::Path& path,
                             const Gtk::TreeModel::iterator& iter);
    void instrument_name_changed(const Gtk::TreeModel::Path& path,
                                 const Gtk::TreeModel::iterator& iter);

    void __import_queued_samples();
    void __clear();

    bool close_confirmation_dialog();
    bool leaving_shared_mode_dialog();

    Gtk::Menu* popup_menu;

    bool on_delete_event(GdkEventAny* event);

    bool first_call_to_drag_data_get;
};

#endif
