# not a GNU package. You can remove this line, if
# have all needed files, that a GNU package needs
AUTOMAKE_OPTIONS = foreign 1.4

SUBDIRS = src

.PHONY: parser

# generate parser with lex and yacc
parser:
	@cd $(srcdir)/src/network && make $@
