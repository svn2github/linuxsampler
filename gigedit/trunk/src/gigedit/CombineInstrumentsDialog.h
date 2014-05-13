/*
    Copyright (c) 2014 Christian Schoenebeck
    
    This file is part of "gigedit" and released under the terms of the
    GNU General Public License version 2.
*/

#ifndef GIGEDIT_COMBINEINSTRUMENTSDIALOG
#define GIGEDIT_COMBINEINSTRUMENTSDIALOG

#include <gig.h>

#include <gtkmm/buttonbox.h>
#include <gtkmm/window.h>
#include <gtkmm/dialog.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>

#include "wrapLabel.hh"

/**
 * @brief Modal dialog which allows to merge instruments.
 *
 * This dialog shows a list of all instruments of the currently open .gig file
 * in gigedit and allows the user to shift select a set of instruments to be
 * combined.
 *
 * If the user successfully combined instruments in this dialog, then
 * newCombinedInstrument() will return a pointer to that new instrument.
 */
class CombineInstrumentsDialog : public Gtk::Dialog {
public:
    CombineInstrumentsDialog(Gtk::Window& parent, gig::File* gig);
    bool fileWasChanged() const;
    gig::Instrument* newCombinedInstrument() const;
protected:
    gig::File* m_gig;
    bool m_fileWasChanged;
    gig::Instrument* m_newCombinedInstrument;

    Gtk::HButtonBox m_buttonBox;
    Gtk::TreeView   m_treeView;
    Gtk::Button     m_cancelButton;
    Gtk::Button     m_OKButton;
#if GTKMM_MAJOR_VERSION < 3
    view::WrapLabel m_descriptionLabel;
#else
    Gtk::Label      m_descriptionLabel;
#endif

    class ListModel : public Gtk::TreeModel::ColumnRecord {
    public:
        ListModel() {
            add(m_col_name);
            add(m_col_instr);
        }

        Gtk::TreeModelColumn<Glib::ustring>    m_col_name;
        Gtk::TreeModelColumn<gig::Instrument*> m_col_instr;
    } m_columns;

    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

    void combineSelectedInstruments();
    void onSelectionChanged();
};

#endif // GIGEDIT_COMBINEINSTRUMENTSDIALOG
