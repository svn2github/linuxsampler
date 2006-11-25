INCLUDES = $(all_includes)
AM_CXXFLAGS = -Wreturn-type -ffast-math $(CXX_CPU_SWITCH)
METASOURCES = AUTO
SUBDIRS = gig common

liblinuxsamplerengineincludedir = $(includedir)/linuxsampler/engines
liblinuxsamplerengineinclude_HEADERS = \
	Engine.h \
	EngineChannel.h

noinst_LTLIBRARIES = liblinuxsamplerengines.la
liblinuxsamplerengines_la_SOURCES = \
	Engine.h \
	EngineChannel.cpp EngineChannel.h \
	EngineFactory.cpp EngineFactory.h \
	EngineChannelFactory.cpp EngineChannelFactory.h
