if HAVE_VST

plugindir = $(libdir)/vst
plugin_LTLIBRARIES = LinuxSampler.la
INCLUDES = -I@VSTSDK_DIR@ -I@VSTSDK_DIR@/public.sdk/source/vst2.x $(GIG_CFLAGS)

LinuxSampler_la_SOURCES = PluginVst.cpp PluginVst.h
nodist_LinuxSampler_la_SOURCES = \
	@VSTSDK_DIR@/public.sdk/source/vst2.x/audioeffectx.cpp \
	@VSTSDK_DIR@/public.sdk/source/vst2.x/audioeffect.cpp \
	@VSTSDK_DIR@/public.sdk/source/vst2.x/vstplugmain.cpp

LinuxSampler_la_LDFLAGS = -module -avoid-version -no-undefined -Wl,-s
LinuxSampler_la_LIBADD = $(top_builddir)/src/liblinuxsampler.la

EXTRA_DIST = PluginVst.def

if HAVE_WINDOWS
LinuxSampler_la_LDFLAGS += -Wl,PluginVst.def
LinuxSampler_la_LIBADD += -lws2_32
else
LinuxSampler_la_CPPFLAGS = -D__cdecl=
endif

endif
