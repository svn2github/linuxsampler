# not a GNU package. You can remove this line, if
# have all needed files, that a GNU package needs
AUTOMAKE_OPTIONS = foreign 1.4 dist-bzip2

SUBDIRS = man src

.PHONY: parser testcases

# generate parser with yacc
parser:
	@cd $(srcdir)/src/network && make $@

# compile test cases for the LinuxSampler codebase
testcases:
	@cd $(srcdir)/src/testcases && make linuxsamplertest

tests: testcases
