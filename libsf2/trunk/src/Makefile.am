#SUBDIRS = testcases

# to prevent compile errors on some systems
AM_CXXFLAGS = -pedantic -Wreturn-type

libsf2includedir = $(includedir)/sf2
libsf2include_HEADERS = RIFF.h SF.h

lib_LTLIBRARIES = libsf2.la
libsf2_la_SOURCES = RIFF.cpp SF.cpp
libsf2_la_LDFLAGS = -no-undefined -version-info @SHARED_VERSION_INFO@ @SHLIB_VERSION_ARG@
if WIN32
libsf2_la_LIBADD = -lrpcrt4
endif

bin_PROGRAMS = sf2dump
sf2dump_SOURCES = sf2dump.cpp
sf2dump_LDADD = $(top_builddir)/src/libsf2.la
