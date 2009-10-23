if HAVE_SF2
INCLUDES = $(all_includes) $(SF2_CFLAGS) $(GIG_CFLAGS)
METASOURCES = AUTO

AM_CXXFLAGS = -Wreturn-type -ffast-math

noinst_LTLIBRARIES = liblinuxsamplersf2engine.la
liblinuxsamplersf2engine_la_SOURCES = \
	InstrumentResourceManager.cpp InstrumentResourceManager.h \
	DiskThread.cpp DiskThread.h \
	EngineChannel.cpp EngineChannel.h \
	Engine.cpp Engine.h \
	Voice.cpp Voice.h \
	Stream.cpp Stream.h
liblinuxsamplersf2engine_la_LIBADD = $(SF2_LIBS)
liblinuxsamplersf2engine_la_LDFLAGS = $(SF2_CFLAGS)
endif
