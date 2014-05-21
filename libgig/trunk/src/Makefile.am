# to prevent compile errors on some systems
AM_CXXFLAGS = -pedantic -Wreturn-type

libgigincludedir = $(includedir)
libgiginclude_HEADERS = RIFF.h DLS.h SF.h gig.h Korg.h

pkglib_LTLIBRARIES = libgig.la
libgig_la_SOURCES = RIFF.cpp DLS.cpp SF.cpp gig.cpp Korg.cpp
libgig_la_LDFLAGS = -no-undefined -version-info @SHARED_VERSION_INFO@ @SHLIB_VERSION_ARG@
if WIN32
libgig_la_LIBADD = -lrpcrt4
endif
if MAC
libgig_la_LDFLAGS += -framework CoreFoundation
endif

EXTRA_DIST = helper.h

SUBDIRS = . tools testcases
