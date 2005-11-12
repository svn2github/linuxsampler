# to prevent compile errors on some systems
AM_CXXFLAGS = -pedantic -Wreturn-type

# link gigextract either against libaudiofile or libsndfile
# (if both exist on the system, prefer libsndfile)
if HAVE_SNDFILE
gigextract_libs = $(SNDFILE_LIBS)
gigextract_flags = $(SNDFILE_CFLAGS)
else
gigextract_libs = $(AUDIOFILE_LIBS)
gigextract_flags = $(AUDIOFILE_CFLAGS)
endif

libgigincludedir = $(includedir)
libgiginclude_HEADERS = RIFF.h DLS.h gig.h

lib_LTLIBRARIES = libgig.la
libgig_la_SOURCES = RIFF.cpp DLS.cpp gig.cpp
libgig_la_LDFLAGS = -version-info @SHARED_VERSION_INFO@ @SHLIB_VERSION_ARG@

bin_PROGRAMS = rifftree dlsdump gigdump gigextract
rifftree_SOURCES = rifftree.cpp
rifftree_LDADD = $(top_builddir)/src/libgig.la
dlsdump_SOURCES = dlsdump.cpp
dlsdump_LDADD = $(top_builddir)/src/libgig.la
gigdump_SOURCES = gigdump.cpp
gigdump_LDADD = $(top_builddir)/src/libgig.la
gigextract_SOURCES = gigextract.cpp
gigextract_LDADD = $(top_builddir)/src/libgig.la $(gigextract_libs) -ldl
gigextract_CFLAGS = $(gigextract_flags)

EXTRA_DIST = helper.h
