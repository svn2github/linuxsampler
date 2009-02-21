# set the include path found by configure
INCLUDES= $(all_includes) $(GIG_CFLAGS)

if HAVE_COREMIDI
coremidi_ldflags = -framework CoreAudio \
	-framework CoreMIDI \
	-framework CoreServices \
	-framework AudioUnit
else
coremidi_ldflags =
endif

if HAVE_SQLITE3
sqlite3_lib = $(top_builddir)/src/db/liblinuxsamplerdb.la
else
sqlite3_lib =
endif

AM_CXXFLAGS = -Wreturn-type -ffast-math $(CXX_CPU_SWITCH)

SUBDIRS = db network engines common testcases drivers plugins effects . hostplugins

liblinuxsamplerincludedir = $(includedir)/linuxsampler
liblinuxsamplerinclude_HEADERS = Sampler.h EventListeners.h

pkglib_LTLIBRARIES = liblinuxsampler.la
liblinuxsampler_la_SOURCES = Sampler.cpp
liblinuxsampler_la_LIBADD = \
	$(sqlite3_lib) \
	$(top_builddir)/src/network/liblinuxsamplernetwork.la \
	$(top_builddir)/src/engines/gig/liblinuxsamplergigengine.la \
	$(top_builddir)/src/engines/common/liblinuxsamplercommonengine.la \
	$(top_builddir)/src/engines/liblinuxsamplerengines.la \
	$(top_builddir)/src/drivers/liblinuxsamplerdrivers.la \
	$(top_builddir)/src/drivers/audio/liblinuxsampleraudiodriver.la \
	$(top_builddir)/src/drivers/midi/liblinuxsamplermididriver.la \
	$(top_builddir)/src/plugins/liblinuxsamplerplugins.la \
	$(top_builddir)/src/effects/liblinuxsamplereffects.la \
	$(top_builddir)/src/common/liblinuxsamplercommon.la
liblinuxsampler_la_LDFLAGS = -version-info @SHARED_VERSION_INFO@ @SHLIB_VERSION_ARG@ -no-undefined

bin_PROGRAMS = linuxsampler
linuxsampler_SOURCES = linuxsampler.cpp
linuxsampler_LDADD = $(top_builddir)/src/liblinuxsampler.la
linuxsampler_LDFLAGS = $(coremidi_ldflags)
