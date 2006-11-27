INCLUDES = $(all_includes)
METASOURCES = AUTO

AM_CXXFLAGS = -Wreturn-type -ffast-math $(CXX_CPU_SWITCH)

if HAVE_SQLITE3
sqlite3_lflags = $(SQLITE3_LIBS)
sqlite3_cflags = $(SQLITE3_CFLAGS)
else
sqlite3_lflags =
sqlite3_cflags =
endif

noinst_LTLIBRARIES = liblinuxsamplernetwork.la
liblinuxsamplernetwork_la_SOURCES = \
	lscp.h \
	lscpparser.cpp lscpparser.h \
	lscpserver.cpp lscpserver.h \
	lscpsymbols.h \
	lscpresultset.cpp lscpresultset.h \
	lscpevent.cpp lscpevent.h

liblinuxsamplernetwork_la_LIBADD = $(sqlite3_lflags)
liblinuxsamplernetwork_la_CFLAGS = $(sqlite3_cflags)
liblinuxsamplernetwork_la_CXXFLAGS = $(sqlite3_cflags)

EXTRA_DIST = lscp.y

.PHONY: parser

# generate parser with lex and yacc
parser:
	@echo "Generating LSCP parser..."
	@if which "yacc" > /dev/null; then \
	    yacc -d lscp.y && \
	    yacc lscp.y && \
	    mv -f y.tab.h lscpsymbols.h && \
	    mv -f y.tab.c lscpparser.cpp && \
	    echo -n "Updating Documentation/lscp.xml..." && \
	    (cd ../../scripts/ && ./update_grammar.pl) && \
	    echo "OK"; \
	else \
	    echo "You need yacc (or bison) to generate the parser."; \
	fi;
