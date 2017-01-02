// qsampler.cpp
//
/****************************************************************************
   Copyright (C) 2004-2017, rncbc aka Rui Nuno Capela. All rights reserved.
   Copyright (C) 2007,2008,2015 Christian Schoenebeck

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
#include <QLibraryInfo>
#include <QTranslator>
#include <QLocale>

#if defined(__APPLE__)  // Toshi Nagata 20080105
#include <QDir>
#endif

#ifndef CONFIG_PREFIX
#define CONFIG_PREFIX	"/usr/local"
#endif

#ifndef CONFIG_DATADIR
#define CONFIG_DATADIR	CONFIG_PREFIX "/share"
#endif

#if WIN32
#define RELATIVE_LOCALE_DIR "/share/locale"
#elif defined(__APPLE__)
#define RELATIVE_LOCALE_DIR "/../Resources"
#endif


//-------------------------------------------------------------------------
// Singleton application instance stuff (Qt/X11 only atm.)
//

#if QT_VERSION < 0x050000
#if defined(Q_WS_X11)
#define CONFIG_X11
#endif
#else
#if defined(QT_X11EXTRAS_LIB)
#define CONFIG_X11
#endif
#endif


#ifdef CONFIG_X11
#ifdef CONFIG_XUNIQUE

#include <QX11Info>

#include <X11/Xatom.h>
#include <X11/Xlib.h>

#define QSAMPLER_XUNIQUE "qsamplerApplication"

#if QT_VERSION >= 0x050100

#include <xcb/xcb.h>
#include <xcb/xproto.h>

#include <QAbstractNativeEventFilter>

class qsamplerApplication;

class qsamplerXcbEventFilter : public QAbstractNativeEventFilter
{
public:

	// Constructor.
	qsamplerXcbEventFilter(qsamplerApplication *pApp)
		: QAbstractNativeEventFilter(), m_pApp(pApp) {}

	// XCB event filter (virtual processor).
	bool nativeEventFilter(const QByteArray& eventType, void *message, long *);

private:

	// Instance variable.
	qsamplerApplication *m_pApp;
};

#endif

#endif	// CONFIG_XUNIQUE
#endif	// CONFIG_X11


class qsamplerApplication : public QApplication
{
public:

	// Constructor.
	qsamplerApplication(int& argc, char **argv) : QApplication(argc, argv),
		m_pQtTranslator(0), m_pMyTranslator(0), m_pWidget(0)
	{
		// Load translation support.
		QLocale loc;
		if (loc.language() != QLocale::C) {
			// Try own Qt translation...
			m_pQtTranslator = new QTranslator(this);
			QString sLocName = "qt_" + loc.name();
			QString sLocPath = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
			if (m_pQtTranslator->load(sLocName, sLocPath)) {
				QApplication::installTranslator(m_pQtTranslator);
			} else {
			#ifdef RELATIVE_LOCALE_DIR
				sLocPath = QApplication::applicationDirPath() + RELATIVE_LOCALE_DIR;
				if (m_pQtTranslator->load(sLocName, sLocPath)) {
					QApplication::installTranslator(m_pQtTranslator);
				} else {
			#endif
				delete m_pQtTranslator;
				m_pQtTranslator = 0;
			#ifdef CONFIG_DEBUG
				qWarning("Warning: no translation found for '%s' locale: %s/%s.qm",
					loc.name().toUtf8().constData(),
					sLocPath.toUtf8().constData(),
					sLocName.toUtf8().constData());
			#endif
			#ifdef RELATIVE_LOCALE_DIR
				}
			#endif
			}
			// Try own application translation...
			m_pMyTranslator = new QTranslator(this);
			sLocName = "qsampler_" + loc.name();
			if (m_pMyTranslator->load(sLocName, sLocPath)) {
				QApplication::installTranslator(m_pMyTranslator);
			} else {
			#ifdef RELATIVE_LOCALE_DIR
				sLocPath = QApplication::applicationDirPath() + RELATIVE_LOCALE_DIR;
			#else
				sLocPath = CONFIG_DATADIR "/qsampler/translations";
			#endif
				if (m_pMyTranslator->load(sLocName, sLocPath)) {
					QApplication::installTranslator(m_pMyTranslator);
				} else {
					delete m_pMyTranslator;
					m_pMyTranslator = 0;
				#ifdef CONFIG_DEBUG
					qWarning("Warning: no translation found for '%s' locale: %s/%s.qm",
						loc.name().toUtf8().constData(),
						sLocPath.toUtf8().constData(),
						sLocName.toUtf8().constData());
				#endif
				}
			}
		}
	#ifdef CONFIG_X11
	#ifdef CONFIG_XUNIQUE
 		// Instance uniqueness initialization...
		m_pDisplay = QX11Info::display();
		m_aUnique  = XInternAtom(m_pDisplay, QSAMPLER_XUNIQUE, false);
		XGrabServer(m_pDisplay);
		m_wOwner = XGetSelectionOwner(m_pDisplay, m_aUnique);
		XUngrabServer(m_pDisplay);
	#if QT_VERSION >= 0x050100
		m_pXcbEventFilter = new qsamplerXcbEventFilter(this);
		installNativeEventFilter(m_pXcbEventFilter);
	#endif
	#endif	// CONFIG_XUNIQUE
	#endif	// CONFIG_X11
	}

	// Destructor.
	~qsamplerApplication()
	{
	#ifdef CONFIG_X11
	#ifdef CONFIG_XUNIQUE
	#if QT_VERSION >= 0x050100
		removeNativeEventFilter(m_pXcbEventFilter);
		delete m_pXcbEventFilter;
	#endif
	#endif	// CONFIG_XUNIQUE
	#endif	// CONFIG_X11
		if (m_pMyTranslator) delete m_pMyTranslator;
		if (m_pQtTranslator) delete m_pQtTranslator;
	}

	// Main application widget accessors.
	void setMainWidget(QWidget *pWidget)
	{
		m_pWidget = pWidget;
	#ifdef CONFIG_X11
	#ifdef CONFIG_XUNIQUE
		m_wOwner = m_pWidget->winId();
		if (m_pDisplay && m_wOwner) {
			XGrabServer(m_pDisplay);
			XSetSelectionOwner(m_pDisplay, m_aUnique, m_wOwner, CurrentTime);
			XUngrabServer(m_pDisplay);
		}
	#endif	// CONFIG_XUNIQUE
	#endif	// CONFIG_X11
	}

	QWidget *mainWidget() const { return m_pWidget; }

	// Check if another instance is running,
    // and raise its proper main widget...
	bool setup()
	{
	#ifdef CONFIG_X11
	#ifdef CONFIG_XUNIQUE
		if (m_pDisplay && m_wOwner != None) {
			// First, notify any freedesktop.org WM
			// that we're about to show the main widget...
			Screen *pScreen = XDefaultScreenOfDisplay(m_pDisplay);
			int iScreen = XScreenNumberOfScreen(pScreen);
			XEvent ev;
			memset(&ev, 0, sizeof(ev));
			ev.xclient.type = ClientMessage;
			ev.xclient.display = m_pDisplay;
			ev.xclient.window = m_wOwner;
			ev.xclient.message_type = XInternAtom(m_pDisplay, "_NET_ACTIVE_WINDOW", false);
			ev.xclient.format = 32;
			ev.xclient.data.l[0] = 0; // Source indication.
			ev.xclient.data.l[1] = 0; // Timestamp.
			ev.xclient.data.l[2] = 0; // Requestor's currently active window (none)
			ev.xclient.data.l[3] = 0;
			ev.xclient.data.l[4] = 0;
			XSelectInput(m_pDisplay, m_wOwner, StructureNotifyMask);
			XSendEvent(m_pDisplay, RootWindow(m_pDisplay, iScreen), false,
				(SubstructureNotifyMask | SubstructureRedirectMask), &ev);
			XSync(m_pDisplay, false);
			XRaiseWindow(m_pDisplay, m_wOwner);
			// And then, let it get caught on destination
			// by QApplication::native/x11EventFilter...
			const QByteArray value = QSAMPLER_XUNIQUE;
			XChangeProperty(
				m_pDisplay,
				m_wOwner,
				m_aUnique,
				m_aUnique, 8,
				PropModeReplace,
				(unsigned char *) value.data(),
				value.length());
			// Done.
			return true;
		}
	#endif	// CONFIG_XUNIQUE
	#endif	// CONFIG_X11
		return false;
	}

#ifdef CONFIG_X11
#ifdef CONFIG_XUNIQUE
	void x11PropertyNotify(Window w)
	{
		if (m_pDisplay && m_pWidget && m_wOwner == w) {
			// Always check whether our property-flag is still around...
			Atom aType;
			int iFormat = 0;
			unsigned long iItems = 0;
			unsigned long iAfter = 0;
			unsigned char *pData = 0;
			if (XGetWindowProperty(
					m_pDisplay,
					m_wOwner,
					m_aUnique,
					0, 1024,
					false,
					m_aUnique,
					&aType,
					&iFormat,
					&iItems,
					&iAfter,
					&pData) == Success
				&& aType == m_aUnique && iItems > 0 && iAfter == 0) {
				// Avoid repeating it-self...
				XDeleteProperty(m_pDisplay, m_wOwner, m_aUnique);
				// Just make it always shows up fine...
				m_pWidget->show();
				m_pWidget->raise();
				m_pWidget->activateWindow();
			}
			// Free any left-overs...
			if (iItems > 0 && pData)
				XFree(pData);
		}
	}
#if QT_VERSION < 0x050000
	bool x11EventFilter(XEvent *pEv)
	{
		if (pEv->type == PropertyNotify
			&& pEv->xproperty.state == PropertyNewValue)
			x11PropertyNotify(pEv->xproperty.window);
		return QApplication::x11EventFilter(pEv);
	}
#endif
#endif	// CONFIG_XUNIQUE
#endif	// CONFIG_X11
	
private:

	// Translation support.
	QTranslator *m_pQtTranslator;
	QTranslator *m_pMyTranslator;

	// Instance variables.
	QWidget *m_pWidget;

#ifdef CONFIG_X11
#ifdef CONFIG_XUNIQUE
	Display *m_pDisplay;
	Atom     m_aUnique;
	Window   m_wOwner;
#if QT_VERSION >= 0x050100
	qsamplerXcbEventFilter *m_pXcbEventFilter;
#endif
#endif	// CONFIG_XUNIQUE
#endif	// CONFIG_X11
};


#ifdef CONFIG_X11
#ifdef CONFIG_XUNIQUE
#if QT_VERSION >= 0x050100
// XCB Event filter (virtual processor).
bool qsamplerXcbEventFilter::nativeEventFilter (
	const QByteArray& eventType, void *message, long * )
{
	if (eventType == "xcb_generic_event_t") {
		xcb_property_notify_event_t *pEv
			= static_cast<xcb_property_notify_event_t *> (message);
		if ((pEv->response_type & ~0x80) == XCB_PROPERTY_NOTIFY
			&& pEv->state == XCB_PROPERTY_NEW_VALUE)
			m_pApp->x11PropertyNotify(pEv->window);
	}
	return false;
}
#endif
#endif	// CONFIG_XUNIQUE
#endif	// CONFIG_X11


//-------------------------------------------------------------------------
// stacktrace - Signal crash handler.
//

#ifdef CONFIG_STACKTRACE
#if defined(__GNUC__) && defined(Q_OS_LINUX)

#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void stacktrace ( int signo )
{
	pid_t pid;
	int rc;
	int status = 0;
	char cmd[80];

	// Reinstall default handler; prevent race conditions...
	signal(signo, SIG_DFL);

	static const char *shell  = "/bin/sh";
	static const char *format = "gdb -q --batch --pid=%d"
		" --eval-command='thread apply all bt'";

	snprintf(cmd, sizeof(cmd), format, (int) getpid());

	pid = fork();

	// Fork failure!
	if (pid < 0)
		return;

	// Fork child...
	if (pid == 0) {
		execl(shell, shell, "-c", cmd, NULL);
		_exit(1);
		return;
	}

	// Parent here: wait for child to terminate...
	do { rc = waitpid(pid, &status, 0); }
	while ((rc < 0) && (errno == EINTR));

	// Dispatch any logging, if any...
	QApplication::processEvents(QEventLoop::AllEvents, 3000);

	// Make sure everyone terminates...
	kill(pid, SIGTERM);
	_exit(1);
}

#endif
#endif


//-------------------------------------------------------------------------
// main - The main program trunk.
//

int main ( int argc, char **argv )
{
	Q_INIT_RESOURCE(qsampler);
#ifdef CONFIG_STACKTRACE
#if defined(__GNUC__) && defined(Q_OS_LINUX)
	signal(SIGILL,  stacktrace);
	signal(SIGFPE,  stacktrace);
	signal(SIGSEGV, stacktrace);
	signal(SIGABRT, stacktrace);
	signal(SIGBUS,  stacktrace);
#endif
#endif
	qsamplerApplication app(argc, argv);

	#if defined(__APPLE__)  //  Toshi Nagata 20080105
	{
		//  Set the plugin path to @exetutable_path/../plugins
		QDir dir(QApplication::applicationDirPath());
		dir.cdUp();  // "Contents" directory
		QApplication::setLibraryPaths(QStringList(dir.absolutePath() + "/plugins"));

		//  Set the PATH environment variable to include @executable_path/../../..
		dir.cdUp();
		dir.cdUp();
		QString path(getenv("PATH"));
		path = dir.absolutePath() + ":" + path;
		setenv("PATH", path.toUtf8().constData(), 1);
	}
	#endif

	// Construct default settings; override with command line arguments.
	QSampler::Options options;
	if (!options.parse_args(app.arguments())) {
		app.quit();
		return 1;
	}

	// Have another instance running?
	if (app.setup()) {
		app.quit();
		return 2;
	}

	// Dark themes grayed/disabled color group fix...
	QPalette pal(app.palette());
	if (pal.base().color().value() < 0x7f) {
	#if QT_VERSION >= 0x050000
		const QColor& color = pal.window().color();
		const int iGroups = int(QPalette::Active | QPalette::Inactive) + 1;
		for (int i = 0; i < iGroups; ++i) {
			const QPalette::ColorGroup group = QPalette::ColorGroup(i);
			pal.setBrush(group, QPalette::Light,    color.lighter(150));
			pal.setBrush(group, QPalette::Midlight, color.lighter(120));
			pal.setBrush(group, QPalette::Dark,     color.darker(150));
			pal.setBrush(group, QPalette::Mid,      color.darker(120));
			pal.setBrush(group, QPalette::Shadow,   color.darker(200));
		}
	//	pal.setColor(QPalette::Disabled, QPalette::ButtonText, pal.mid().color());
	#endif
		pal.setColorGroup(QPalette::Disabled,
			pal.windowText().color().darker(),
			pal.button(),
			pal.light(),
			pal.dark(),
			pal.mid(),
			pal.text().color().darker(),
			pal.text().color().lighter(),
			pal.base(),
			pal.window());
		app.setPalette(pal);
	}

	// Set default base font...
	if (options.iBaseFontSize > 0)
		app.setFont(QFont(app.font().family(), options.iBaseFontSize));

	// Construct, setup and show the main form.
	QSampler::MainForm w;
	w.setup(&options);
	w.show();

	// Settle this one as application main widget...
	app.setMainWidget(&w);

	// Register the quit signal/slot.
	// app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));

	return app.exec();
}


// end of qsampler.cpp

