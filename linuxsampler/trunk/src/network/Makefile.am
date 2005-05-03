INCLUDES = $(all_includes)
METASOURCES = AUTO

AM_CXXFLAGS = -Wreturn-type -ffast-math -march=$(target_cpu)

if HAVE_SQLITE3
sqlite3_lflags = $(SQLITE3_LIBS)
else
sqlite3_lflags =
endif

noinst_LTLIBRARIES = liblinuxsamplernetwork.la
liblinuxsamplernetwork_la_SOURCES = lscp.h lscpparser.cpp lscpparser.h lscpserver.cpp lscpserver.h lscpsymbols.h lscpresultset.cpp lscpresultset.h lscpevent.cpp lscpevent.h lscpinstrumentloader.cpp
liblinuxsamplernetwork_la_LIBADD = $(sqlite3_lflags)

.PHONY: parser

# generate parser with lex and yacc
parser:
	@echo "Generating LSCP parser..."
	@if which "yacc" > /dev/null; then \
	    yacc -d lscp.y && \
	    yacc lscp.y && \
	    mv -f y.tab.h lscpsymbols.h && \
	    mv -f y.tab.c lscpparser.cpp; \
	else \
	    echo "You need yacc (or bison) to generate the parser."; \
	fi;
