#TODO: retrieve plugin path from LS's pkg-config info
pkglibdir = /usr/lib/linuxsampler/plugins

pkglib_LTLIBRARIES = \
	libgigeditlinuxsamplerplugin.la
libgigeditlinuxsamplerplugin_la_SOURCES = \
	linuxsamplerplugin.cpp
libgigeditlinuxsamplerplugin_la_LIBADD = \
	$(top_builddir)/src/gigedit/libgigedit.la
libgigeditlinuxsamplerplugin_la_CXXFLAGS = \
	$(LINUXSAMPLER_CFLAGS)
libgigeditlinuxsamplerplugin_la_LDFLAGS = \
	-version-info @SHARED_VERSION_INFO@ @SHLIB_VERSION_ARG@ \
	$(LINUXSAMPLER_LIBS)
