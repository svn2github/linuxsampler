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
#include <gtkmm/alignment.h>
#include <gtkmm/box.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/combobox.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/liststore.h>
#include <gtkmm/notebook.h>
#include <gtkmm/paned.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/scale.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/table.h>
#include <gtkmm/treestore.h>
#include <gtkmm/treeview.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/window.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/treemodel.h>

#include <sstream>

#include "regionchooser.h"
#include "dimregionchooser.h"

extern bool update_gui;

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
protected:
    Gtk::VBox vbox;
    Gtk::HButtonBox buttonBox;
    Gtk::Button quitButton;
    Gtk::Table table;
    Gtk::Label label[10];
    Gtk::Entry entry[8];
    Gtk::CheckButton check[2];
};

class LoadDialog : public Gtk::Dialog {
public:
    LoadDialog();
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

class LabelWidget {
public:
    Gtk::Label label;
    Gtk::Widget& widget;

    LabelWidget(char* labelText, Gtk::Widget& widget);
    void set_sensitive(bool sensitive = true);
};


template<typename T2>
class NumEntry : public LabelWidget {
protected:
    Gtk::Adjustment adjust;
    Gtk::HScale scale;
    Gtk::SpinButton spinbutton;
    Gtk::HBox box;
    T2* dimreg;
public:
    NumEntry(char* labelText, double lower = 0, double upper = 127,
             int decimals = 0);
    void set_value(double value) {
        spinbutton.set_value(value);
    }
    Glib::SignalProxy0<void> signal_value_changed() {
        return spinbutton.signal_value_changed();
    }
    double get_value() const {
        return spinbutton.get_value();
    }
};

template<typename T2>
NumEntry<T2>::NumEntry(char* labelText, double lower, double upper,
                       int decimals) :
    adjust(lower, lower, upper, 1, 10),
    scale(adjust),
    spinbutton(adjust),
    LabelWidget(labelText, box)
{
    spinbutton.set_digits(decimals);
    scale.set_draw_value(false);
    box.pack_start(spinbutton, Gtk::PACK_SHRINK);
    box.add(scale);
}

class NumEntryGain : public NumEntry<gig::DimensionRegion> {
private:
    void value_changed();
public:
    NumEntryGain(char* labelText,
		 double lower, double upper, int decimals);
    void set_dimreg(gig::DimensionRegion* dimreg);
};

template<typename T>
class NumEntryX : public NumEntry<gig::DimensionRegion> {
private:
    T& (*access)(gig::DimensionRegion*);
    void value_changed();
public:
    NumEntryX(char* labelText, T& (*access)(gig::DimensionRegion*),
              double lower = 0, double upper = 127, int decimals = 0);
    void set_dimreg(gig::DimensionRegion* dimreg);
};

template<typename T>
NumEntryX<T>::NumEntryX(char* labelText, T& (*access)(gig::DimensionRegion*),
			double lower, double upper, int decimals) :
    NumEntry<gig::DimensionRegion>(labelText, lower, upper, decimals),
    access(access)
{
    spinbutton.signal_value_changed().connect(
        sigc::mem_fun(*this, &NumEntryX::value_changed));
}

template<typename T>
void NumEntryX<T>::value_changed()
{
    if (dimreg && update_gui) {
        access(dimreg) = T(spinbutton.get_value());
    }
}

template<typename T>
void NumEntryX<T>::set_dimreg(gig::DimensionRegion* dimreg)
{
    this->dimreg = 0;
    set_value(access(dimreg));
    this->dimreg = dimreg;
}


class NoteEntry : public NumEntryX<uint8_t> {
public:
    NoteEntry(char* labelText, uint8_t& (*access)(gig::DimensionRegion*));
private:
    int on_input(double* new_value);
    bool on_output();
};


template<typename T, typename T2 = gig::DimensionRegion>
class NumEntryTemp : public NumEntry<T2> {
    using NumEntry<T2>::spinbutton;
    using NumEntry<T2>::dimreg;
private:
    T T2::* param;
    void value_changed();
public:
    NumEntryTemp(char* labelText, T T2::* param,
                 double lower = 0, double upper = 127, int decimals = 0);
    void set_dimreg(gig::DimensionRegion* dimreg);
};

template<typename T, typename T2>
NumEntryTemp<T, T2>::NumEntryTemp(char* labelText, T T2::* param,
                                  double lower, double upper, int decimals) :
    NumEntry<T2>(labelText, lower, upper, decimals),
    param(param)
{
    spinbutton.signal_value_changed().connect(
        sigc::mem_fun(*this, &NumEntryTemp<T, T2>::value_changed));
}

template<typename T, typename T2>
void NumEntryTemp<T, T2>::value_changed()
{
    if (dimreg && update_gui) {
        dimreg->*param = T(spinbutton.get_value());
    }
}

template<typename T, typename T2>
void NumEntryTemp<T, T2>::set_dimreg(gig::DimensionRegion* dimreg)
{
    this->dimreg = 0;
    set_value(dimreg->*param);
    this->dimreg = dimreg;
}



class NumEntryPermille : public NumEntry<gig::DimensionRegion> {
private:
    uint16_t gig::DimensionRegion::* param;
    void value_changed();
public:
    NumEntryPermille(char* labelText, uint16_t gig::DimensionRegion::* param,
                     double lower = 0, double upper = 127, int decimals = 0);
    void set_dimreg(gig::DimensionRegion* dimreg);
};


template<typename T>
class ChoiceEntry : public LabelWidget {
private:
    Gtk::ComboBoxText combobox;
    Gtk::Alignment align;
    T gig::DimensionRegion::* param;
    gig::DimensionRegion* dimreg;
    void value_changed();
    const T* values;
public:
    ChoiceEntry(char* labelText,
                T gig::DimensionRegion::* param);
    void set_choices(char** texts, const T* values);
    void set_dimreg(gig::DimensionRegion* dimreg);
    int get_active_row_number() { return combobox.get_active_row_number(); }
    Glib::SignalProxy0<void> signal_changed() {
        return combobox.signal_changed();
    }
};

template<typename T>
ChoiceEntry<T>::ChoiceEntry(char* labelText,
                            T gig::DimensionRegion::* param) :
    align(0, 0, 0, 0),
    LabelWidget(labelText, align),
    param(param)
{
    combobox.signal_changed().connect(
        sigc::mem_fun(*this, &ChoiceEntry::value_changed));
    align.add(combobox);
}

template<typename T>
void ChoiceEntry<T>::set_choices(char** texts, const T* values)
{
    for (int i = 0 ; texts[i] ; i++) {
        combobox.append_text(texts[i]);
    }
    this->values = values;
}

template<typename T>
void ChoiceEntry<T>::value_changed()
{
    if (dimreg && update_gui) {
        int rowno = combobox.get_active_row_number();
        if (rowno != -1) dimreg->*param = values[rowno];
    }
}

template<typename T>
void ChoiceEntry<T>::set_dimreg(gig::DimensionRegion* dimreg)
{
    this->dimreg = 0;
    T value = dimreg->*param;
    int row = 0;
    int nb_rows = combobox.get_model()->children().size();
    for (; row < nb_rows ; row++) {
        if (value == values[row]) break;
    }
    combobox.set_active(row == nb_rows ? -1 : row);
    this->dimreg = dimreg;
}


class ChoiceEntryLeverageCtrl : public LabelWidget {
private:
    Gtk::ComboBoxText combobox;
    Gtk::Alignment align;
    gig::leverage_ctrl_t gig::DimensionRegion::* param;
    gig::DimensionRegion* dimreg;
    void value_changed();
public:
    ChoiceEntryLeverageCtrl(char* labelText,
                            gig::leverage_ctrl_t gig::DimensionRegion::* param);
    void set_dimreg(gig::DimensionRegion* dimreg);
    int get_active_row_number() { return combobox.get_active_row_number(); }
    Glib::SignalProxy0<void> signal_changed() {
        return combobox.signal_changed();
    }
};



class BoolEntry : public LabelWidget {
private:
    Gtk::CheckButton checkbutton;
    bool gig::DimensionRegion::* param;
    gig::DimensionRegion* dimreg;
    void value_changed();
public:
    BoolEntry(char* labelText, bool gig::DimensionRegion::* param);
    void set_dimreg(gig::DimensionRegion* dimreg);
    bool get_active() { return checkbutton.get_active(); }
    Glib::SignalProxy0<void> signal_toggled() {
        return checkbutton.signal_toggled();
    }
};

class MainWindow : public Gtk::Window {
public:
    MainWindow();
    virtual ~MainWindow();
    void getInfo(const char* filename);

protected:
    Glib::RefPtr<Gtk::ActionGroup> actionGroup;
    Glib::RefPtr<Gtk::UIManager> uiManager;

    int rowno;
    int pageno;
    int firstRowInBlock;

    NumEntryPermille eEG1PreAttack;
    NumEntryTemp<double> eEG1Attack;
    NumEntryTemp<double> eEG1Decay1;
    NumEntryTemp<double> eEG1Decay2;
    BoolEntry eEG1InfiniteSustain;
    NumEntryPermille eEG1Sustain;
    NumEntryTemp<double> eEG1Release;
    BoolEntry eEG1Hold;
    ChoiceEntryLeverageCtrl eEG1Controller;
    BoolEntry eEG1ControllerInvert;
    NumEntryTemp<uint8_t> eEG1ControllerAttackInfluence;
    NumEntryTemp<uint8_t> eEG1ControllerDecayInfluence;
    NumEntryTemp<uint8_t> eEG1ControllerReleaseInfluence;
    NumEntryTemp<double> eLFO1Frequency;
    NumEntryTemp<uint16_t> eLFO1InternalDepth;
    NumEntryTemp<uint16_t> eLFO1ControlDepth;
    ChoiceEntry<gig::lfo1_ctrl_t> eLFO1Controller;
    BoolEntry eLFO1FlipPhase;
    BoolEntry eLFO1Sync;
    NumEntryPermille eEG2PreAttack;
    NumEntryTemp<double> eEG2Attack;
    NumEntryTemp<double> eEG2Decay1;
    NumEntryTemp<double> eEG2Decay2;
    BoolEntry eEG2InfiniteSustain;
    NumEntryPermille eEG2Sustain;
    NumEntryTemp<double> eEG2Release;
    ChoiceEntryLeverageCtrl eEG2Controller;
    BoolEntry eEG2ControllerInvert;
    NumEntryTemp<uint8_t> eEG2ControllerAttackInfluence;
    NumEntryTemp<uint8_t> eEG2ControllerDecayInfluence;
    NumEntryTemp<uint8_t> eEG2ControllerReleaseInfluence;
    NumEntryTemp<double> eLFO2Frequency;
    NumEntryTemp<uint16_t> eLFO2InternalDepth;
    NumEntryTemp<uint16_t> eLFO2ControlDepth;
    ChoiceEntry<gig::lfo2_ctrl_t> eLFO2Controller;
    BoolEntry eLFO2FlipPhase;
    BoolEntry eLFO2Sync;
    NumEntryTemp<double> eEG3Attack;
    NumEntryTemp<int16_t> eEG3Depth;
    NumEntryTemp<double> eLFO3Frequency;
    NumEntryTemp<int16_t> eLFO3InternalDepth;
    NumEntryTemp<int16_t> eLFO3ControlDepth;
    ChoiceEntry<gig::lfo3_ctrl_t> eLFO3Controller;
    BoolEntry eLFO3Sync;
    BoolEntry eVCFEnabled;
    ChoiceEntry<gig::vcf_type_t> eVCFType;
    ChoiceEntry<gig::vcf_cutoff_ctrl_t> eVCFCutoffController;
    BoolEntry eVCFCutoffControllerInvert;
    NumEntryTemp<uint8_t> eVCFCutoff;
    ChoiceEntry<gig::curve_type_t> eVCFVelocityCurve;
    NumEntryTemp<uint8_t> eVCFVelocityScale;
    NumEntryTemp<uint8_t> eVCFVelocityDynamicRange;
    NumEntryTemp<uint8_t> eVCFResonance;
    BoolEntry eVCFResonanceDynamic;
    ChoiceEntry<gig::vcf_res_ctrl_t> eVCFResonanceController;
    BoolEntry eVCFKeyboardTracking;
    NumEntryTemp<uint8_t> eVCFKeyboardTrackingBreakpoint;
    ChoiceEntry<gig::curve_type_t> eVelocityResponseCurve;
    NumEntryTemp<uint8_t> eVelocityResponseDepth;
    NumEntryTemp<uint8_t> eVelocityResponseCurveScaling;
    ChoiceEntry<gig::curve_type_t> eReleaseVelocityResponseCurve;
    NumEntryTemp<uint8_t> eReleaseVelocityResponseDepth;
    NumEntryTemp<uint8_t> eReleaseTriggerDecay;
    NumEntryX<uint8_t> eCrossfade_in_start;
    NumEntryX<uint8_t> eCrossfade_in_end;
    NumEntryX<uint8_t> eCrossfade_out_start;
    NumEntryX<uint8_t> eCrossfade_out_end;
    BoolEntry ePitchTrack;
    ChoiceEntry<gig::dim_bypass_ctrl_t> eDimensionBypass;
    NumEntryTemp<int8_t> ePan;
    BoolEntry eSelfMask;
    ChoiceEntryLeverageCtrl eAttenuationController;
    BoolEntry eInvertAttenuationController;
    NumEntryTemp<uint8_t> eAttenuationControllerThreshold;
    NumEntryTemp<uint8_t> eChannelOffset;
    BoolEntry eSustainDefeat;
    BoolEntry eMSDecode;
    NumEntryTemp<uint16_t> eSampleStartOffset;
    // NumEntryX<uint8_t> eUnityNote;
    NoteEntry eUnityNote;
    NumEntryX<int16_t> eFineTune;
    NumEntryGain eGain;
    NumEntryX<uint32_t> eSampleLoops;

    void addProp(LabelWidget& labelwidget);
    void addString(char* labelText, Gtk::Label*& label,
                   Gtk::Entry*& widget);
    void addHeader(char* text);
    void nextPage();

    RegionChooser m_RegionChooser;
    DimRegionChooser m_DimRegionChooser;

    void set_dim_region(gig::DimensionRegion* d);
    PropDialog propDialog;
    InstrumentProps instrumentProps;

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

    Gtk::Notebook m_Notebook;
    Gtk::Notebook m_TreeViewNotebook;

    Gtk::Table* table[5];

    // dimensionregion parameter widgets
    // TODO: remove:
    Gtk::Label* lSample;
    Gtk::Entry* wSample;

    struct SampleImportItem {
        gig::Sample*  gig_sample;  // pointer to the gig::Sample to which the sample data should be imported to
        Glib::ustring sample_path; // file name of the sample to be imported
    };
    std::list<SampleImportItem> m_SampleImportQueue;

    void VCFEnabled_toggled();
    void VCFCutoffController_changed();
    void VCFResonanceController_changed();
    void EG1InfiniteSustain_toggled();
    void EG2InfiniteSustain_toggled();
    void EG1Controller_changed();
    void EG2Controller_changed();
    void AttenuationController_changed();
    void LFO1Controller_changed();
    void LFO2Controller_changed();
    void LFO3Controller_changed();
    void crossfade1_changed();
    void crossfade2_changed();
    void crossfade3_changed();
    void crossfade4_changed();

    void on_action_file_new();
    void on_action_file_open();
    void on_action_file_save();
    void on_action_file_save_as();
    void on_action_file_properties();
    void on_action_help_about();

    // sample right-click popup actions
    void on_sample_treeview_button_release(GdkEventButton* button);
    void on_action_sample_properties();
    void on_action_add_group();
    void on_action_add_sample();
    void on_action_remove_sample();

    LoadDialog* load_dialog;
    Loader* loader;
    void load_gig(gig::File* gig, const char* filename);

    gig::File* file;

    void on_button_release(GdkEventButton* button);
    void on_sample_treeview_drag_data_get(const Glib::RefPtr<Gdk::DragContext>&, Gtk::SelectionData& selection_data, guint, guint);
    void on_sample_label_drop_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int, int, const Gtk::SelectionData& selection_data, guint, guint time);
    void sample_name_changed(const Gtk::TreeModel::Path& path, const Gtk::TreeModel::iterator& iter);
    void instrument_name_changed(const Gtk::TreeModel::Path& path, const Gtk::TreeModel::iterator& iter);

    void __import_queued_samples();

  Gtk::Menu* popup_menu;
};

#endif
