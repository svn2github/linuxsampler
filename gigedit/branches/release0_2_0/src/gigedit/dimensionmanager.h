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

#ifndef GIGEDIT_DIMENSIONMANAGER_H
#define GIGEDIT_DIMENSIONMANAGER_H

#include <gtkmm/window.h>
#include <gtkmm/layout.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include <gtkmm/scrolledwindow.h>

#include <gig.h>

class DimensionManager : public Gtk::Window {
public:
    sigc::signal<void, gig::Region*> region_to_be_changed_signal;
    sigc::signal<void, gig::Region*> region_changed_signal;

    DimensionManager();
    void show(gig::Region* region);
    void set_region(gig::Region* region);
protected:
    gig::Region* region;
    Gtk::VBox vbox;
    Gtk::HButtonBox buttonBox;
    Gtk::ScrolledWindow scrolledWindow;
    Gtk::TreeView treeView;
    Gtk::Button addButton;
    Gtk::Button removeButton;

    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        ModelColumns() {
            add(m_dim_type);
            add(m_bits);
            add(m_zones);
            add(m_description);
            add(m_definition);
        }

        Gtk::TreeModelColumn<Glib::ustring> m_dim_type;
        Gtk::TreeModelColumn<int> m_bits;
        Gtk::TreeModelColumn<int> m_zones;
        Gtk::TreeModelColumn<Glib::ustring> m_description;
        Gtk::TreeModelColumn<gig::dimension_def_t*> m_definition;
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

    void refreshManager();
    void addDimension();
    void removeDimension();
};

#endif // GIGEDIT_DIMENSIONMANAGER_H
