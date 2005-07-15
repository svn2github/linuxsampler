INCLUDES = $(all_includes)
METASOURCES = AUTO

AM_CXXFLAGS = -Wreturn-type -ffast-math $(CXX_CPU_SWITCH)

noinst_LTLIBRARIES = liblinuxsamplercommon.la
liblinuxsamplercommon_la_SOURCES = \
	ArrayList.h \
	atomic.h \
	Condition.cpp Condition.h \
	ConditionServer.cpp ConditionServer.h \
	Features.cpp Features.h \
	global.h \
	LinuxSamplerException.h \
	Mutex.cpp Mutex.h \
	optional.cpp optional.h \
	Pool.h \
	ResourceManager.h \
	RingBuffer.h \
	RTMath.cpp RTMath.h \
	stacktrace.c stacktrace.h \
	Thread.cpp Thread.h
