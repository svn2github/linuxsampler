/*
    Copyright (c) 2014-2016 Christian Schoenebeck
    
    This file is part of "gigedit" and released under the terms of the
    GNU General Public License version 2.
*/

#ifndef GIGEDIT_REFERENCESVIEW_H
#define GIGEDIT_REFERENCESVIEW_H

#include <gig.h>
#include <gtkmm.h>
#include "wrapLabel.hh"
#include "ManagedWindow.h"

/** @brief Sample reference browser dialog.
 *
 * Shows a modal dialog with a tree view showing all instruments and their
 * respective regions which reference the selected sample at least once.
 */
class ReferencesView : public ManagedDialog {
public:
    ReferencesView(Gtk::Window& parent);
    void setSample(gig::Sample* sample);

    // When the user single clicked on a sample reference on this reference
    // view dialog, then this signal is emitted and the dimension region editor
    // shall select the respective, instrument, region and dimension region for
    // further editing. The editor shall return true if selection was successful
    // or should return false on errors.
    sigc::signal<bool, gig::DimensionRegion*> dimension_region_selected;

    // implementation for abstract methods of interface class "ManagedDialog"
    virtual Settings::Property<int>* windowSettingX() { return &Settings::singleton()->sampleRefsWindowX; }
    virtual Settings::Property<int>* windowSettingY() { return &Settings::singleton()->sampleRefsWindowY; }
    virtual Settings::Property<int>* windowSettingWidth() { return &Settings::singleton()->sampleRefsWindowW; }
    virtual Settings::Property<int>* windowSettingHeight() { return &Settings::singleton()->sampleRefsWindowH; }

protected:
    gig::Sample* m_sample;

    Gtk::HButtonBox      m_buttonBox;
    Gtk::ScrolledWindow  m_scrolledWindow;
    Gtk::TreeView        m_treeView;
    Gtk::Button          m_closeButton;
#if GTKMM_MAJOR_VERSION < 3
    view::WrapLabel      m_descriptionLabel;
#else
    Gtk::Label           m_descriptionLabel;
#endif
#if GTKMM_MAJOR_VERSION < 3
    view::WrapLabel      m_summaryLabel;
#else
    Gtk::Label           m_summaryLabel;
#endif

    class RefsTreeModel : public Gtk::TreeModel::ColumnRecord {
    public:
        RefsTreeModel() {
            add(m_col_name);
            add(m_col_instr);
            add(m_col_region);
            add(m_col_refcount);
        }

        Gtk::TreeModelColumn<Glib::ustring>    m_col_name;
        Gtk::TreeModelColumn<gig::Instrument*> m_col_instr;
        Gtk::TreeModelColumn<gig::Region*>     m_col_region;
        Gtk::TreeModelColumn<Glib::ustring>    m_col_refcount;
    } m_columns;

    class RefsTreeStore : public Gtk::TreeStore {
    public:
        static Glib::RefPtr<RefsTreeStore> create(const RefsTreeModel& columns) {
            return Glib::RefPtr<RefsTreeStore>( new RefsTreeStore(columns) );
        }
    protected:
        RefsTreeStore(const RefsTreeModel& columns) : Gtk::TreeStore(columns) {}
    };

    Glib::RefPtr<RefsTreeStore>  m_refTreeModel;

    void onSelectionChanged();
};

#endif // GIGEDIT_REFERENCESVIEW_H
