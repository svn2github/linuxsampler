if HAVE_VST

BUILT_SOURCES = vstsdk

clean-local: $(CLEAN_MAC)
	$(RM) -r vstsdk

# create links to vst sdk so make doesn't get confused by spaces in path
vstsdk:
	mkdir -p vstsdk/pluginterfaces vstsdk/public.sdk/source
	ln -s "$(VSTSDK_DIR)"/pluginterfaces/vst2.x vstsdk/pluginterfaces/vst2.x
	ln -s "$(VSTSDK_DIR)"/public.sdk/source/vst2.x vstsdk/public.sdk/source

plugindir = $(libdir)/vst
plugin_LTLIBRARIES = LinuxSampler.la
LinuxSampler_la_CPPFLAGS = -Ivstsdk -Ivstsdk/public.sdk/source/vst2.x \
	$(GIG_CFLAGS) $(SQLITE3_CFLAGS)

LinuxSampler_la_SOURCES = PluginVst.cpp PluginVst.h
nodist_LinuxSampler_la_SOURCES = \
	vstsdk/public.sdk/source/vst2.x/audioeffectx.cpp \
	vstsdk/public.sdk/source/vst2.x/audioeffect.cpp \
	vstsdk/public.sdk/source/vst2.x/vstplugmain.cpp

LinuxSampler_la_LDFLAGS = -module -avoid-version -no-undefined
LinuxSampler_la_LIBADD = $(top_builddir)/src/liblinuxsampler.la

if HAVE_WINDOWS
LinuxSampler_la_LDFLAGS += -Wl,$(srcdir)/PluginVst.def -Wl,-s
LinuxSampler_la_LIBADD += -lws2_32
else
LinuxSampler_la_CPPFLAGS += -D__cdecl= -DDATADIR=\""$(datadir)"\"
if LINUX
LinuxSampler_la_LDFLAGS += -Wl,--defsym -Wl,main=VSTPluginMain -Wl,-s
endif
endif

if MAC
all-local: LinuxSampler.vst

LinuxSampler.vst: LinuxSampler.la $(srcdir)/Info.plist $(srcdir)/PkgInfo
	mkdir -p LinuxSampler.vst/Contents/MacOS
	cp $(srcdir)/Info.plist LinuxSampler.vst/Contents
	cp $(srcdir)/PkgInfo LinuxSampler.vst/Contents
	if test -f .libs/LinuxSampler.so ; then cp .libs/LinuxSampler.so LinuxSampler.vst/Contents/MacOS/LinuxSampler ; fi
	@touch $@

CLEAN_MAC = clean-bundle

clean-bundle:
	rm -rf LinuxSampler.vst

install-exec-hook:
	if mkdir -p $(MAC_PLUGIN_INSTALL_DIR)/VST && \
	test -w $(MAC_PLUGIN_INSTALL_DIR)/VST ; then \
	cp -r LinuxSampler.vst $(MAC_PLUGIN_INSTALL_DIR)/VST/ ; \
	if test -n "$(INSTALL_STRIP_FLAG)" ; then $(STRIP) -x $(MAC_PLUGIN_INSTALL_DIR)/VST/LinuxSampler.vst/Contents/MacOS/LinuxSampler ; fi ; fi

uninstall-hook:
	rm -rf $(MAC_PLUGIN_INSTALL_DIR)/VST/LinuxSampler.vst
endif

endif

EXTRA_DIST = PluginVst.def PkgInfo Info.plist
