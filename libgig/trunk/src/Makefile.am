# set the include path found by configure
INCLUDES= $(all_includes)

# to prevent compile errors on some systems
AM_CXXFLAGS = -pedantic

pkglib_LTLIBRARIES = libgig.la
libgig_la_SOURCES = RIFF.cpp RIFF.h DLS.cpp DLS.h gig.cpp gig.h
libgig_la_LDFLAGS = -module

bin_PROGRAMS = rifftree dlsdump gigdump gigextract
rifftree_SOURCES = rifftree.cpp
rifftree_LDADD = $(top_builddir)/src/libgig.la
dlsdump_SOURCES = dlsdump.cpp
dlsdump_LDADD = $(top_builddir)/src/libgig.la
gigdump_SOURCES = gigdump.cpp
gigdump_LDADD = $(top_builddir)/src/libgig.la
gigextract_SOURCES = gigextract.cpp
gigextract_LDADD = $(top_builddir)/src/libgig.la -ldl
