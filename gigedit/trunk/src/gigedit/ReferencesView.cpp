/*
    Copyright (c) 2014 Christian Schoenebeck
    
    This file is part of "gigedit" and released under the terms of the
    GNU General Public License version 2.
*/

#include "ReferencesView.h"
#include "global.h"
#include "compat.h"

Glib::ustring gig_to_utf8(const gig::String& gig_string);
Glib::ustring note_str(int note);

ReferencesView::ReferencesView(Gtk::Window& parent) :
    Gtk::Dialog("", parent, true), m_sample(NULL),
    m_closeButton(Gtk::Stock::CLOSE), m_descriptionLabel()
{
    set_title("Nothing selected");

    m_scrolledWindow.add(m_treeView);
    m_scrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    get_vbox()->pack_start(m_descriptionLabel, Gtk::PACK_SHRINK);
    get_vbox()->pack_start(m_scrolledWindow);
    get_vbox()->pack_start(m_summaryLabel, Gtk::PACK_SHRINK);
    get_vbox()->pack_start(m_buttonBox, Gtk::PACK_SHRINK);

#if GTKMM_MAJOR_VERSION >= 3
    m_descriptionLabel.set_line_wrap();
#endif
    m_descriptionLabel.set_text(_(
        "Selected sample is referenced by the following instruments and their "
        "respective regions:"
    ));

    m_refTreeModel = RefsTreeStore::create(m_columns);
    m_treeView.set_model(m_refTreeModel);
    m_treeView.set_tooltip_text(_(
        "Amount of times the selected sample in question is referenced."
    ));
    m_treeView.append_column(_("Name"), m_columns.m_col_name);
    m_treeView.append_column(_("References"), m_columns.m_col_refcount);
    m_treeView.set_headers_visible(true);
    //m_treeView.get_selection()->set_mode(Gtk::SELECTION_MULTIPLE);
    //m_treeView.get_selection()->signal_changed().connect(
    //    sigc::mem_fun(*this, &ReferencesView::onSelectionChanged)
    //);

    m_buttonBox.set_layout(Gtk::BUTTONBOX_END);
    m_buttonBox.set_border_width(5);
    m_buttonBox.pack_start(m_closeButton, Gtk::PACK_SHRINK);

    m_closeButton.signal_clicked().connect(
        sigc::mem_fun(*this, &ReferencesView::hide)
    );

    show_all_children();
}

void ReferencesView::setSample(gig::Sample* sample) {
    m_refTreeModel->clear();

    m_sample = sample;
    if (!sample) {
        set_title("Nothing selected");
        m_summaryLabel.set_text("");
        return;
    }

    set_title(_("References of Sample \"") + sample->pInfo->Name + "\"");

    int filesRefCount = 0;

    gig::File* gig = (gig::File*) sample->GetParent();

    for (gig::Instrument* instrument = gig->GetFirstInstrument(); instrument;
         instrument = gig->GetNextInstrument())
    {
        Gtk::TreeModel::iterator iterInstr = m_refTreeModel->append();
        Gtk::TreeModel::Row rowInstr = *iterInstr;
        rowInstr[m_columns.m_col_name]   = gig_to_utf8(instrument->pInfo->Name);
        rowInstr[m_columns.m_col_instr]  = instrument;
        rowInstr[m_columns.m_col_region] = NULL;

        int instrumentsRefcount = 0;
        for (gig::Region* rgn = instrument->GetFirstRegion(); rgn;
             rgn = instrument->GetNextRegion())
        {
            int regionsRefCount = 0;

            for (int i = 0; i < 256; ++i) {
                if (!rgn->pDimensionRegions[i]) continue;
                if (rgn->pDimensionRegions[i]->pSample != sample) continue;
                regionsRefCount++;
            }
            if (!regionsRefCount) continue;

            instrumentsRefcount += regionsRefCount;

            Gtk::TreeModel::iterator iterRegion = m_refTreeModel->append(rowInstr.children());
            Gtk::TreeModel::Row rowRegion = *iterRegion;
            rowRegion[m_columns.m_col_name] =
                _("Region from ") + note_str(rgn->KeyRange.low) + _(" to ") + note_str(rgn->KeyRange.high);
            rowRegion[m_columns.m_col_instr]  = NULL;
            rowRegion[m_columns.m_col_region] = rgn;
            rowRegion[m_columns.m_col_refcount] =
                ToString(regionsRefCount) + " " + _("Refs.");
        }

        if (!instrumentsRefcount) {
            m_refTreeModel->erase(iterInstr);
            continue;
        }

        rowInstr[m_columns.m_col_refcount] =
            ToString(instrumentsRefcount) + " " + _("Refs.");
        
        filesRefCount += instrumentsRefcount;
    }

    if (filesRefCount)
        m_summaryLabel.set_text(_("Total References: ") + ToString(filesRefCount));
    else
        m_summaryLabel.set_text(_("This sample is not referenced at all."));

    // unfold all instruments by default
    m_treeView.expand_all();
}
