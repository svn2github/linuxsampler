# set the include path found by configure
INCLUDES= $(all_includes)

# to prevent compile errors on some systems
AM_CXXFLAGS = -pedantic

SUBDIRS = network engines common audiodriver mididriver lib testcases

pkglib_LTLIBRARIES = liblinuxsampler.la
liblinuxsampler_la_SOURCES = Sampler.cpp Sampler.h
liblinuxsampler_la_LIBADD = $(top_builddir)/src/network/liblinuxsamplernetwork.la $(top_builddir)/src/mididriver/liblinuxsamplermididriver.la $(top_builddir)/src/lib/fileloader/libgig/libgig.la $(top_builddir)/src/engines/gig/liblinuxsamplergigengine.la $(top_builddir)/src/engines/common/liblinuxsamplercommonengine.la $(top_builddir)/src/common/liblinuxsamplercommon.la $(top_builddir)/src/audiodriver/liblinuxsampleraudiodriver.la
liblinuxsampler_la_LDFLAGS = -module

bin_PROGRAMS = linuxsampler
linuxsampler_SOURCES = linuxsampler.cpp
linuxsampler_LDADD = $(top_builddir)/src/liblinuxsampler.la
