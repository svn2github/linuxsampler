if HAVE_LINUXSAMPLER
optional_subdirs = plugin
else
optional_subdirs =
endif

SUBDIRS = $(optional_subdirs)

AM_CPPFLAGS = $(GTKMM_CFLAGS) $(GIG_CFLAGS)
DEFS = -DLOCALEDIR=\"$(datadir)/locale\" @DEFS@

pkglib_LTLIBRARIES = libgigedit.la
libgigedit_la_SOURCES = \
	gigedit.cpp gigedit.h \
	mainwindow.cpp mainwindow.h \
	regionchooser.cpp regionchooser.h \
	dimregionchooser.cpp dimregionchooser.h \
	dimregionedit.cpp dimregionedit.h \
	paramedit.cpp paramedit.h \
	dimensionmanager.cpp dimensionmanager.h
libgigedit_la_LIBADD = \
	$(GTKMM_LIBS) $(GIG_LIBS) $(SNDFILE_LIBS)
libgigedit_la_CXXFLAGS = \
	$(SNDFILE_CFLAGS)
libgigedit_la_LDFLAGS = \
	-version-info @SHARED_VERSION_INFO@ @SHLIB_VERSION_ARG@

bin_PROGRAMS = gigedit
gigedit_SOURCES = main.cpp
gigedit_LDADD = \
	$(top_builddir)/src/libgigedit.la
