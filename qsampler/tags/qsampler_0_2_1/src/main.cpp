// main.cpp
//
/****************************************************************************
   Copyright (C) 2004-2007, rncbc aka Rui Nuno Capela. All rights reserved.
   Copyright (C) 2007, Christian Schoenebeck

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*****************************************************************************/

#include "qsamplerAbout.h"
#include "qsamplerOptions.h"
#include "qsamplerMainForm.h"

#include <QApplication>
#include <QTranslator>
#include <QLocale>


//-------------------------------------------------------------------------
// main - The main program trunk.
//

int main ( int argc, char **argv )
{
	QApplication app(argc, argv);

	// Load translation support.
	QTranslator translator(0);
	QLocale loc;
	if (loc.language() != QLocale::C) {
		QString sLocName = "qsampler_" + loc.name();
		if (!translator.load(sLocName, ".")) {
			QString sLocPath = CONFIG_PREFIX "/share/locale";
			if (!translator.load(sLocName, sLocPath))
				fprintf(stderr, "Warning: no locale found: %s/%s.qm\n",
					sLocPath.toUtf8().constData(),
					sLocName.toUtf8().constData());
		}
		app.installTranslator(&translator);
	}

	// Construct default settings; override with command line arguments.
	QSampler::Options options;
	if (!options.parse_args(app.argc(), app.argv())) {
		app.quit();
		return 1;
	}

	// Construct, setup and show the main form.
	QSampler::MainForm w;
	w.setup(&options);
	w.show();

	// Register the quit signal/slot.
	// app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));

	return app.exec();
}


// end of main.cpp
