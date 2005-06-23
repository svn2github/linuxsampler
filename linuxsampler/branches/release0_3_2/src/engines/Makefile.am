INCLUDES = $(all_includes)
AM_CXXFLAGS = -Wreturn-type -ffast-math $(CXX_CPU_SWITCH)
METASOURCES = AUTO
SUBDIRS = gig common
noinst_LTLIBRARIES = liblinuxsamplerengines.la
liblinuxsamplerengines_la_SOURCES = \
	EngineFactory.cpp EngineFactory.h \
	EngineChannelFactory.cpp EngineChannelFactory.h
