INCLUDES = $(all_includes)
METASOURCES = AUTO

AM_CXXFLAGS = -ffast-math -march=$(target_cpu) -mcpu=$(target_cpu)

noinst_LTLIBRARIES = liblinuxsamplercommon.la
liblinuxsamplercommon_la_SOURCES = atomic.h Condition.cpp Condition.h ConditionServer.cpp ConditionServer.h global.h LinuxSamplerException.h Mutex.cpp Mutex.h ResourceManager.h RingBuffer.h RTELMemoryPool.h RTMath.cpp RTMath.h Thread.cpp Thread.h optional.h optional.cpp stacktrace.c stacktrace.h Features.cpp
noinst_HEADERS =  Features.h
