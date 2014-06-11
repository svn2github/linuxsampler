/*
    Copyright (c) 2014 Christian Schoenebeck
    
    This file is part of "gigedit" and released under the terms of the
    GNU General Public License version 2.
*/

#ifndef GIGEDIT_REFERENCESVIEW_H
#define GIGEDIT_REFERENCESVIEW_H

#include <gig.h>
#include <gtkmm.h>
#include "wrapLabel.hh"

/** @brief Sample reference browser dialog.
 *
 * Shows a modal dialog with a tree view showing all instruments and their
 * respective regions which reference the selected sample at least once.
 */
class ReferencesView : public Gtk::Dialog {
public:
    ReferencesView(Gtk::Window& parent);
    void setSample(gig::Sample* sample);
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
};

#endif // GIGEDIT_REFERENCESVIEW_H
