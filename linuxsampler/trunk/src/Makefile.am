# set the include path found by configure
INCLUDES= $(all_includes)

# to prevent compile errors on some systems
AM_CXXFLAGS = -pedantic

SUBDIRS = network engines common audiodriver mididriver lib

pkglib_LTLIBRARIES = liblinuxsampler.la


liblinuxsampler_la_SOURCES = Sampler.cpp Sampler.h

bin_PROGRAMS = linuxsampler
linuxsampler_SOURCES = linuxsampler.cpp
linuxsampler_LDADD = $(top_builddir)/src/liblinuxsampler.la $(top_builddir)/src/common/liblinuxsamplercommon.a $(top_builddir)/src/mididriver/liblinuxsamplermididriver.a $(top_builddir)/src/audiodriver/liblinuxsampleraudiodriver.a $(top_builddir)/src/engines/common/liblinuxsamplercommonengine.a $(top_builddir)/src/engines/gig/liblinuxsamplergigengine.a $(top_builddir)/src/network/liblinuxsamplernetwork.a $(top_builddir)/src/lib/fileloader/libgig/libgig.la -lasound
linuxsampler_DEPENDENCIES = $(JACK_LIBS)
liblinuxsampler_la_LIBADD = $(top_builddir)/src/network/liblinuxsamplernetwork.a $(top_builddir)/src/mididriver/liblinuxsamplermididriver.a $(top_builddir)/src/lib/fileloader/libgig/libgig.la $(top_builddir)/src/engines/gig/liblinuxsamplergigengine.a $(top_builddir)/src/engines/common/liblinuxsamplercommonengine.a $(top_builddir)/src/common/liblinuxsamplercommon.a $(top_builddir)/src/audiodriver/liblinuxsampleraudiodriver.a -lasound
liblinuxsampler_la_DEPENDENCIES = $(JACK_LIBS)
liblinuxsampler_la_LDFLAGS = $(JACK_LIBS)
