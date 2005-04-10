# set the include path found by configure
INCLUDES = $(all_includes)

METASOURCES = AUTO

# to prevent compile errors on some systems
AM_CXXFLAGS = -pedantic -march=$(target_cpu)

pkglib_LTLIBRARIES = libgig.la
libgig_la_SOURCES = RIFF.cpp RIFF.h DLS.cpp DLS.h gig.cpp gig.h
