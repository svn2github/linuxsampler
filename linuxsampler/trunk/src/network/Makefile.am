INCLUDES = $(all_includes)
METASOURCES = AUTO

AM_CXXFLAGS = -Wreturn-type -ffast-math $(CXX_CPU_SWITCH)

noinst_LTLIBRARIES = liblinuxsamplernetwork.la
liblinuxsamplernetwork_la_SOURCES = \
	lscp.h \
	lscpparser.cpp lscpparser.h \
	lscpserver.cpp lscpserver.h \
	lscpsymbols.h \
	lscpresultset.cpp lscpresultset.h \
	lscpevent.cpp lscpevent.h

EXTRA_DIST = lscp.y

.PHONY: parser

# generate parser with bison / yacc
parser:
	$(top_builddir)/scripts/generate_parser.sh
