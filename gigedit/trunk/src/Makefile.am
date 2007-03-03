bin_PROGRAMS = gigedit
gigedit_SOURCES = main.cpp \
	mainwindow.cpp mainwindow.h \
	regionchooser.cpp regionchooser.h \
	dimregionchooser.cpp dimregionchooser.h

gigedit_LDADD = $(GTKMM_LIBS) $(GIG_LIBS)

AM_CPPFLAGS = $(GTKMM_CFLAGS) $(GIG_CFLAGS)
DEFS = -DLOCALEDIR=\"$(datadir)/locale\" @DEFS@
