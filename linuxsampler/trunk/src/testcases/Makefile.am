INCLUDES = $(all_includes)
METASOURCES = AUTO

EXTRA_PROGRAMS = linuxsamplertest
linuxsamplertest_SOURCES = linuxsamplertest.cpp ThreadTest.cpp MutexTest.cpp MutexTest.h ThreadTest.h ConditionTest.cpp
linuxsamplertest_LDADD = $(top_builddir)/src/liblinuxsampler.la -lcppunit
noinst_HEADERS =  ConditionTest.h
