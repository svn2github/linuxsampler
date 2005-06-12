INCLUDES = $(all_includes)
METASOURCES = AUTO

AM_CXXFLAGS = -Wreturn-type -ffast-math $(CXX_CPU_SWITCH)

noinst_LTLIBRARIES = liblinuxsamplercommon.la
liblinuxsamplercommon_la_SOURCES = atomic.h Condition.cpp Condition.h ConditionServer.cpp ConditionServer.h global.h LinuxSamplerException.h Mutex.cpp Mutex.h ResourceManager.h RingBuffer.h RTMath.cpp RTMath.h Thread.cpp Thread.h Pool.h optional.h optional.cpp stacktrace.c stacktrace.h Features.cpp
noinst_HEADERS = Features.h ArrayList.h
