INCLUDES = $(all_includes)
METASOURCES = AUTO

AM_CXXFLAGS = -ffast-math -march=$(target_cpu) -mcpu=$(target_cpu)

noinst_LTLIBRARIES = liblinuxsamplernetwork.la
liblinuxsamplernetwork_la_SOURCES = lscp.h lscpparser.cpp lscpparser.h lscpscanner.cpp lscpserver.cpp lscpserver.h lscpsymbols.h lscpresultset.cpp lscpresultset.h lscpevent.cpp lscpevent.h

.PHONY: parser

# generate parser with lex and yacc
parser:
	@echo "Generating LSCP parser..."
	@if which "lex" > /dev/null && which "yacc" > /dev/null; then \
	    yacc -d lscp.y && \
	    lex --fast --8bit lscp.l && \
	    yacc lscp.y && \
	    mv -f y.tab.h lscpsymbols.h && \
	    mv -f y.tab.c lscpparser.cpp && \
	    mv -f lex.yy.c lscpscanner.cpp; \
	else \
	    echo "You need lex (or flex) and yacc (or bison) to generate the parser."; \
	fi;
