INCLUDES = $(all_includes)
METASOURCES = AUTO

EXTRA_PROGRAMS = linuxsamplertest
linuxsamplertest_SOURCES = linuxsamplertest.cpp PoolTest.cpp ThreadTest.cpp MutexTest.cpp ConditionTest.cpp LSCPTest.cpp
linuxsamplertest_LDADD = $(top_builddir)/src/liblinuxsampler.la -lcppunit
