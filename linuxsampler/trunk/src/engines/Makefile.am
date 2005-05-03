INCLUDES = $(all_includes)
AM_CXXFLAGS = -Wreturn-type -ffast-math -march=$(target_cpu)
METASOURCES = AUTO
SUBDIRS = gig common
noinst_LTLIBRARIES = liblinuxsamplerengines.la
noinst_HEADERS = EngineChannelFactory.h EngineFactory.h
liblinuxsamplerengines_la_SOURCES = EngineChannelFactory.cpp EngineFactory.cpp
