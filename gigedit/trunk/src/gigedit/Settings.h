/*
    Copyright (c) 2014 Christian Schoenebeck
    
    This file is part of "gigedit" and released under the terms of the
    GNU General Public License version 2.
*/

#ifndef GIGEDIT_SETTINGS
#define GIGEDIT_SETTINGS

// Probably a bit overkill for only one setting (right now), but I saw no better
// place to put this, since warnUserOnExtensions needs to be accessed without
// a MainWindow instance.
struct Settings {
    bool warnUserOnExtensions; ///< if enabled, the user shall he be warned if he is trying to use a gig format extension that will not work with Gigasampler/GigaStudio
    
    static Settings* singleton();
    Settings();
};

#endif // GIGEDIT_SETTINGS
