bin_PROGRAMS = rifftree gigdump dlsdump gigextract

# set the include path found by configure
INCLUDES= $(all_includes)

# the library search path.
rifftree_SOURCES =  rifftree.cpp
lib_LIBRARIES =  libgig.a
libgig_a_SOURCES = RIFF.cpp RIFF.h DLS.cpp DLS.h gig.cpp gig.h
rifftree_LDADD = $(top_builddir)/src/libgig.a
gigdump_SOURCES =  gigdump.cpp
gigdump_LDADD = $(top_builddir)/src/libgig.a


dlsdump_SOURCES =  dlsdump.cpp
dlsdump_LDADD = $(top_builddir)/src/libgig.a


applnkApplicationdir = $(kde_appsdir)/Application
gigextract_SOURCES =  gigextract.cpp
gigextract_LDADD = $(top_builddir)/src/libgig.a -ldl


