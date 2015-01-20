/*                                                         -*- c++ -*-
 * Copyright (C) 2006 - 2015 Andreas Persson
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
#include <gtkmm/menu.h>
#include <gtkmm/paned.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/radiomenuitem.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treestore.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/window.h>
#include <gtkmm/statusbar.h>
#include <gtkmm/image.h>

#include <sstream>

#include "regionchooser.h"
#include "dimregionchooser.h"
#include "dimregionedit.h"
#include "midirules.h"
#ifndef OLD_THREADS
#include <glibmm/threads.h>
#endif

class MainWindow;

class PropDialog : public Gtk::Window,
                   public PropEditor<DLS::Info> {
public:
    PropDialog();
    void set_info(DLS::Info* info);
    void set_file(gig::File* file);
protected:
    ChoiceEntry<int> eFileFormat;
    StringEntry eName;
    StringEntry eCreationDate;
    StringEntryMultiLine eComments;
    StringEntry eProduct;
    StringEntry eCopyright;
    StringEntry eArtists;
    StringEntry eGenre;
    StringEntry eKeywords;
    StringEntry eEngineer;
    StringEntry eTechnician;
    StringEntry eSoftware;
    StringEntry eMedium;
    StringEntry eSource;
    StringEntry eSourceForm;
    StringEntry eCommissioned;
    StringEntry eSubject;
    Gtk::VBox vbox;
    Gtk::HButtonBox buttonBox;
    Gtk::Button quitButton;
    Table table;

    gig::File* m_file;

    void onFileFormatChanged();
};

class InstrumentProps : public Gtk::Window,
                        public PropEditor<gig::Instrument> {
public:
    InstrumentProps();
    void set_instrument(gig::Instrument* instrument);
    gig::Instrument* get_instrument() { return m; }
    void update_name();
    sigc::signal<void>& signal_name_changed() {
        return sig_name_changed;
    }
protected:
    void set_Name(const gig::String& name);
    void set_IsDrum(bool value);
    void set_MIDIBank(uint16_t value);
    void set_MIDIProgram(uint32_t value);

    sigc::signal<void> sig_name_changed;
    Gtk::VBox vbox;
    Gtk::HButtonBox buttonBox;
    Gtk::Button quitButton;
    Table table;
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
};

class ProgressDialog : public Gtk::Dialog {
public:
    ProgressDialog(const Glib::ustring& title, Gtk::Window& parent);
    void set_fraction(float fraction) { progressBar.set_fraction(fraction); }
protected:
    Gtk::ProgressBar progressBar;
};

class Loader : public sigc::trackable {
public:
    Loader(const char* filename);
    void launch();
    Glib::Dispatcher& signal_progress();
    Glib::Dispatcher& signal_finished(); ///< Finished successfully, without error.
    Glib::Dispatcher& signal_error();
    void progress_callback(float fraction);
    float get_progress();
    const Glib::ustring filename;
    Glib::ustring error_message;
    gig::File* gig;

private:
    Glib::Threads::Thread* thread;
    void thread_function();
    Glib::Dispatcher finished_dispatcher;
    Glib::Dispatcher progress_dispatcher;
    Glib::Dispatcher error_dispatcher;
    Glib::Threads::Mutex progressMutex;
    float progress;
};

class Saver : public sigc::trackable {
public:
    Saver(gig::File* file, Glib::ustring filename = ""); ///< one argument means "save", two arguments means "save as"
    void launch();
    Glib::Dispatcher& signal_progress();
    Glib::Dispatcher& signal_finished(); ///< Finished successfully, without error.
    Glib::Dispatcher& signal_error();
    void progress_callback(float fraction);
    float get_progress();
    gig::File* gig;
    const Glib::ustring filename;
    Glib::ustring error_message;

private:
    Glib::Threads::Thread* thread;
    void thread_function();
    Glib::Dispatcher finished_dispatcher;
    Glib::Dispatcher progress_dispatcher;
    Glib::Dispatcher error_dispatcher;
    Glib::Threads::Mutex progressMutex;
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
    sigc::signal<void, gig::Sample*>& signal_sample_changed();
    sigc::signal<void, gig::Sample*/*old*/, gig::Sample*/*new*/>& signal_sample_ref_changed();

    sigc::signal<void, int/*key*/, int/*velocity*/>& signal_note_on();
    sigc::signal<void, int/*key*/, int/*velocity*/>& signal_note_off();

    sigc::signal<void, int/*key*/, int/*velocity*/>& signal_keyboard_key_hit();
    sigc::signal<void, int/*key*/, int/*velocity*/>& signal_keyboard_key_released();

    sigc::signal<void, gig::Instrument*>& signal_switch_sampler_instrument();

protected:
    Glib::RefPtr<Gtk::ActionGroup> actionGroup;
    Glib::RefPtr<Gtk::UIManager> uiManager;

    Gtk::Statusbar m_StatusBar;
    Gtk::Label     m_AttachedStateLabel;
    Gtk::Image     m_AttachedStateImage;

    RegionChooser m_RegionChooser;
    DimRegionChooser m_DimRegionChooser;

    PropDialog propDialog;
    InstrumentProps instrumentProps;
    MidiRules midiRules;

    sigc::signal<void, gig::File*> file_structure_to_be_changed_signal;
    sigc::signal<void, gig::File*> file_structure_changed_signal;
    sigc::signal<void, std::list<gig::Sample*> > samples_to_be_removed_signal;
    sigc::signal<void> samples_removed_signal;
    sigc::signal<void, gig::Region*> region_to_be_changed_signal;
    sigc::signal<void, gig::Region*> region_changed_signal;
    sigc::signal<void, gig::DimensionRegion*> dimreg_to_be_changed_signal;
    sigc::signal<void, gig::DimensionRegion*> dimreg_changed_signal;
    sigc::signal<void, gig::Sample*> sample_changed_signal;
    sigc::signal<void, gig::Sample*/*old*/, gig::Sample*/*new*/> sample_ref_changed_signal;

    sigc::signal<void, int/*key*/, int/*velocity*/> note_on_signal;
    sigc::signal<void, int/*key*/, int/*velocity*/> note_off_signal;

    sigc::signal<void, gig::Instrument*> switch_sampler_instrument_signal;

    void on_instrument_selection_change(Gtk::RadioMenuItem* item);
    void on_sel_change();
    void region_changed();
    void dimreg_changed();
    void select_instrument(gig::Instrument* instrument);
    bool select_dimension_region(gig::DimensionRegion* dimRgn);
    void select_sample(gig::Sample* sample);
    void on_loader_progress();
    void on_loader_finished();
    void on_loader_error();
    void on_saver_progress();
    void on_saver_error();
    void on_saver_finished();

    void dimreg_all_dimregs_toggled();
    gig::Instrument* get_instrument();
    void add_region_to_dimregs(gig::Region* region, bool stereo, bool all_dimregs);
    void update_dimregs();

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

    Gtk::Menu* instrument_menu;

    std::map<gig::Sample*,int> sample_ref_count;

    class SamplesModel : public Gtk::TreeModel::ColumnRecord {
    public:
        SamplesModel() {
            add(m_col_name);
            add(m_col_sample);
            add(m_col_group);
            add(m_col_refcount);
            add(m_color);
        }

        Gtk::TreeModelColumn<Glib::ustring> m_col_name;
        Gtk::TreeModelColumn<gig::Sample*> m_col_sample;
        Gtk::TreeModelColumn<gig::Group*> m_col_group;
        Gtk::TreeModelColumn<Glib::ustring> m_col_refcount;
        Gtk::TreeModelColumn<Glib::ustring> m_color;
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

    class ScriptsModel : public Gtk::TreeModel::ColumnRecord {
    public:
        ScriptsModel() {
            add(m_col_name);
            add(m_col_script);
            add(m_col_group);
        }

        Gtk::TreeModelColumn<Glib::ustring> m_col_name;
        Gtk::TreeModelColumn<gig::Script*> m_col_script;
        Gtk::TreeModelColumn<gig::ScriptGroup*> m_col_group;
    } m_ScriptsModel;

    class ScriptsTreeStore : public Gtk::TreeStore {
    public:
        static Glib::RefPtr<ScriptsTreeStore> create(const ScriptsModel& columns) {
            return Glib::RefPtr<ScriptsTreeStore>( new ScriptsTreeStore(columns) );
        }
    protected:
        ScriptsTreeStore(const ScriptsModel& columns) : Gtk::TreeStore(columns) {}
    };

    Gtk::ScrolledWindow m_ScrolledWindowScripts;
    Gtk::TreeView m_TreeViewScripts;
    Glib::RefPtr<ScriptsTreeStore> m_refScriptsTreeModel;

    Gtk::VBox dimreg_vbox;
    Gtk::HBox dimreg_hbox;
    Gtk::Label dimreg_label;
    Gtk::CheckButton dimreg_all_regions;
    Gtk::CheckButton dimreg_all_dimregs;
    Gtk::CheckButton dimreg_stereo;
    DimRegionEdit dimreg_edit;

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
    bool instr_props_set_instrument();
    void show_midi_rules();
    void show_script_slots();
    void on_action_view_status_bar();
    void on_action_warn_user_on_extensions();
    void on_action_sync_sampler_instrument_selection();
    void on_action_help_about();

    // sample right-click popup actions
    void on_sample_treeview_button_release(GdkEventButton* button);
    void on_action_sample_properties();
    void on_action_add_group();
    void on_action_add_sample();
    void on_action_replace_sample();
    void on_action_replace_all_samples_in_all_groups();
    void on_action_remove_sample();
    
    // script right-click popup actions
    void on_script_treeview_button_release(GdkEventButton* button);
    void on_action_add_script_group();
    void on_action_add_script();
    void on_action_edit_script();
    void on_action_remove_script();

    void on_action_add_instrument();
    void on_action_duplicate_instrument();
    void on_action_remove_instrument();

    void show_samples_tab();
    void show_intruments_tab();
    void show_scripts_tab();

    void add_instrument(gig::Instrument* instrument);
    Gtk::RadioMenuItem* add_instrument_to_menu(const Glib::ustring& name,
                                               int position = -1);
    void remove_instrument_from_menu(int index);

    ProgressDialog* progress_dialog;
    Loader* loader;
    Saver* saver;
    void load_gig(gig::File* gig, const char* filename, bool isSharedInstrument = false);
    void updateSampleRefCountMap(gig::File* gig);

    gig::File* file;
    bool file_is_shared;
    bool file_has_name;
    bool file_is_changed;
    std::string filename;
    std::string current_gig_dir;
    std::string current_sample_dir;

    void set_file_is_shared(bool);

    bool file_save();
    bool file_save_as();
    bool check_if_savable();

    void on_button_release(GdkEventButton* button);
    void on_instruments_treeview_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context);
    void on_instruments_treeview_drag_data_get(const Glib::RefPtr<Gdk::DragContext>&,
                                               Gtk::SelectionData& selection_data, guint, guint);
    void on_instruments_treeview_drop_drag_data_received(
        const Glib::RefPtr<Gdk::DragContext>& context, int, int,
        const Gtk::SelectionData& selection_data, guint, guint time
    );
    void on_scripts_treeview_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context);
    void on_scripts_treeview_drag_data_get(const Glib::RefPtr<Gdk::DragContext>&,
                                           Gtk::SelectionData& selection_data, guint, guint);
    void on_sample_treeview_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context);
    void on_sample_treeview_drag_data_get(const Glib::RefPtr<Gdk::DragContext>&,
                                          Gtk::SelectionData& selection_data, guint, guint);
    void on_sample_label_drop_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context,
                                                 int, int,
                                                 const Gtk::SelectionData& selection_data,
                                                 guint, guint time);

    void script_name_changed(const Gtk::TreeModel::Path& path,
                             const Gtk::TreeModel::iterator& iter);
    void script_double_clicked(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
    void sample_name_changed(const Gtk::TreeModel::Path& path,
                             const Gtk::TreeModel::iterator& iter);
    void instrument_name_changed(const Gtk::TreeModel::Path& path,
                                 const Gtk::TreeModel::iterator& iter);
    void instr_name_changed_by_instr_props(Gtk::TreeModel::iterator& it);
    sigc::connection instrument_name_connection;

    void on_action_combine_instruments();
    void on_action_view_references();
    void on_action_merge_files();
    void mergeFiles(const std::vector<std::string>& filenames);

    void on_sample_ref_changed(gig::Sample* oldSample, gig::Sample* newSample);
    void on_sample_ref_count_incremented(gig::Sample* sample, int offset);
    void on_samples_to_be_removed(std::list<gig::Sample*> samples);

    void add_or_replace_sample(bool replace);

    void __import_queued_samples();
    void __clear();
    void __refreshEntireGUI();

    bool close_confirmation_dialog();
    bool leaving_shared_mode_dialog();

    Gtk::Menu* popup_menu;

    bool on_delete_event(GdkEventAny* event);

    bool first_call_to_drag_data_get;
    
    bool is_copy_samples_unity_note_enabled() const;
    bool is_copy_samples_fine_tune_enabled() const;
    bool is_copy_samples_loop_enabled() const;
};

#endif
