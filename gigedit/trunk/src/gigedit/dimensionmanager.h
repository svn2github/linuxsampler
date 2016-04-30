/*                                                         -*- c++ -*-
 * Copyright (C) 2006 - 2016 Andreas Persson
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

#ifndef GIGEDIT_DIMENSIONMANAGER_H
#define GIGEDIT_DIMENSIONMANAGER_H

#include <glibmm/property.h>
#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include <gtkmm/layout.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/checkbutton.h>

#include <gig.h>
#include <set>
#include "ManagedWindow.h"

class DimTypeCellRenderer : public Gtk::CellRendererText {
public:
    Glib::PropertyProxy<gig::dimension_t> propertyDimType() {
        return m_propertyDimType.get_proxy();
    }

    Glib::PropertyProxy<int> propertyUsageCount() {
        return m_propertyUsageCount.get_proxy();
    }

    Glib::PropertyProxy<int> propertyTotalRegions() {
        return m_propertyTotalRegions.get_proxy();
    }

    DimTypeCellRenderer();
protected:
    void typeChanged();
    void statsChanged();
private:
    Glib::Property<gig::dimension_t> m_propertyDimType;
    Glib::Property<int> m_propertyUsageCount;
    Glib::Property<int> m_propertyTotalRegions;
};

class IntSetCellRenderer : public Gtk::CellRendererText {
public:
    Glib::PropertyProxy<std::set<int> > propertyValue() {
        return m_propertyValue.get_proxy();
    }

    IntSetCellRenderer();
protected:
    void valueChanged();
private:
    Glib::Property<std::set<int> > m_propertyValue;
};

class DimensionManager : public ManagedWindow {
public:
    sigc::signal<void, gig::Region*> region_to_be_changed_signal;
    sigc::signal<void, gig::Region*> region_changed_signal;

    DimensionManager();
    void show(gig::Region* region);
    void set_region(gig::Region* region);

    // implementation for abstract methods of interface class "ManagedWindow"
    virtual Settings::Property<int>* windowSettingX() { return &Settings::singleton()->dimensionManagerWindowX; }
    virtual Settings::Property<int>* windowSettingY() { return &Settings::singleton()->dimensionManagerWindowY; }
    virtual Settings::Property<int>* windowSettingWidth() { return &Settings::singleton()->dimensionManagerWindowW; }
    virtual Settings::Property<int>* windowSettingHeight() { return &Settings::singleton()->dimensionManagerWindowH; }
    
protected:
    gig::Region* region;
    Gtk::VBox vbox;
    Gtk::HButtonBox buttonBox;
    Gtk::ScrolledWindow scrolledWindow;
    Gtk::TreeView treeView;
    Gtk::Button addButton;
    Gtk::Button removeButton;
    Gtk::CheckButton allRegionsCheckBox;

    DimTypeCellRenderer m_cellRendererDimType;
    IntSetCellRenderer m_cellRendererIntSet;

    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        ModelColumns() {
            add(m_type);
            add(m_bits);
            add(m_zones);
            add(m_description);
            add(m_usageCount);
            add(m_totalRegions);
        }

        Gtk::TreeModelColumn<gig::dimension_t> m_type;
        Gtk::TreeModelColumn<std::set<int> > m_bits;
        Gtk::TreeModelColumn<std::set<int> > m_zones;
        Gtk::TreeModelColumn<Glib::ustring> m_description;
        Gtk::TreeModelColumn<int> m_usageCount;
        Gtk::TreeModelColumn<int> m_totalRegions;
    } tableModel;

    class ComboModelColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        ComboModelColumns() {
            add(m_type_id);
            add(m_type_name);
        }

        Gtk::TreeModelColumn<int> m_type_id;
        Gtk::TreeModelColumn<Glib::ustring> m_type_name;
    } comboModel;

    Glib::RefPtr<Gtk::ListStore> refTableModel;
    bool ignoreColumnClicked; //HACK: Prevents that onColumnClicked() gets called multiple times or at times where it is not desired

    void onAllRegionsCheckBoxToggled();
    void onColumnClicked();
    void refreshManager();
    void addDimension();
    void removeDimension();
    bool allRegions() const;
};

#endif // GIGEDIT_DIMENSIONMANAGER_H
