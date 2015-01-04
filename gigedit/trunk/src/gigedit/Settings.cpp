/*
    Copyright (c) 2014-2015 Christian Schoenebeck
    
    This file is part of "gigedit" and released under the terms of the
    GNU General Public License version 2.
*/

#include "Settings.h"

static Settings _instance;
    
Settings* Settings::singleton() {
    return &_instance;
}

Settings::Settings() {
    warnUserOnExtensions = true;
    syncSamplerInstrumentSelection = true;
}
