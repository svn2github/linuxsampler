INCLUDES = $(all_includes)
METASOURCES = AUTO

AM_CXXFLAGS = -Wreturn-type -ffast-math $(CXX_CPU_SWITCH)

liblinuxsamplercommonincludedir = $(includedir)/linuxsampler/common
liblinuxsamplercommoninclude_HEADERS = \
	atomic.h \
	Exception.h \
	global.h \
	optional.h \
	Mutex.h \
	SynchronizedConfig.h

noinst_LTLIBRARIES = liblinuxsamplercommon.la
liblinuxsamplercommon_la_SOURCES = \
	ArrayList.h \
	Condition.cpp Condition.h \
	ConditionServer.cpp ConditionServer.h \
	Features.cpp Features.h \
	global.cpp \
	Mutex.cpp \
	optional.cpp \
	Pool.h \
	ResourceManager.h \
	RingBuffer.h \
	RTMath.cpp RTMath.h \
	stacktrace.c stacktrace.h \
	Thread.cpp Thread.h
