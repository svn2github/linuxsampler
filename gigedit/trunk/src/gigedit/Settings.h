/*
    Copyright (c) 2014-2015 Christian Schoenebeck
    
    This file is part of "gigedit" and released under the terms of the
    GNU General Public License version 2.
*/

#ifndef GIGEDIT_SETTINGS
#define GIGEDIT_SETTINGS

// Probably a bit overkill for only two settings (right now), but I saw
// originnaly no better place to put this, since warnUserOnExtensions needs to
// be accessed without a MainWindow instance.
struct Settings {
    bool warnUserOnExtensions; ///< if enabled, the user shall he be warned if he is trying to use a gig format extension that will not work with Gigasampler/GigaStudio
    bool syncSamplerInstrumentSelection; ///< if enabled, the sampler's current instrument will automatically be switched whenever another instrument was selected in gigedit
    
    static Settings* singleton();
    Settings();
};

#endif // GIGEDIT_SETTINGS
