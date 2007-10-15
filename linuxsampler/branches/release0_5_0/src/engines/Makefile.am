INCLUDES = $(all_includes)
AM_CXXFLAGS = -Wreturn-type -ffast-math $(CXX_CPU_SWITCH) -DCONFIG_PLUGIN_DIR=\"$(config_plugin_dir)\"
METASOURCES = AUTO
SUBDIRS = gig common

liblinuxsamplerengineincludedir = $(includedir)/linuxsampler/engines
liblinuxsamplerengineinclude_HEADERS = \
	Engine.h \
	EngineChannel.h \
	FxSend.h \
	InstrumentManager.h

noinst_LTLIBRARIES = liblinuxsamplerengines.la
liblinuxsamplerengines_la_SOURCES = \
	Engine.cpp Engine.h \
	EngineChannel.cpp EngineChannel.h \
	EngineFactory.cpp EngineFactory.h \
	EngineChannelFactory.cpp EngineChannelFactory.h \
	FxSend.cpp FxSend.h \
	InstrumentManager.cpp InstrumentManager.h \
	InstrumentManagerThread.cpp InstrumentManagerThread.h
