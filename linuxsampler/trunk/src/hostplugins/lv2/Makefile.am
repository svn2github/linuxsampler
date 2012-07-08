if HAVE_LV2
INCLUDES = $(LV2_CFLAGS) $(GIG_CFLAGS) $(SQLITE3_CFLAGS)
plugindir = $(libdir)/lv2/linuxsampler.lv2
plugin_LTLIBRARIES = linuxsampler.la
plugin_DATA = manifest.ttl linuxsampler.ttl

linuxsampler_la_SOURCES = PluginLv2.cpp PluginLv2.h
linuxsampler_la_LDFLAGS = -module -avoid-version
linuxsampler_la_LIBADD = $(top_builddir)/src/liblinuxsampler.la
endif

EXTRA_DIST = $(plugin_DATA)
