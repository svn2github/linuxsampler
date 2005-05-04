# set the include path found by configure
INCLUDES= $(all_includes)

AM_CXXFLAGS = -Wreturn-type -ffast-math $(CXX_CPU_SWITCH)

SUBDIRS = network engines common lib testcases drivers

pkglib_LTLIBRARIES = liblinuxsampler.la
liblinuxsampler_la_SOURCES = Sampler.cpp Sampler.h
liblinuxsampler_la_LIBADD = \
	$(top_builddir)/src/network/liblinuxsamplernetwork.la \
	$(top_builddir)/src/engines/gig/liblinuxsamplergigengine.la \
	$(top_builddir)/src/engines/common/liblinuxsamplercommonengine.la \
	$(top_builddir)/src/engines/liblinuxsamplerengines.la \
	$(top_builddir)/src/drivers/liblinuxsamplerdrivers.la \
	$(top_builddir)/src/drivers/audio/liblinuxsampleraudiodriver.la \
	$(top_builddir)/src/drivers/midi/liblinuxsamplermididriver.la \
	$(top_builddir)/src/common/liblinuxsamplercommon.la

bin_PROGRAMS = linuxsampler
linuxsampler_SOURCES = linuxsampler.cpp
linuxsampler_LDADD = $(top_builddir)/src/liblinuxsampler.la
