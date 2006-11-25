INCLUDES = $(all_includes)
METASOURCES = AUTO

EXTRA_PROGRAMS = linuxsamplertest
linuxsamplertest_SOURCES = \
	linuxsamplertest.cpp \
	PoolTest.cpp PoolTest.h \
	ThreadTest.cpp ThreadTest.h \
	MutexTest.cpp MutexTest.h \
	ConditionTest.cpp ConditionTest.h \
	LSCPTest.cpp LSCPTest.h
linuxsamplertest_LDADD = $(top_builddir)/src/liblinuxsampler.la -lcppunit
