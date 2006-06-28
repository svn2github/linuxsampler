INCLUDES = $(all_includes)
METASOURCES = AUTO

AM_CXXFLAGS = -Wreturn-type -ffast-math $(CXX_CPU_SWITCH)

liblinuxsamplerdriversincludedir = $(includedir)/linuxsampler/drivers
liblinuxsamplerdriversinclude_HEADERS = \
	Device.h \
	DeviceParameter.h

noinst_LTLIBRARIES = liblinuxsamplerdrivers.la
liblinuxsamplerdrivers_la_SOURCES = DeviceParameter.cpp DeviceParameter.h Device.h DeviceParameterFactory.cpp DeviceParameterFactory.h
liblinuxsamplerdrivers_la_LDFLAGS =
#liblinuxsamplerdrivers_la_DEPENDENCIES =
liblinuxsamplerdrivers_la_LIBADD =
SUBDIRS = audio midi
