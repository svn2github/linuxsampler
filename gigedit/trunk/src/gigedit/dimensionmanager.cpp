/*
 * Copyright (C) 2006-2014 Andreas Persson
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

#include "dimensionmanager.h"

#include <gtkmm/stock.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/dialog.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/table.h>

#include "global.h"
#include "compat.h"

// returns a human readable name of the given dimension type
Glib::ustring dimTypeAsString(gig::dimension_t d) {
    char buf[32];
    switch (d) {
        case gig::dimension_none:
            return _("None");
        case gig::dimension_samplechannel:
            return _("Sample Channel");
        case gig::dimension_layer:
            return _("Layer");
        case gig::dimension_velocity:
            return _("Velocity");
        case gig::dimension_channelaftertouch:
            return _("Aftertouch");
        case gig::dimension_releasetrigger:
            return _("Release Trigger");
        case gig::dimension_keyboard:
            return _("Keyswitching");
        case gig::dimension_roundrobin:
            return _("Round Robin");
        case gig::dimension_random:
            return _("Random Generator");
        case gig::dimension_smartmidi:
            return _("Smart MIDI");
        case gig::dimension_roundrobinkeyboard:
            return _("Keyboard Round Robin");
        case gig::dimension_modwheel:
            return _("Modulation Wheel");
        case gig::dimension_breath:
            return _("Breath Ctrl.");
        case gig::dimension_foot:
            return _("Foot Ctrl.");
        case gig::dimension_portamentotime:
            return _("Portamento Time Ctrl.");
        case gig::dimension_effect1:
            return _("Effect Ctrl. 1");
        case gig::dimension_effect2:
            return _("Effect Ctrl. 2");
        case gig::dimension_genpurpose1:
            return _("General Purpose Ctrl. 1");
        case gig::dimension_genpurpose2:
            return _("General Purpose Ctrl. 2");
        case gig::dimension_genpurpose3:
            return _("General Purpose Ctrl. 3");
        case gig::dimension_genpurpose4:
            return _("General Purpose Ctrl. 4");
        case gig::dimension_sustainpedal:
            return _("Sustain Pedal");
        case gig::dimension_portamento:
            return _("Portamento Ctrl.");
        case gig::dimension_sostenutopedal:
            return _("Sostenuto Pedal");
        case gig::dimension_softpedal:
            return _("Soft Pedal");
        case gig::dimension_genpurpose5:
            return _("General Purpose Ctrl. 5");
        case gig::dimension_genpurpose6:
            return _("General Purpose Ctrl. 6");
        case gig::dimension_genpurpose7:
            return _("General Purpose Ctrl. 7");
        case gig::dimension_genpurpose8:
            return _("General Purpose Ctrl. 8");
        case gig::dimension_effect1depth:
            return _("Effect 1 Depth");
        case gig::dimension_effect2depth:
            return _("Effect 2 Depth");
        case gig::dimension_effect3depth:
            return _("Effect 3 Depth");
        case gig::dimension_effect4depth:
            return _("Effect 4 Depth");
        case gig::dimension_effect5depth:
            return _("Effect 5 Depth");
        default:
            sprintf(buf, "Unknown Type (0x%x) !!!", d);
            return buf;
    }
}

// returns a human readable description of the given dimension
static Glib::ustring __dimDescriptionAsString(gig::dimension_t d) {
    switch (d) {
        case gig::dimension_none:
            return _("Dimension not in use");
        case gig::dimension_samplechannel:
            return _("If used sample has more than one channel (thus is not mono)");
        case gig::dimension_layer:
            return _("For layering of up to 8 instruments (and eventually crossfading of 2 or 4 layers");
        case gig::dimension_velocity:
            return _("Key Velocity (this is the only dimension in gig2 where the ranges can exactly be defined)");
        case gig::dimension_channelaftertouch:
            return _("Channel Key Pressure");
        case gig::dimension_releasetrigger:
            return _("Special dimension for triggering samples on releasing a key");
        case gig::dimension_keyboard:
            return _("Dimension for keyswitching (keyboard)");
        case gig::dimension_roundrobin:
            return _("Different samples triggered each time a note is played, dimension regions selected in sequence");
        case gig::dimension_random:
            return _("Different samples triggered each time a note is played, random order");
        case gig::dimension_smartmidi:
            return _("For MIDI tools like legato and repetition mode");
        case gig::dimension_roundrobinkeyboard:
            return _("Different samples triggered each time a note is played, any key advances the counter");
        case gig::dimension_modwheel:
            return _("MIDI Controller 1");
        case gig::dimension_breath:
            return _("MIDI Controller 2");
        case gig::dimension_foot:
            return _("MIDI Controller 4");
        case gig::dimension_portamentotime:
            return _("MIDI Controller 5");
        case gig::dimension_effect1:
            return _("MIDI Controller 12");
        case gig::dimension_effect2:
            return _("MIDI Controller 13");
        case gig::dimension_genpurpose1:
            return _("Slider, MIDI Controller 16");
        case gig::dimension_genpurpose2:
            return _("Slider, MIDI Controller 17");
        case gig::dimension_genpurpose3:
            return _("Slider, MIDI Controller 18");
        case gig::dimension_genpurpose4:
            return _("Slider, MIDI Controller 19");
        case gig::dimension_sustainpedal:
            return _("MIDI Controller 64");
        case gig::dimension_portamento:
            return _("MIDI Controller 65");
        case gig::dimension_sostenutopedal:
            return _("MIDI Controller 66");
        case gig::dimension_softpedal:
            return _("MIDI Controller 67");
        case gig::dimension_genpurpose5:
            return _("Button, MIDI Controller 80");
        case gig::dimension_genpurpose6:
            return _("Button, MIDI Controller 81");
        case gig::dimension_genpurpose7:
            return _("Button, MIDI Controller 82");
        case gig::dimension_genpurpose8:
            return _("Button, MIDI Controller 83");
        case gig::dimension_effect1depth:
            return _("MIDI Controller 91");
        case gig::dimension_effect2depth:
            return _("MIDI Controller 92");
        case gig::dimension_effect3depth:
            return _("MIDI Controller 93");
        case gig::dimension_effect4depth:
            return _("MIDI Controller 94");
        case gig::dimension_effect5depth:
            return _("MIDI Controller 95");
        default:
            return _("Please report this !!!");
    }
}

DimTypeCellRenderer::DimTypeCellRenderer() :
    Glib::ObjectBase(typeid(DimTypeCellRenderer)),
    Gtk::CellRendererText(),
    m_propertyDimType(*this, "gigdimension_t", gig::dimension_none),
    m_propertyUsageCount(*this, "intusagecount", 0),
    m_propertyTotalRegions(*this, "inttotalregions", 0)
{
    propertyDimType().signal_changed().connect(
        sigc::mem_fun(*this, &DimTypeCellRenderer::typeChanged)
    );
    propertyUsageCount().signal_changed().connect(
        sigc::mem_fun(*this, &DimTypeCellRenderer::statsChanged)
    );
    propertyTotalRegions().signal_changed().connect(
        sigc::mem_fun(*this, &DimTypeCellRenderer::statsChanged)
    );
}

void DimTypeCellRenderer::typeChanged() {
    gig::dimension_t type = propertyDimType();
    Glib::ustring s = dimTypeAsString(type);
    property_text() = s;
}

void DimTypeCellRenderer::statsChanged() {
    int usageCount   = propertyUsageCount();
    int totalRegions = propertyTotalRegions();
    bool bDimensionExistsOnAllRegions = (usageCount == totalRegions);
    property_foreground() = ((bDimensionExistsOnAllRegions) ? "black" : "gray");
}

IntSetCellRenderer::IntSetCellRenderer() :
    Glib::ObjectBase(typeid(IntSetCellRenderer)),
    Gtk::CellRendererText(),
    m_propertyValue(*this, "stdintset", std::set<int>())
{
    propertyValue().signal_changed().connect(
        sigc::mem_fun(*this, &IntSetCellRenderer::valueChanged)
    );
}

void IntSetCellRenderer::valueChanged() {
    Glib::ustring s;
    std::set<int> v = propertyValue();
    for (std::set<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        s += ToString(*it);
        if (*it != *v.rbegin()) s += "|";
    }
    property_text() = s;
    property_foreground() = (v.size() > 1) ? "gray" : "black";
}

DimensionManager::DimensionManager() :
addButton(Gtk::Stock::ADD), removeButton(Gtk::Stock::REMOVE),
allRegionsCheckBox(_("All Regions"))
{
    set_title(_("Dimensions of selected Region"));
    add(vbox);
    scrolledWindow.add(treeView);
    vbox.pack_start(scrolledWindow);
    scrolledWindow.show();
    vbox.pack_start(buttonBox, Gtk::PACK_SHRINK);
    buttonBox.set_layout(Gtk::BUTTONBOX_END);
    buttonBox.set_border_width(5);
    buttonBox.show();
    buttonBox.pack_start(allRegionsCheckBox, Gtk::PACK_EXPAND_PADDING);
    buttonBox.pack_start(addButton, Gtk::PACK_SHRINK);
    buttonBox.pack_start(removeButton, Gtk::PACK_SHRINK);
    addButton.show();
    removeButton.show();
    allRegionsCheckBox.set_tooltip_text(
        _("Enable this if you want to edit dimensions of all regions simultaniously.")
    );

    // setup the table
    refTableModel = Gtk::ListStore::create(tableModel);
    treeView.set_model(refTableModel);
    treeView.append_column(_("Dimension Type"), m_cellRendererDimType);
    treeView.append_column(_("Bits"), m_cellRendererIntSet);
    treeView.append_column(_("Zones"), m_cellRendererIntSet);
    treeView.append_column(_("Description"), tableModel.m_description);
    treeView.get_column(0)->add_attribute(m_cellRendererDimType.propertyDimType(), tableModel.m_type);
    treeView.get_column(0)->add_attribute(m_cellRendererDimType.propertyUsageCount(), tableModel.m_usageCount);
    treeView.get_column(0)->add_attribute(m_cellRendererDimType.propertyTotalRegions(), tableModel.m_totalRegions);
    treeView.get_column(1)->add_attribute(m_cellRendererIntSet.propertyValue(), tableModel.m_bits);
    treeView.get_column(2)->add_attribute(m_cellRendererIntSet.propertyValue(), tableModel.m_zones);
    treeView.show();

    addButton.signal_clicked().connect(
        sigc::mem_fun(*this, &DimensionManager::addDimension)
    );

    removeButton.signal_clicked().connect(
        sigc::mem_fun(*this, &DimensionManager::removeDimension)
    );
    allRegionsCheckBox.signal_toggled().connect(
        sigc::mem_fun(*this, &DimensionManager::onAllRegionsCheckBoxToggled)
    );

    show_all_children();
    
    resize(460,300);
}

bool DimensionManager::allRegions() const {
    return allRegionsCheckBox.get_active();
}

void DimensionManager::onAllRegionsCheckBoxToggled() {
    set_title(
        allRegions() ? _("Dimensions of all Regions") :  _("Dimensions of selected Region")
    );
    treeView.set_tooltip_text(
        allRegions()
            ? _("Dimensions and numbers in gray indicates a difference among the individual regions.")
            : _("You are currently only viewing dimensions of the currently selected region.")
    );
    refreshManager();
}

// following two data types are just used in DimensionManager::refresManager(),
// due to the maps template nature however, they must be declared at global
// space to avoid compilation errors
struct _DimDef {
    std::set<int> bits;
    std::set<int> zones;
    int usageCount;
};
typedef std::map<gig::dimension_t, _DimDef> _Dimensions;

// update all GUI elements according to current gig::Region informations
void DimensionManager::refreshManager() {
    set_sensitive(false);
    refTableModel->clear();
    if (allRegions()) {
        if (region) {
            _Dimensions dims;
            gig::Instrument* instr = (gig::Instrument*)region->GetParent();
            int iRegionsCount = 0;
            for (gig::Region* rgn = instr->GetFirstRegion(); rgn; rgn = instr->GetNextRegion(), ++iRegionsCount) {
                for (uint i = 0; i < rgn->Dimensions; i++) {
                    gig::dimension_def_t* dim = &rgn->pDimensionDefinitions[i];
                    dims[dim->dimension].bits.insert(dim->bits);
                    dims[dim->dimension].zones.insert(dim->zones);
                    dims[dim->dimension].usageCount++;
                }
            }
            for (_Dimensions::const_iterator it = dims.begin(); it != dims.end(); ++it) {
                Gtk::TreeModel::Row row = *(refTableModel->append());
                row[tableModel.m_type] = it->first;
                row[tableModel.m_bits] = it->second.bits;
                row[tableModel.m_zones] = it->second.zones;
                row[tableModel.m_description] = __dimDescriptionAsString(it->first);
                row[tableModel.m_usageCount] = it->second.usageCount;
                row[tableModel.m_totalRegions] = iRegionsCount;
            }
        }
    } else {
        if (region) {
            for (uint i = 0; i < region->Dimensions; i++) {
                gig::dimension_def_t* dim = &region->pDimensionDefinitions[i];
                Gtk::TreeModel::Row row = *(refTableModel->append());
                std::set<int> vBits;
                vBits.insert(dim->bits);
                row[tableModel.m_bits] = vBits;
                std::set<int> vZones;
                vZones.insert(dim->zones);
                row[tableModel.m_zones] = vZones;
                row[tableModel.m_description] = __dimDescriptionAsString(dim->dimension);
                row[tableModel.m_type] = dim->dimension;
                row[tableModel.m_usageCount] = 1;
                row[tableModel.m_totalRegions] = 1;
            }
        }
    }
    set_sensitive(region);
}

void DimensionManager::show(gig::Region* region) {
    this->region = region;
    refreshManager();
    Gtk::Window::show();
    deiconify();
}

void DimensionManager::set_region(gig::Region* region) {
    this->region = region;
    refreshManager();
}

void DimensionManager::addDimension() {
    Gtk::Dialog dialog(_("New Dimension"), true /*modal*/);
    // add dimension type combo box to the dialog
    Glib::RefPtr<Gtk::ListStore> refComboModel = Gtk::ListStore::create(comboModel);
    for (int i = 0x01; i < 0xff; i++) {
        Glib::ustring sType =
            dimTypeAsString(static_cast<gig::dimension_t>(i));
        if (sType.find("Unknown") != 0) {
            Gtk::TreeModel::Row row = *(refComboModel->append());
            row[comboModel.m_type_id]   = i;
            row[comboModel.m_type_name] = sType;
        }
    }
    Gtk::Table table(2, 2);
    Gtk::Label labelDimType(_("Dimension:"), Gtk::ALIGN_START);
    Gtk::ComboBox comboDimType;
    comboDimType.set_model(refComboModel);
    comboDimType.pack_start(comboModel.m_type_id);
    comboDimType.pack_start(comboModel.m_type_name);
    Gtk::Label labelZones(_("Zones:"), Gtk::ALIGN_START);
    table.attach(labelDimType, 0, 1, 0, 1);
    table.attach(comboDimType, 1, 2, 0, 1);
    table.attach(labelZones, 0, 1, 1, 2);
    dialog.get_vbox()->pack_start(table);

    // number of zones: use a combo box with fix values for gig
    // v2 and a spin button for v3
    Gtk::ComboBoxText comboZones;
    Gtk::SpinButton spinZones;
    bool version2 = false;
    if (region) {
        gig::File* file = (gig::File*)region->GetParent()->GetParent();
        version2 = file->pVersion && file->pVersion->major == 2;
    }
    if (version2) {
        for (int i = 1; i <= 5; i++) {
            char buf[3];
            sprintf(buf, "%d", 1 << i);
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 24) || GTKMM_MAJOR_VERSION < 2
            comboZones.append_text(buf);
#else
            comboZones.append(buf);
#endif
        }
        table.attach(comboZones, 1, 2, 1, 2);
    } else {
        spinZones.set_increments(1, 8);
        spinZones.set_numeric(true);
        spinZones.set_range(2, 128);
        spinZones.set_value(2);
        table.attach(spinZones, 1, 2, 1, 2);
    }

    dialog.add_button(Gtk::Stock::OK, 0);
    dialog.add_button(Gtk::Stock::CANCEL, 1);
    dialog.show_all_children();

    if (!dialog.run()) { // OK selected ...
        Gtk::TreeModel::iterator iterType = comboDimType.get_active();
        if (!iterType) return;
        Gtk::TreeModel::Row rowType = *iterType;
        if (!rowType) return;
        int iTypeID = rowType[comboModel.m_type_id];
        gig::dimension_t type = static_cast<gig::dimension_t>(iTypeID);
        gig::dimension_def_t dim;
        dim.dimension = type;

        if (version2) {
            if (comboZones.get_active_row_number() < 0) return;
            dim.bits = comboZones.get_active_row_number() + 1;
            dim.zones = 1 << dim.bits;
        } else {
            dim.zones = spinZones.get_value_as_int();
            dim.bits = zoneCountToBits(dim.zones);
        }

        // assemble the list of regions where the selected dimension shall be
        // added to
        std::vector<gig::Region*> vRegions;
        if (allRegions()) {
            gig::Instrument* instr = (gig::Instrument*)region->GetParent();
            for (gig::Region* rgn = instr->GetFirstRegion(); rgn; rgn = instr->GetNextRegion()) {
                if (!rgn->GetDimensionDefinition(type)) vRegions.push_back(rgn);
            }
        } else vRegions.push_back(region);
            
        std::set<Glib::ustring> errors;

        for (uint iRgn = 0; iRgn < vRegions.size(); ++iRgn) {
            gig::Region* region = vRegions[iRgn];
            try {
                printf(
                    "Adding dimension (type=0x%x, bits=%d, zones=%d)\n",
                    dim.dimension, dim.bits, dim.zones
                );
                // notify everybody that we're going to update the region
                region_to_be_changed_signal.emit(region);
                // add the new dimension to the region
                // (implicitly creates new dimension regions)
                region->AddDimension(&dim);
                // let everybody know there was a change
                region_changed_signal.emit(region);
            } catch (RIFF::Exception e) {
                // notify that the changes are over (i.e. to avoid dead locks)
                region_changed_signal.emit(region);
                Glib::ustring txt = _("Could not add dimension: ") + e.Message;
                if (vRegions.size() == 1) {
                    // show error message directly
                    Gtk::MessageDialog msg(*this, txt, false, Gtk::MESSAGE_ERROR);
                    msg.run();
                } else {
                    // remember error, they are shown after all regions have been processed
                    errors.insert(txt);
                }
            }
        }
        // update all GUI elements
        refreshManager();

        if (!errors.empty()) {
            Glib::ustring txt = _(
                "The following errors occurred while trying to create the dimension on all regions:"
            );
            txt += "\n\n";
            for (std::set<Glib::ustring>::const_iterator it = errors.begin();
                 it != errors.end(); ++it)
            {
                txt += "-> " + *it + "\n";
            }
            txt += "\n";
            txt += _(
                "You might also want to check the console for further warnings and "
                "error messages."
            );
            Gtk::MessageDialog msg(*this, txt, false, Gtk::MESSAGE_ERROR);
            msg.run();
        }
    }
}

void DimensionManager::removeDimension() {        
    Glib::RefPtr<Gtk::TreeSelection> sel = treeView.get_selection();
    Gtk::TreeModel::iterator it = sel->get_selected();
    if (it) {
        Gtk::TreeModel::Row row = *it;
        gig::dimension_t type = row[tableModel.m_type];

        // assemble the list of regions where the selected dimension shall be
        // added to
        std::vector<gig::Region*> vRegions;
        if (allRegions()) {
            gig::Instrument* instr = (gig::Instrument*)region->GetParent();
            for (gig::Region* rgn = instr->GetFirstRegion(); rgn; rgn = instr->GetNextRegion()) {
                if (rgn->GetDimensionDefinition(type)) vRegions.push_back(rgn);
            }
        } else vRegions.push_back(region);

        std::set<Glib::ustring> errors;

        for (uint iRgn = 0; iRgn < vRegions.size(); ++iRgn) {
            gig::Region* region = vRegions[iRgn];
            gig::dimension_def_t* dim = region->GetDimensionDefinition(type);
            try {
                // notify everybody that we're going to update the region
                region_to_be_changed_signal.emit(region);
                // remove selected dimension    
                region->DeleteDimension(dim);
                // let everybody know there was a change
                region_changed_signal.emit(region);
            } catch (RIFF::Exception e) {
                // notify that the changes are over (i.e. to avoid dead locks)
                region_changed_signal.emit(region);
                Glib::ustring txt = _("Could not remove dimension: ") + e.Message;
                if (vRegions.size() == 1) {
                    // show error message directly
                    Gtk::MessageDialog msg(*this, txt, false, Gtk::MESSAGE_ERROR);
                    msg.run();
                } else {
                    // remember error, they are shown after all regions have been processed
                    errors.insert(txt);
                }
            }
        }
        // update all GUI elements
        refreshManager();

        if (!errors.empty()) {
            Glib::ustring txt = _(
                "The following errors occurred while trying to remove the dimension from all regions:"
            );
            txt += "\n\n";
            for (std::set<Glib::ustring>::const_iterator it = errors.begin();
                 it != errors.end(); ++it)
            {
                txt += "-> " + *it + "\n";
            }
            txt += "\n";
            txt += _(
                "You might also want to check the console for further warnings and "
                "error messages."
            );
            Gtk::MessageDialog msg(*this, txt, false, Gtk::MESSAGE_ERROR);
            msg.run();
        }
    }
}
