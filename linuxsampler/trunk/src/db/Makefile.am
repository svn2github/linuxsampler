INCLUDES = $(all_includes)
AM_CXXFLAGS = -Wreturn-type -ffast-math $(CXX_CPU_SWITCH)
METASOURCES = AUTO

if HAVE_SQLITE3
sqlite3_lflags = $(SQLITE3_LIBS)
sqlite3_cflags = $(SQLITE3_CFLAGS)
else
sqlite3_lflags =
sqlite3_cflags =
endif

liblinuxsamplerdbincludedir = $(includedir)/linuxsampler/db
liblinuxsamplerdbinclude_HEADERS = \
	InstrumentsDb.h

noinst_LTLIBRARIES = liblinuxsamplerdb.la
liblinuxsamplerdb_la_SOURCES = \
	InstrumentsDb.cpp InstrumentsDb.h

liblinuxsamplerdb_la_LIBADD = $(sqlite3_lflags)
liblinuxsamplerdb_la_CFLAGS = $(sqlite3_cflags)
liblinuxsamplerdb_la_CXXFLAGS = $(sqlite3_cflags)
