INCLUDES = $(all_includes)
METASOURCES = AUTO
noinst_LTLIBRARIES = liblinuxsamplernetwork.la
liblinuxsamplernetwork_la_SOURCES = lscp.h lscpparser.cpp lscpparser.h lscpscanner.cpp lscpserver.cpp lscpserver.h lscpsymbols.h

.PHONY: parser

# generate parser with lex and yacc
parser:
	@echo "Generating LSCP parser..."
	@if which "lex" > /dev/null && which "yacc" > /dev/null; then \
	    yacc -d lscp.y && \
	    lex -f lscp.l && \
	    yacc lscp.y && \
	    mv -f y.tab.h lscpsymbols.h && \
	    mv -f y.tab.c lscpparser.cpp && \
	    mv -f lex.yy.c lscpscanner.cpp; \
	else \
	    echo "You need lex (or flex) and yacc (or bison) to generate the parser."; \
	fi;
