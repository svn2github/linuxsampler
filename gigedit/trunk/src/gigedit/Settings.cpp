/*
    Copyright (c) 2014-2016 Christian Schoenebeck
    
    This file is part of "gigedit" and released under the terms of the
    GNU General Public License version 2.
*/

#include "Settings.h"
#include <glib.h>
#include "global.h"
#include <glibmm/keyfile.h>
#include <iostream>
#include <stdio.h>
#include <fstream>

#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 40) || GTKMM_MAJOR_VERSION < 2
# define HAS_GLIB_KEYFILE_SAVE_TO_FILE 0
#else
# define HAS_GLIB_KEYFILE_SAVE_TO_FILE 1
#endif

static std::string configDir() {
    //printf("configDir '%s'\n", g_get_user_config_dir());
    return g_get_user_config_dir();
}

static std::string dirSep() {
    //printf("sep '%s'\n", G_DIR_SEPARATOR_S);
    return G_DIR_SEPARATOR_S;
}

static std::string configFile() {
    return configDir() + dirSep() + "gigedit.conf";
}

static std::string groupName(Settings::Group_t group) {
    switch (group) {
        case Settings::GLOBAL: return "Global";
        case Settings::MAIN_WINDOW: return "MainWindow";
        case Settings::SCRIPT_EDITOR: return "ScriptEditor";
        case Settings::DIMENSION_MANAGER: return "DimensionManager";
        case Settings::SCRIPT_SLOTS: return "ScriptSlots";
        case Settings::COMBINE_INSTRUMENTS: return "CombineInstruments";
        case Settings::MIDI_RULES: return "MidiRules";
        case Settings::FILE_PROPS: return "FileProps";
        case Settings::INSTR_PROPS: return "InstrProps";
        case Settings::SAMPLE_REFS: return "SampleRefs";
    }
    return "Global";
}

#if !HAS_GLIB_KEYFILE_SAVE_TO_FILE

static bool saveToFile(Glib::KeyFile* keyfile, std::string filename) {
    Glib::ustring s = keyfile->to_data();
    std::ofstream out;
    out.open(filename.c_str(), std::ios_base::out | std::ios_base::trunc);
    out << s;
    out.close();
    return true;
}

#endif // ! HAS_GLIB_KEYFILE_SAVE_TO_FILE

static Settings* _instance = NULL;
    
Settings* Settings::singleton() {
    if (!_instance) {
        _instance = new Settings;
        _instance->load();
    }
    return _instance;
}

Settings::Settings() : Glib::ObjectBase(typeid(Settings)),
    warnUserOnExtensions(*this, GLOBAL, "warnUserOnExtensions", true),
    syncSamplerInstrumentSelection(*this, GLOBAL, "syncSamplerInstrumentSelection", true),
    moveRootNoteWithRegionMoved(*this, GLOBAL, "moveRootNoteWithRegionMoved", true),
    autoRestoreWindowDimension(*this, GLOBAL, "autoRestoreWindowDimension", false),
    mainWindowX(*this, MAIN_WINDOW, "x", -1),
    mainWindowY(*this, MAIN_WINDOW, "y", -1),
    mainWindowW(*this, MAIN_WINDOW, "w", -1),
    mainWindowH(*this, MAIN_WINDOW, "h", -1),
    scriptEditorWindowX(*this, SCRIPT_EDITOR, "x", -1),
    scriptEditorWindowY(*this, SCRIPT_EDITOR, "y", -1),
    scriptEditorWindowW(*this, SCRIPT_EDITOR, "w", -1),
    scriptEditorWindowH(*this, SCRIPT_EDITOR, "h", -1),
    scriptEditorFontSize(*this, SCRIPT_EDITOR, "fontSize", -1),
    dimensionManagerWindowX(*this, DIMENSION_MANAGER, "x", -1),
    dimensionManagerWindowY(*this, DIMENSION_MANAGER, "y", -1),
    dimensionManagerWindowW(*this, DIMENSION_MANAGER, "w", -1),
    dimensionManagerWindowH(*this, DIMENSION_MANAGER, "h", -1),
    scriptSlotsWindowX(*this, SCRIPT_SLOTS, "x", -1),
    scriptSlotsWindowY(*this, SCRIPT_SLOTS, "y", -1),
    scriptSlotsWindowW(*this, SCRIPT_SLOTS, "w", -1),
    scriptSlotsWindowH(*this, SCRIPT_SLOTS, "h", -1),
    combineInstrumentsWindowX(*this, COMBINE_INSTRUMENTS, "x", -1),
    combineInstrumentsWindowY(*this, COMBINE_INSTRUMENTS, "y", -1),
    combineInstrumentsWindowW(*this, COMBINE_INSTRUMENTS, "w", -1),
    combineInstrumentsWindowH(*this, COMBINE_INSTRUMENTS, "h", -1),
    midiRulesWindowX(*this, MIDI_RULES, "x", -1),
    midiRulesWindowY(*this, MIDI_RULES, "y", -1),
    midiRulesWindowW(*this, MIDI_RULES, "w", -1),
    midiRulesWindowH(*this, MIDI_RULES, "h", -1),
    filePropsWindowX(*this, FILE_PROPS, "x", -1),
    filePropsWindowY(*this, FILE_PROPS, "y", -1),
    filePropsWindowW(*this, FILE_PROPS, "w", -1),
    filePropsWindowH(*this, FILE_PROPS, "h", -1),
    instrPropsWindowX(*this, INSTR_PROPS, "x", -1),
    instrPropsWindowY(*this, INSTR_PROPS, "y", -1),
    instrPropsWindowW(*this, INSTR_PROPS, "w", -1),
    instrPropsWindowH(*this, INSTR_PROPS, "h", -1),
    sampleRefsWindowX(*this, SAMPLE_REFS, "x", -1),
    sampleRefsWindowY(*this, SAMPLE_REFS, "y", -1),
    sampleRefsWindowW(*this, SAMPLE_REFS, "w", -1),
    sampleRefsWindowH(*this, SAMPLE_REFS, "h", -1),
    m_ignoreNotifies(false)
{
    m_boolProps.push_back(&warnUserOnExtensions);
    m_boolProps.push_back(&syncSamplerInstrumentSelection);
    m_boolProps.push_back(&moveRootNoteWithRegionMoved);
    m_boolProps.push_back(&autoRestoreWindowDimension);
    m_intProps.push_back(&mainWindowX);
    m_intProps.push_back(&mainWindowY);
    m_intProps.push_back(&mainWindowW);
    m_intProps.push_back(&mainWindowH);
    m_intProps.push_back(&scriptEditorWindowX);
    m_intProps.push_back(&scriptEditorWindowY);
    m_intProps.push_back(&scriptEditorWindowW);
    m_intProps.push_back(&scriptEditorWindowH);
    m_intProps.push_back(&scriptEditorFontSize);
    m_intProps.push_back(&dimensionManagerWindowX);
    m_intProps.push_back(&dimensionManagerWindowY);
    m_intProps.push_back(&dimensionManagerWindowW);
    m_intProps.push_back(&dimensionManagerWindowH);
    m_intProps.push_back(&scriptSlotsWindowX);
    m_intProps.push_back(&scriptSlotsWindowY);
    m_intProps.push_back(&scriptSlotsWindowW);
    m_intProps.push_back(&scriptSlotsWindowH);
    m_intProps.push_back(&combineInstrumentsWindowX);
    m_intProps.push_back(&combineInstrumentsWindowY);
    m_intProps.push_back(&combineInstrumentsWindowW);
    m_intProps.push_back(&combineInstrumentsWindowH);
    m_intProps.push_back(&midiRulesWindowX);
    m_intProps.push_back(&midiRulesWindowY);
    m_intProps.push_back(&midiRulesWindowW);
    m_intProps.push_back(&midiRulesWindowH);
    m_intProps.push_back(&filePropsWindowX);
    m_intProps.push_back(&filePropsWindowY);
    m_intProps.push_back(&filePropsWindowW);
    m_intProps.push_back(&filePropsWindowH);
    m_intProps.push_back(&instrPropsWindowX);
    m_intProps.push_back(&instrPropsWindowY);
    m_intProps.push_back(&instrPropsWindowW);
    m_intProps.push_back(&instrPropsWindowH);
    m_intProps.push_back(&sampleRefsWindowX);
    m_intProps.push_back(&sampleRefsWindowY);
    m_intProps.push_back(&sampleRefsWindowW);
    m_intProps.push_back(&sampleRefsWindowH);
}

void Settings::onPropertyChanged(Glib::PropertyBase* pProperty, RawValueType_t type, Group_t group) {
    if (m_ignoreNotifies) return;

    //printf("Settings::onPropertyChanged(%s)\n", pProperty->get_name().c_str());

    Glib::KeyFile file;
    try {
        bool ok = file.load_from_file(configFile());
        if (!ok) {
            std::cerr << "Could not load '" << configFile() << "'\n" << std::flush;
        }
    } catch (...) {
        std::cerr << "Could not load '" << configFile() << "'\n" << std::flush;
    }

    switch (type) {
        case BOOLEAN: {
            Property<bool>* prop = static_cast<Property<bool>*>(pProperty);
            //std::cout << "Saving bool setting '" << prop->get_name() << "'\n" << std::flush;
            file.set_boolean(groupName(prop->group()), prop->get_name(), prop->get_value());
            break;
        }
        case INTEGER: {
            Property<int>* prop = static_cast<Property<int>*>(pProperty);
            //std::cout << "Saving int setting '" << prop->get_name() << "'\n" << std::flush;
            file.set_integer(groupName(prop->group()), prop->get_name(), prop->get_value());
            break;
        }
        case UNKNOWN:
            std::cerr << "BUG: Unknown setting raw type of property '" << pProperty->get_name() << "'\n" << std::flush;
            return;
    }

    try {
#if HAS_GLIB_KEYFILE_SAVE_TO_FILE
        bool ok = file.save_to_file(configFile());
#else
        bool ok = saveToFile(&file, configFile());
#endif
        if (!ok) {
            std::cerr << "Failed saving gigedit config to '" << configFile() << "'\n" << std::flush;
        } else {
            //std::cout <<"gigedit CONFIG SAVED\n";
        }
    } catch (...) {
        std::cerr << "Failed saving gigedit config to '" << configFile() << "'\n" << std::flush;
    }
}

void Settings::load() {
    Glib::KeyFile file;
    try {
        bool ok = file.load_from_file(configFile());
        if (!ok) return;
    } catch (...) {
        std::cerr << "Could not load gigedit config file '" << configFile() << "'\n" << std::flush;
        return;
    }

    // ignore onPropertyChanged() calls during updating the property values below
    m_ignoreNotifies = true;

    for (int i = 0; i < m_boolProps.size(); ++i) {
        Property<bool>* prop = static_cast<Property<bool>*>(m_boolProps[i]);
        try {
            const std::string group = groupName(prop->group());
            if (!file.has_key(group, prop->get_name())) continue;
            const bool value = file.get_boolean(group, prop->get_name());
            prop->set_value(value);
        } catch (...) {
            continue;
        }
    }

    for (int i = 0; i < m_intProps.size(); ++i) {
        Property<int>* prop = static_cast<Property<int>*>(m_intProps[i]);
        try {
            const std::string group = groupName(prop->group());
            if (!file.has_key(group, prop->get_name())) continue;
            const int value = file.get_integer(group, prop->get_name());
            prop->set_value(value);
        } catch (...) {
            continue;
        }
    }

    m_ignoreNotifies = false;
}

