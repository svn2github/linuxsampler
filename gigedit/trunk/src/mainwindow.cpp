/*
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

#include <libintl.h>
#include <iostream>

#include <gtkmm/filechooserdialog.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/stock.h>
#include <gtkmm/targetentry.h>
#include <gtkmm/main.h>

#if GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION >= 6
#define ABOUT_DIALOG
#include <gtkmm/aboutdialog.h>
#endif

#include <stdio.h>
#include <sndfile.h>

#include "mainwindow.h"

#define _(String) gettext(String)

template<class T> inline std::string ToString(T o) {
    std::stringstream ss;
    ss << o;
    return ss.str();
}

MainWindow::MainWindow()
{
//    set_border_width(5);
//    set_default_size(400, 200);


    add(m_VBox);

    // Handle selection
    Glib::RefPtr<Gtk::TreeSelection> tree_sel_ref = m_TreeView.get_selection();
    tree_sel_ref->signal_changed().connect(
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


    m_TreeViewNotebook.set_size_request(300);

    m_HPaned.add1(m_TreeViewNotebook);
    m_HPaned.add2(dimreg_edit);


    m_TreeViewNotebook.append_page(m_ScrolledWindowSamples, "Samples");
    m_TreeViewNotebook.append_page(m_ScrolledWindow, "Instruments");


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
                     *(new Gtk::AccelKey("<shift><control>s")),
                     sigc::mem_fun(
                         *this, &MainWindow::on_action_file_save_as)
        );
    actionGroup->add(Gtk::Action::create("Properties",
                                         Gtk::Stock::PROPERTIES),
                     sigc::mem_fun(
                         *this, &MainWindow::on_action_file_properties));
    actionGroup->add(Gtk::Action::create("InstrProperties",
                                         Gtk::Stock::PROPERTIES),
                     sigc::mem_fun(
                         *this, &MainWindow::show_instr_props));
    actionGroup->add(Gtk::Action::create("Quit", Gtk::Stock::QUIT),
                     sigc::mem_fun(
                         *this, &MainWindow::hide));
    actionGroup->add(Gtk::Action::create("MenuInstrument", _("_Instrument")));

    action = Gtk::Action::create("MenuHelp", Gtk::Stock::HELP);
    actionGroup->add(Gtk::Action::create("MenuHelp",
                                         action->property_label()));
#ifdef ABOUT_DIALOG
    actionGroup->add(Gtk::Action::create("About", Gtk::Stock::ABOUT),
                     sigc::mem_fun(
                         *this, &MainWindow::on_action_help_about));
#endif
    actionGroup->add(
        Gtk::Action::create("AddInstrument", _("Add _Instrument")),
        sigc::mem_fun(*this, &MainWindow::on_action_add_instrument)
    );
    actionGroup->add(
        Gtk::Action::create("RemoveInstrument", Gtk::Stock::REMOVE),
        sigc::mem_fun(*this, &MainWindow::on_action_remove_instrument)
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
        Gtk::Action::create("AddSample", _("Add _Sample(s)")),
        sigc::mem_fun(*this, &MainWindow::on_action_add_sample)
    );
    actionGroup->add(
        Gtk::Action::create("RemoveSample", Gtk::Stock::REMOVE),
        sigc::mem_fun(*this, &MainWindow::on_action_remove_sample)
    );

    uiManager = Gtk::UIManager::create();
    uiManager->insert_action_group(actionGroup);
    // add_accel_group(uiManager->get_accel_group());

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
        "    <menu action='MenuInstrument'>"
        "    </menu>"
#ifdef ABOUT_DIALOG
        "    <menu action='MenuHelp'>"
        "      <menuitem action='About'/>"
        "    </menu>"
#endif
        "  </menubar>"
        "  <popup name='PopupMenu'>"
        "    <menuitem action='InstrProperties'/>"
        "    <menuitem action='AddInstrument'/>"
        "    <separator/>"
        "    <menuitem action='RemoveInstrument'/>"
        "  </popup>"
        "  <popup name='SamplePopupMenu'>"
        "    <menuitem action='SampleProperties'/>"
        "    <menuitem action='AddGroup'/>"
        "    <menuitem action='AddSample'/>"
        "    <separator/>"
        "    <menuitem action='RemoveSample'/>"
        "  </popup>"
        "</ui>";
    uiManager->add_ui_from_string(ui_info);

    popup_menu = dynamic_cast<Gtk::Menu*>(uiManager->get_widget("/PopupMenu"));

    Gtk::Widget* menuBar = uiManager->get_widget("/MenuBar");
    m_VBox.pack_start(*menuBar, Gtk::PACK_SHRINK);
    m_VBox.pack_start(m_HPaned);
    m_VBox.pack_start(m_RegionChooser, Gtk::PACK_SHRINK);
    m_VBox.pack_start(m_DimRegionChooser, Gtk::PACK_SHRINK);

    m_RegionChooser.signal_sel_changed().connect(
        sigc::mem_fun(*this, &MainWindow::region_changed) );
    m_DimRegionChooser.signal_sel_changed().connect(
        sigc::mem_fun(*this, &MainWindow::dimreg_changed) );


    // Create the Tree model:
    m_refTreeModel = Gtk::ListStore::create(m_Columns);
    m_TreeView.set_model(m_refTreeModel);
    m_refTreeModel->signal_row_changed().connect(
        sigc::mem_fun(*this, &MainWindow::instrument_name_changed)
    );

    // Add the TreeView's view columns:
    m_TreeView.append_column_editable("Instrument", m_Columns.m_col_name);
    m_TreeView.set_headers_visible(false);

    // create samples treeview (including its data model)
    m_refSamplesTreeModel = SamplesTreeStore::create(m_SamplesModel);
    m_TreeViewSamples.set_model(m_refSamplesTreeModel);
    // m_TreeViewSamples.set_reorderable();
    m_TreeViewSamples.append_column_editable("Samples", m_SamplesModel.m_col_name);
    m_TreeViewSamples.set_headers_visible(false);
    m_TreeViewSamples.signal_button_press_event().connect_notify(
        sigc::mem_fun(*this, &MainWindow::on_sample_treeview_button_release)
    );
    m_refSamplesTreeModel->signal_row_changed().connect(
        sigc::mem_fun(*this, &MainWindow::sample_name_changed)
    );

    // establish drag&drop between samples tree view and dimension region 'Sample' text entry
    std::list<Gtk::TargetEntry> drag_target_gig_sample;
    drag_target_gig_sample.push_back( Gtk::TargetEntry("gig::Sample") );
    m_TreeViewSamples.drag_source_set(drag_target_gig_sample);
    m_TreeViewSamples.signal_drag_data_get().connect(
        sigc::mem_fun(*this, &MainWindow::on_sample_treeview_drag_data_get)
    );
    dimreg_edit.wSample->drag_dest_set(drag_target_gig_sample);
    dimreg_edit.wSample->signal_drag_data_received().connect(
        sigc::mem_fun(*this, &MainWindow::on_sample_label_drop_drag_data_received)
    );

    file = 0;

    show_all_children();
}

MainWindow::~MainWindow()
{
}

void MainWindow::region_changed()
{
    m_DimRegionChooser.set_region(m_RegionChooser.get_region());
}

void MainWindow::dimreg_changed()
{
    dimreg_edit.set_dim_region(m_DimRegionChooser.get_dimregion());
}

void MainWindow::on_sel_change()
{
    Glib::RefPtr<Gtk::TreeSelection> tree_sel_ref = m_TreeView.get_selection();

    Gtk::TreeModel::iterator it = tree_sel_ref->get_selected();
    if (it) {
        Gtk::TreeModel::Row row = *it;
        std::cout << row[m_Columns.m_col_name] << std::endl;

        m_RegionChooser.set_instrument(row[m_Columns.m_col_instr]);
    } else {
        m_RegionChooser.set_instrument(0);
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
        Glib::Mutex::Lock lock(progressMutex);
        progress = fraction;
    }
    progress_dispatcher();
}

void Loader::thread_function()
{
    printf("thread_function self=%x\n", Glib::Thread::self());
    printf("Start %s\n", filename);
    RIFF::File* riff = new RIFF::File(filename);
    gig = new gig::File(riff);
    gig::progress_t progress;
    progress.callback = loader_progress_callback;
    progress.custom = this;

    gig->GetInstrument(0, &progress);
    printf("End\n");
    finished_dispatcher();
}

Loader::Loader(const char* filename)
    : thread(0), filename(filename)
{
}

void Loader::launch()
{
    thread = Glib::Thread::create(sigc::mem_fun(*this, &Loader::thread_function), true);
    printf("launch thread=%x\n", thread);
}

float Loader::get_progress()
{
    float res;
    {
        Glib::Mutex::Lock lock(progressMutex);
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

LoadDialog::LoadDialog(const Glib::ustring& title, Gtk::Window& parent)
    : Gtk::Dialog(title, parent, true)
{
    get_vbox()->pack_start(progressBar);
    show_all_children();
}

// Clear all GUI elements / controls. This method is typically called
// before a new .gig file is to be created or to be loaded.
void MainWindow::__clear() {
    // remove all entries from "Instrument" menu
    Gtk::MenuItem* instrument_menu =
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/MenuBar/MenuInstrument"));
    instrument_menu->hide();
    for (int i = 0; i < instrument_menu->get_submenu()->items().size(); i++) {
        delete &instrument_menu->get_submenu()->items()[i];
    }
    instrument_menu->get_submenu()->items().clear();
    // forget all samples that ought to be imported
    m_SampleImportQueue.clear();
    // clear the samples and instruments tree views
    m_refTreeModel->clear();
    m_refSamplesTreeModel->clear();
    // free libgig's gig::File instance
    if (file) {
        delete file;
        file = NULL;
    }
}

void MainWindow::on_action_file_new()
{
    // clear all GUI elements
    __clear();
    // create a new .gig file (virtually yet)
    gig::File* pFile = new gig::File;
    // already add one new instrument by default
    gig::Instrument* pInstrument = pFile->AddInstrument();
    pInstrument->pInfo->Name = "Unnamed Instrument";
    // update GUI with that new gig::File
    load_gig(pFile, NULL /*no file name yet*/);
}

void MainWindow::on_action_file_open()
{
    Gtk::FileChooserDialog dialog(*this, _("Open file"));
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
    Gtk::FileFilter filter;
    filter.add_pattern("*.gig");
    dialog.set_filter(filter);
    if (dialog.run() == Gtk::RESPONSE_OK) {
        printf("filename=%s\n", dialog.get_filename().c_str());
        __clear();
        printf("on_action_file_open self=%x\n", Glib::Thread::self());
        load_file(dialog.get_filename().c_str());
    }
}

void MainWindow::load_file(const char* name)
{
    load_dialog = new LoadDialog("Loading...", *this);
    load_dialog->show_all();
    loader = new Loader(strdup(name));
    loader->signal_progress().connect(
        sigc::mem_fun(*this, &MainWindow::on_loader_progress));
    loader->signal_finished().connect(
        sigc::mem_fun(*this, &MainWindow::on_loader_finished));
    loader->launch();
}

void MainWindow::load_instrument(gig::Instrument* instr) {
    if (!instr) {
        Glib::ustring txt = "Provided instrument is NULL!\n";
        Gtk::MessageDialog msg(*this, txt, false, Gtk::MESSAGE_ERROR);
        msg.run();
        Gtk::Main::quit();
    }
    gig::File* pFile = (gig::File*) instr->GetParent();
    load_gig(pFile, NULL /*file name*/);
    //TODO: automatically select the given instrument
}

void MainWindow::on_loader_progress()
{
    load_dialog->set_fraction(loader->get_progress());
}

void MainWindow::on_loader_finished()
{
    printf("Loader finished!\n");
    printf("on_loader_finished self=%x\n", Glib::Thread::self());
    load_gig(loader->gig, loader->filename);
    load_dialog->hide();
}

void MainWindow::on_action_file_save()
{
    if (!file) return;
    std::cout << "Saving file\n" << std::flush;
    try {
        file->Save();
    } catch (RIFF::Exception e) {
        Glib::ustring txt = "Could not save file: " + e.Message;
        Gtk::MessageDialog msg(*this, txt, false, Gtk::MESSAGE_ERROR);
        msg.run();
        return;
    }
    std::cout << "Saving file done\n" << std::flush;
    __import_queued_samples();
}

void MainWindow::on_action_file_save_as()
{
    if (!file) return;
    Gtk::FileChooserDialog dialog(*this, "Open", Gtk::FILE_CHOOSER_ACTION_SAVE);
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);
    Gtk::FileFilter filter;
    filter.add_pattern("*.gig");
    dialog.set_filter(filter);
    if (dialog.run() == Gtk::RESPONSE_OK) {
        printf("filename=%s\n", dialog.get_filename().c_str());
        try {
            file->Save(dialog.get_filename());
        } catch (RIFF::Exception e) {
            Glib::ustring txt = "Could not save file: " + e.Message;
            Gtk::MessageDialog msg(*this, txt, false, Gtk::MESSAGE_ERROR);
            msg.run();
            return;
        }
        __import_queued_samples();
    }
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
        try {
            if (!hFile) throw std::string("could not open file");
            // determine sample's bit depth
            int bitdepth;
            switch (info.format & 0xff) {
                case SF_FORMAT_PCM_S8:
                    bitdepth = 16; // we simply convert to 16 bit for now
                    break;
                case SF_FORMAT_PCM_16:
                    bitdepth = 16;
                    break;
                case SF_FORMAT_PCM_24:
                    bitdepth = 32; // we simply convert to 32 bit for now
                    break;
                case SF_FORMAT_PCM_32:
                    bitdepth = 32;
                    break;
                case SF_FORMAT_PCM_U8:
                    bitdepth = 16; // we simply convert to 16 bit for now
                    break;
                case SF_FORMAT_FLOAT:
                    bitdepth = 32;
                    break;
                case SF_FORMAT_DOUBLE:
                    bitdepth = 32; // I guess we will always truncate this to 32 bit
                    break;
                default:
                    sf_close(hFile); // close sound file
                    throw std::string("format not supported"); // unsupported subformat (yet?)
            }
            // allocate appropriate copy buffer (TODO: for now we copy
            // it in one piece, might be tough for very long samples)
            // and copy sample data into buffer
            int8_t* buffer = NULL;
            switch (bitdepth) {
                case 16:
                    buffer = new int8_t[2 * info.channels * info.frames];
                    // libsndfile does the conversion for us (if needed)
                    sf_readf_short(hFile, (short*) buffer, info.frames);
                    break;
                case 32:
                    buffer = new int8_t[4 * info.channels * info.frames];
                    // libsndfile does the conversion for us (if needed)
                    sf_readf_int(hFile, (int*) buffer, info.frames);
                    break;
            }
            // write from buffer directly (physically) into .gig file
            (*iter).gig_sample->Write(buffer, info.frames);
            // cleanup
            sf_close(hFile);
            delete[] buffer;
            // on success we remove the sample from the import queue,
            // otherwise keep it, maybe it works the next time ?
            std::list<SampleImportItem>::iterator cur = iter;
            ++iter;
            m_SampleImportQueue.erase(cur);
        } catch (std::string what) {
            // remember the files that made trouble (and their cause)
            if (error_files.size()) error_files += "\n";
            error_files += (*iter).sample_path += " (" + what + ")";
            ++iter;
        }
    }
    // show error message box when some sample(s) could not be imported
    if (error_files.size()) {
        Glib::ustring txt = "Could not import the following sample(s):\n" + error_files;
        Gtk::MessageDialog msg(*this, txt, false, Gtk::MESSAGE_ERROR);
        msg.run();
    }
}

void MainWindow::on_action_file_properties()
{
    propDialog.show();
    propDialog.deiconify();
}

void MainWindow::on_action_help_about()
{
#ifdef ABOUT_DIALOG
    Gtk::AboutDialog dialog;
    dialog.set_version(VERSION);
    dialog.run();
#endif
}

PropDialog::PropDialog()
    : table(2,1)
{
    table.set_col_spacings(5);
    const char* propLabels[] = {
        "Name:",
        "CreationDate:",
        "Comments:", // TODO: multiline
        "Product:",
        "Copyright:",
        "Artists:",
        "Genre:",
        "Keywords:",
        "Engineer:",
        "Technician:",
        "Software:", // TODO: readonly
        "Medium:",
        "Source:",
        "SourceForm:",
        "Commissioned:",
        "Subject:"
    };
    for (int i = 0 ; i < sizeof(propLabels) / sizeof(char*) ; i++) {
        label[i].set_text(propLabels[i]);
        label[i].set_alignment(Gtk::ALIGN_LEFT);
        table.attach(label[i], 0, 1, i, i + 1, Gtk::FILL, Gtk::SHRINK);
        table.attach(entry[i], 1, 2, i, i + 1, Gtk::FILL | Gtk::EXPAND,
                     Gtk::SHRINK);
    }

    add(table);
    // add_button(Gtk::Stock::CANCEL, 0);
    // add_button(Gtk::Stock::OK, 1);
    show_all_children();
}

void PropDialog::set_info(DLS::Info* info)
{
    entry[0].set_text(info->Name);
    entry[1].set_text(info->CreationDate);
    entry[2].set_text(Glib::convert(info->Comments, "UTF-8", "ISO-8859-1"));
    entry[3].set_text(info->Product);
    entry[4].set_text(info->Copyright);
    entry[5].set_text(info->Artists);
    entry[6].set_text(info->Genre);
    entry[7].set_text(info->Keywords);
    entry[8].set_text(info->Engineer);
    entry[9].set_text(info->Technician);
    entry[10].set_text(info->Software);
    entry[11].set_text(info->Medium);
    entry[12].set_text(info->Source);
    entry[13].set_text(info->SourceForm);
    entry[14].set_text(info->Commissioned);
    entry[15].set_text(info->Subject);
}

void InstrumentProps::add_prop(LabelWidget& prop)
{
    table.attach(prop.label, 0, 1, rowno, rowno + 1,
                 Gtk::FILL, Gtk::SHRINK);
    table.attach(prop.widget, 1, 2, rowno, rowno + 1,
                 Gtk::FILL | Gtk::EXPAND, Gtk::SHRINK);
    rowno++;
}

InstrumentProps::InstrumentProps()
    : table(2,1),
      quitButton(Gtk::Stock::CLOSE),
      eName("Name"),
      eIsDrum("IsDrum"),
      eMIDIBank("MIDIBank", 0, 16383),
      eMIDIProgram("MIDIProgram"),
      eAttenuation("Attenuation", 0, 96, 0, 1),
      eGainPlus6("Gain +6dB", eAttenuation, -6),
      eEffectSend("EffectSend", 0, 65535),
      eFineTune("FineTune", -8400, 8400),
      ePitchbendRange("PitchbendRange", 0, 12),
      ePianoReleaseMode("PianoReleaseMode"),
      eDimensionKeyRangeLow("DimensionKeyRangeLow"),
      eDimensionKeyRangeHigh("DimensionKeyRangeHigh")
{
    set_title("Instrument properties");

    rowno = 0;
    table.set_col_spacings(5);

    add_prop(eName);
    add_prop(eIsDrum);
    add_prop(eMIDIBank);
    add_prop(eMIDIProgram);
    add_prop(eAttenuation);
    add_prop(eGainPlus6);
    add_prop(eEffectSend);
    add_prop(eFineTune);
    add_prop(ePitchbendRange);
    add_prop(ePianoReleaseMode);
    add_prop(eDimensionKeyRangeLow);
    add_prop(eDimensionKeyRangeHigh);

    eDimensionKeyRangeLow.signal_value_changed().connect(
        sigc::mem_fun(*this, &InstrumentProps::key_range_low_changed));
    eDimensionKeyRangeHigh.signal_value_changed().connect(
        sigc::mem_fun(*this, &InstrumentProps::key_range_high_changed));

    add(vbox);
    table.set_border_width(5);
    vbox.pack_start(table);
    table.show();
    vbox.pack_start(buttonBox, Gtk::PACK_SHRINK);
    buttonBox.set_layout(Gtk::BUTTONBOX_END);
    buttonBox.set_border_width(5);
    buttonBox.show();
    buttonBox.pack_start(quitButton);
    quitButton.set_flags(Gtk::CAN_DEFAULT);
    quitButton.grab_focus();

    quitButton.signal_clicked().connect(
        sigc::mem_fun(*this, &InstrumentProps::hide));

    quitButton.show();
    vbox.show();
    show_all_children();
}

void InstrumentProps::set_instrument(gig::Instrument* instrument)
{
    update_gui = false;
    eName.set_ptr(&instrument->pInfo->Name);
    eIsDrum.set_ptr(&instrument->IsDrum);
    eMIDIBank.set_ptr(&instrument->MIDIBank);
    eMIDIProgram.set_ptr(&instrument->MIDIProgram);
    eAttenuation.set_ptr(&instrument->Attenuation);
    eGainPlus6.set_ptr(&instrument->Attenuation);
    eEffectSend.set_ptr(&instrument->EffectSend);
    eFineTune.set_ptr(&instrument->FineTune);
    ePitchbendRange.set_ptr(&instrument->PitchbendRange);
    ePianoReleaseMode.set_ptr(&instrument->PianoReleaseMode);
    eDimensionKeyRangeLow.set_ptr(&instrument->DimensionKeyRange.low);
    eDimensionKeyRangeHigh.set_ptr(&instrument->DimensionKeyRange.high);
    update_gui = true;
}

void InstrumentProps::key_range_low_changed()
{
    double l = eDimensionKeyRangeLow.get_value();
    double h = eDimensionKeyRangeHigh.get_value();
    if (h < l) eDimensionKeyRangeHigh.set_value(l);
}

void InstrumentProps::key_range_high_changed()
{
    double l = eDimensionKeyRangeLow.get_value();
    double h = eDimensionKeyRangeHigh.get_value();
    if (h < l) eDimensionKeyRangeLow.set_value(h);
}

void MainWindow::load_gig(gig::File* gig, const char* filename)
{
    file = gig;

    if (filename) {
        const char *basename = strrchr(filename, '/');
        basename = basename ? basename + 1 : filename;
        set_title(basename);
    } else {
        set_title("unnamed");
    }

    propDialog.set_info(gig->pInfo);

    Gtk::MenuItem* instrument_menu =
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/MenuBar/MenuInstrument"));

    int instrument_index = 0;
    Gtk::RadioMenuItem::Group instrument_group;
    for (gig::Instrument* instrument = gig->GetFirstInstrument() ; instrument ;
         instrument = gig->GetNextInstrument()) {
        Gtk::TreeModel::iterator iter = m_refTreeModel->append();
        Gtk::TreeModel::Row row = *iter;
        row[m_Columns.m_col_name] = instrument->pInfo->Name.c_str();
        row[m_Columns.m_col_instr] = instrument;
        // create a menu item for this instrument
        Gtk::RadioMenuItem* item =
            new Gtk::RadioMenuItem(instrument_group, instrument->pInfo->Name.c_str());
        instrument_menu->get_submenu()->append(*item);
        item->signal_activate().connect(
            sigc::bind(
                sigc::mem_fun(*this, &MainWindow::on_instrument_selection_change),
                instrument_index
            )
        );
        instrument_index++;
    }
    instrument_menu->show();
    instrument_menu->get_submenu()->show_all_children();

    for (gig::Group* group = gig->GetFirstGroup(); group; group = gig->GetNextGroup()) {
        if (group->Name != "") {
            Gtk::TreeModel::iterator iterGroup = m_refSamplesTreeModel->append();
            Gtk::TreeModel::Row rowGroup = *iterGroup;
            rowGroup[m_SamplesModel.m_col_name]   = group->Name.c_str();
            rowGroup[m_SamplesModel.m_col_group]  = group;
            rowGroup[m_SamplesModel.m_col_sample] = NULL;
            for (gig::Sample* sample = group->GetFirstSample();
                 sample; sample = group->GetNextSample()) {
                Gtk::TreeModel::iterator iterSample =
                    m_refSamplesTreeModel->append(rowGroup.children());
                Gtk::TreeModel::Row rowSample = *iterSample;
                rowSample[m_SamplesModel.m_col_name]   = sample->pInfo->Name.c_str();
                rowSample[m_SamplesModel.m_col_sample] = sample;
                rowSample[m_SamplesModel.m_col_group]  = NULL;
            }
        }
    }

    // select the first instrument
    Glib::RefPtr<Gtk::TreeSelection> tree_sel_ref = m_TreeView.get_selection();
    tree_sel_ref->select(Gtk::TreePath("0"));
}

void MainWindow::show_instr_props()
{
    Glib::RefPtr<Gtk::TreeSelection> tree_sel_ref = m_TreeView.get_selection();
    Gtk::TreeModel::iterator it = tree_sel_ref->get_selected();
    if (it)
    {
        Gtk::TreeModel::Row row = *it;
        if (row[m_Columns.m_col_instr])
        {
            instrumentProps.set_instrument(row[m_Columns.m_col_instr]);
            instrumentProps.show();
            instrumentProps.deiconify();
        }
    }
}

void MainWindow::on_button_release(GdkEventButton* button)
{
    if (button->type == GDK_2BUTTON_PRESS) {
        show_instr_props();
    } else if (button->type == GDK_BUTTON_PRESS && button->button == 3) {
        popup_menu->popup(button->button, button->time);
    }
}

void MainWindow::on_instrument_selection_change(int index) {
    m_RegionChooser.set_instrument(file->GetInstrument(index));
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
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/SamplePopupMenu/RemoveSample"))->
            set_sensitive(group_selected || sample_selected);
        // show sample popup
        sample_popup->popup(button->button, button->time);
    }
}

void MainWindow::on_action_add_instrument() {
    static int __instrument_indexer = 0;
    if (!file) return;
    gig::Instrument* instrument = file->AddInstrument();
    __instrument_indexer++;
    instrument->pInfo->Name =
        "Unnamed Instrument " + ToString(__instrument_indexer);
    // update instrument tree view
    Gtk::TreeModel::iterator iterInstr = m_refTreeModel->append();
    Gtk::TreeModel::Row rowInstr = *iterInstr;
    rowInstr[m_Columns.m_col_name] = instrument->pInfo->Name.c_str();
    rowInstr[m_Columns.m_col_instr] = instrument;
}

void MainWindow::on_action_remove_instrument() {
    if (!file) return;
    Glib::RefPtr<Gtk::TreeSelection> sel = m_TreeView.get_selection();
    Gtk::TreeModel::iterator it = sel->get_selected();
    if (it) {
        Gtk::TreeModel::Row row = *it;
        gig::Instrument* instr = row[m_Columns.m_col_instr];
        try {
            // remove instrument from the gig file
            if (instr) file->DeleteInstrument(instr);
            // remove respective row from instruments tree view
            m_refTreeModel->erase(it);
        } catch (RIFF::Exception e) {
            Gtk::MessageDialog msg(*this, e.Message.c_str(), false, Gtk::MESSAGE_ERROR);
            msg.run();
        }
    }
}

void MainWindow::on_action_sample_properties() {
    //TODO: show a dialog where the selected sample's properties can be edited
    Gtk::MessageDialog msg(
        *this, "Sorry, yet to be implemented!", false, Gtk::MESSAGE_INFO
    );
    msg.run();
}

void MainWindow::on_action_add_group() {
    static int __sample_indexer = 0;
    if (!file) return;
    gig::Group* group = file->AddGroup();
    group->Name = "Unnamed Group";
    if (__sample_indexer) group->Name += " " + ToString(__sample_indexer);
    __sample_indexer++;
    // update sample tree view
    Gtk::TreeModel::iterator iterGroup = m_refSamplesTreeModel->append();
    Gtk::TreeModel::Row rowGroup = *iterGroup;
    rowGroup[m_SamplesModel.m_col_name] = group->Name.c_str();
    rowGroup[m_SamplesModel.m_col_sample] = NULL;
    rowGroup[m_SamplesModel.m_col_group] = group;
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
    Gtk::FileFilter soundfilter; // matches all file types supported by libsndfile
    const char* supportedFileTypes[] = {
        "*.wav", "*.WAV", "*.aiff", "*.AIFF", "*.aifc", "*.AIFC", "*.snd",
        "*.SND", "*.au", "*.AU", "*.paf", "*.PAF", "*.iff", "*.IFF",
        "*.svx", "*.SVX", "*.sf", "*.SF", "*.voc", "*.VOC", "*.w64",
        "*.W64", "*.pvf", "*.PVF", "*.xi", "*.XI", "*.htk", "*.HTK",
        "*.caf", "*.CAF", NULL
    };
    for (int i = 0; supportedFileTypes[i]; i++)
        soundfilter.add_pattern(supportedFileTypes[i]);
    soundfilter.set_name("Sound Files");
    Gtk::FileFilter allpassfilter; // matches every file
    allpassfilter.add_pattern("*.*");
    allpassfilter.set_name("All Files");
    dialog.add_filter(soundfilter);
    dialog.add_filter(allpassfilter);
    if (dialog.run() == Gtk::RESPONSE_OK) {
        Glib::ustring error_files;
        Glib::SListHandle<Glib::ustring> filenames = dialog.get_filenames();
        for (Glib::SListHandle<Glib::ustring>::iterator iter = filenames.begin();
             iter != filenames.end(); ++iter) {
            printf("Adding sample %s\n",(*iter).c_str());
            // use libsndfile to retrieve file informations
            SF_INFO info;
            info.format = 0;
            SNDFILE* hFile = sf_open((*iter).c_str(), SFM_READ, &info);
            try {
                if (!hFile) throw std::string("could not open file");
                int bitdepth;
                switch (info.format & 0xff) {
                    case SF_FORMAT_PCM_S8:
                        bitdepth = 16; // we simply convert to 16 bit for now
                        break;
                    case SF_FORMAT_PCM_16:
                        bitdepth = 16;
                        break;
                    case SF_FORMAT_PCM_24:
                        bitdepth = 32; // we simply convert to 32 bit for now
                        break;
                    case SF_FORMAT_PCM_32:
                        bitdepth = 32;
                        break;
                    case SF_FORMAT_PCM_U8:
                        bitdepth = 16; // we simply convert to 16 bit for now
                        break;
                    case SF_FORMAT_FLOAT:
                        bitdepth = 32;
                        break;
                    case SF_FORMAT_DOUBLE:
                        bitdepth = 32; // I guess we will always truncate this to 32 bit
                        break;
                    default:
                        sf_close(hFile); // close sound file
                        throw std::string("format not supported"); // unsupported subformat (yet?)
                }
                // add a new sample to the .gig file
                gig::Sample* sample = file->AddSample();
                // file name without path
                sample->pInfo->Name = (*iter).substr((*iter).rfind('/') + 1).raw();
                sample->Channels = info.channels;
                sample->BitDepth = bitdepth;
                sample->FrameSize = bitdepth / 8/*1 byte are 8 bits*/ * info.channels;
                sample->SamplesPerSecond = info.samplerate;
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
                rowSample[m_SamplesModel.m_col_name]   = sample->pInfo->Name.c_str();
                rowSample[m_SamplesModel.m_col_sample] = sample;
                rowSample[m_SamplesModel.m_col_group]  = NULL;
                // close sound file
                sf_close(hFile);
            } catch (std::string what) { // remember the files that made trouble (and their cause)
                if (error_files.size()) error_files += "\n";
                error_files += *iter += " (" + what + ")";
            }
        }
        // show error message box when some file(s) could not be opened / added
        if (error_files.size()) {
            Glib::ustring txt = "Could not add the following sample(s):\n" + error_files;
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
                // temporarily remember the samples that bolong to
                // that group (we need that to clean the queue)
                std::list<gig::Sample*> members;
                for (gig::Sample* pSample = group->GetFirstSample();
                     pSample; pSample = group->GetNextSample()) {
                    members.push_back(pSample);
                }
                // delete the group in the .gig file including the
                // samples that belong to the group
                file->DeleteGroup(group);
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
            } else if (sample) {
                // remove sample from the .gig file
                file->DeleteSample(sample);
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
            }
            // remove respective row(s) from samples tree view
            m_refSamplesTreeModel->erase(it);
        } catch (RIFF::Exception e) {
            Gtk::MessageDialog msg(*this, e.Message.c_str(), false, Gtk::MESSAGE_ERROR);
            msg.run();
        }
    }
}

void MainWindow::on_sample_treeview_drag_data_get(const Glib::RefPtr<Gdk::DragContext>&,
                                                  Gtk::SelectionData& selection_data, guint, guint)
{
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
    gig::DimensionRegion* dimregion = m_DimRegionChooser.get_dimregion();
    gig::Sample* sample = *((gig::Sample**) selection_data.get_data());

    if (sample && dimregion && selection_data.get_length() == sizeof(gig::Sample*)) {
        if (sample != dimregion->pSample) {
            dimregion->pSample = sample;
            dimreg_edit.wSample->set_text(dimregion->pSample->pInfo->Name.c_str());
            std::cout << "Drop received sample \"" <<
                dimregion->pSample->pInfo->Name.c_str() << "\"" << std::endl;
            // drop success
            context->drop_reply(true, time);
            return;
        }
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
    if (group) {
        group->Name = name;
    } else if (sample) {
        sample->pInfo->Name = name.raw();
    }
}

void MainWindow::instrument_name_changed(const Gtk::TreeModel::Path& path,
                                         const Gtk::TreeModel::iterator& iter) {
    if (!iter) return;
    Gtk::TreeModel::Row row = *iter;
    Glib::ustring name = row[m_Columns.m_col_name];
    gig::Instrument* instrument = row[m_Columns.m_col_instr];
    if (instrument) instrument->pInfo->Name = name.raw();
}
