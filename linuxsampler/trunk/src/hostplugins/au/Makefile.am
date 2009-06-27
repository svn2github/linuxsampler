if HAVE_AU

plugindir = $(libdir)/au
examples_dir = /Developer/Examples
au_public_dir = $(examples_dir)/CoreAudio/AudioUnits/AUPublic
ca_public_dir = $(examples_dir)/CoreAudio/PublicUtility
INCLUDES = -I$(au_public_dir)/AUBase -I$(au_public_dir)/OtherBases \
    -I$(au_public_dir)/Utility -I$(ca_public_dir) $(GIG_CFLAGS) $(SQLITE3_CFLAGS)

noinst_LIBRARIES = libpluginau.a

# Uncomment for debug messages.
#debug_messages = -DAU_DEBUG_DISPATCHER=1

libpluginau_a_CXXFLAGS = $(debug_messages)

nodist_libpluginau_a_SOURCES = $(ca_public_dir)/CAHostTimeBase.cpp \
    $(ca_public_dir)/CAHostTimeBase.h \
    $(ca_public_dir)/CAAUMIDIMap.cpp \
    $(ca_public_dir)/CAAUMIDIMap.h \
    $(ca_public_dir)/CAAUMIDIMapManager.cpp \
    $(ca_public_dir)/CAAUMIDIMapManager.h \
    $(ca_public_dir)/CAAUParameter.cpp \
    $(ca_public_dir)/CAAUParameter.h \
    $(ca_public_dir)/CAAudioChannelLayout.cpp \
    $(ca_public_dir)/CAAudioChannelLayout.h \
    $(ca_public_dir)/CAMutex.cpp \
    $(ca_public_dir)/CAMutex.h \
    $(ca_public_dir)/CAStreamBasicDescription.cpp \
    $(ca_public_dir)/CAStreamBasicDescription.h \
    $(ca_public_dir)/CAVectorUnitTypes.h \
    $(ca_public_dir)/CAVectorUnit.cpp \
    $(ca_public_dir)/CAVectorUnit.h \
    $(au_public_dir)/Utility/AUBuffer.cpp \
    $(au_public_dir)/Utility/AUBuffer.h \
    $(au_public_dir)/Utility/AUDebugDispatcher.cpp \
    $(au_public_dir)/Utility/AUDebugDispatcher.h \
    $(au_public_dir)/Utility/AUInputFormatConverter.h \
    $(au_public_dir)/Utility/AUSilentTimeout.h \
    $(au_public_dir)/Utility/AUTimestampGenerator.h \
    $(au_public_dir)/AUBase/AUBase.cpp \
    $(au_public_dir)/AUBase/AUBase.h \
    $(au_public_dir)/AUBase/AUDispatch.cpp \
    $(au_public_dir)/AUBase/AUDispatch.h \
    $(au_public_dir)/AUBase/AUInputElement.cpp \
    $(au_public_dir)/AUBase/AUInputElement.h \
    $(au_public_dir)/AUBase/AUOutputElement.cpp \
    $(au_public_dir)/AUBase/AUOutputElement.h \
    $(au_public_dir)/AUBase/AUScopeElement.cpp \
    $(au_public_dir)/AUBase/AUScopeElement.h \
    $(au_public_dir)/AUBase/ComponentBase.cpp \
    $(au_public_dir)/AUBase/ComponentBase.h \
    $(au_public_dir)/OtherBases/AUMIDIBase.cpp \
    $(au_public_dir)/OtherBases/AUMIDIBase.h \
    $(au_public_dir)/OtherBases/MusicDeviceBase.cpp \
    $(au_public_dir)/OtherBases/MusicDeviceBase.h

bin_PROGRAMS = LinuxSamplerAU
LinuxSamplerAU_SOURCES = PluginAU.cpp

LinuxSamplerAU_LDADD = $(top_builddir)/src/.libs/liblinuxsampler.a libpluginau.a

if HAVE_AUFLAGS
else
AUFLAGS = $(GIG_LIBS) $(JACK_LIBS) $(SQLITE3_LIBS)
endif

LinuxSamplerAU_CXXFLAGS = -bundle $(debug_messages)
LinuxSamplerAU_LDFLAGS = -static $(AUFLAGS) \
    -exported_symbols_list PluginAU.exp \
    -framework CoreServices -framework CoreMIDI -framework CoreAudio \
    -framework CoreFoundation -framework AudioToolbox -framework AudioUnit

COMPONENT_DIR = LinuxSamplerAU.component

all-local:
	Rez PluginAU.r -d SystemSevenOrLater=1 -useDF -script Roman -d ppc_YES -d i386_YES -d x86_64_YES \
	    -I /System/Library/Frameworks/CoreServices.framework/Frameworks/CarbonCore.framework/Versions/Current/Headers \
	    -I $(au_public_dir)/AUBase/ -arch i386 -arch x86_64 -arch ppc -o LinuxSamplerAU.rsrc

	if test ! -d "$(COMPONENT_DIR)/Contents/Frameworks"; then mkdir -p "$(COMPONENT_DIR)/Contents/Frameworks"; fi
	if test ! -d "$(COMPONENT_DIR)/Contents/MacOS"; then mkdir -p "$(COMPONENT_DIR)/Contents/MacOS"; fi
	if test ! -d "$(COMPONENT_DIR)/Contents/Resources"; then mkdir -p "$(COMPONENT_DIR)/Contents/Resources"; fi

	cp PkgInfo "$(COMPONENT_DIR)/Contents"
	cp Info.plist "$(COMPONENT_DIR)/Contents"
	cp LinuxSamplerAU "$(COMPONENT_DIR)/Contents/MacOS"
	cp LinuxSamplerAU.rsrc "$(COMPONENT_DIR)/Contents/Resources"

#	    cp "`pkg-config --variable=libdir gig`/libgig.6.dylib" "$(COMPONENT_DIR)/Contents/Frameworks/"; \
#	    install_name_tool -id @executable_path/../Frameworks/libgig.6.dylib \
#	        "$(COMPONENT_DIR)/Contents/Frameworks/libgig.6.dylib"; \
#	    install_name_tool -change "`pkg-config --variable=libdir gig`/libgig.6.dylib" \
#	        @executable_path/../Frameworks/libgig.6.dylib \
#	        "$(COMPONENT_DIR)/Contents/MacOS/LinuxSamplerAU"
#
#if HAVE_SQLITE3
#	    cp "`pkg-config --variable=libdir sqlite3`/libsqlite3.dylib" "$(COMPONENT_DIR)/Contents/Frameworks/"; \
#	    install_name_tool -id @executable_path/../Frameworks/libsqlite3.dylib \; \
#	        "$(COMPONENT_DIR)/Contents/Frameworks/libsqlite3.dylib"; \
#	    install_name_tool -change "`pkg-config --variable=libdir sqlite3`/libsqlite3.dylib" \
#	        @executable_path/../Frameworks/libsqlite3.dylib \
#	        "$(COMPONENT_DIR)/Contents/MacOS/LinuxSamplerAU"
#endif
#
#if HAVE_JACK
#	    cp "`pkg-config --variable=libdir jack`/libjack.dylib" "$(COMPONENT_DIR)/Contents/Frameworks/"; \
#	    install_name_tool -id @executable_path/../Frameworks/libjack.dylib \
#	        "$(COMPONENT_DIR)/Contents/Frameworks/libjack.dylib"; \
#	    install_name_tool -change "`pkg-config --variable=libdir jack`/libjack.dylib" \
#	        @executable_path/../Frameworks/libjack.dylib \
#	        "$(COMPONENT_DIR)/Contents/MacOS/LinuxSamplerAU"
#endif

clean-local:
	rm -f LinuxSamplerAU.rsrc
	rm -rf $(COMPONENT_DIR)

install-exec-hook:
	cp -r $(COMPONENT_DIR) /Library/Audio/Plug-Ins/Components/
uninstall-hook:
	rm -rf /Library/Audio/Plug-Ins/Components/$(COMPONENT_DIR)
endif
