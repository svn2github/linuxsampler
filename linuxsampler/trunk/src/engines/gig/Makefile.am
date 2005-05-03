INCLUDES = $(all_includes)
METASOURCES = AUTO

AM_CXXFLAGS = -Wreturn-type -ffast-math

noinst_LTLIBRARIES = liblinuxsamplergigengine.la
liblinuxsamplergigengine_la_SOURCES = DiskThread.cpp DiskThread.h EGADSR.cpp \
	EGADSR.h EGDecay.cpp EGDecay.h Engine.cpp Engine.h Filter.h \
	InstrumentResourceManager.cpp InstrumentResourceManager.h Manipulator.h Stream.cpp Stream.h Voice.cpp \
	Voice.h Synthesizer.cpp Profiler.cpp Profiler.h EngineChannel.cpp
liblinuxsamplergigengine_la_LIBADD = $(GIG_LIBS)
liblinuxsamplergigengine_la_LDFLAGS = $(GIG_CFLAGS)

noinst_HEADERS = Synthesizer.h EngineChannel.h EngineGlobals.h
