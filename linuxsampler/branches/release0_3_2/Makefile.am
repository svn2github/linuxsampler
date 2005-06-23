# require automake (>= 1.5) due to 'dist-bzip2' option
AUTOMAKE_OPTIONS = 1.5 dist-bzip2

SUBDIRS = man src scripts osx Artwork Documentation debian

EXTRA_DIST = Doxyfile linuxsampler.kdevelop

.PHONY: parser testcases

# generate parser with yacc
parser:
	@cd $(srcdir)/src/network && make $@

# compile test cases for the LinuxSampler codebase
testcases:
	@cd $(srcdir)/src/testcases && make linuxsamplertest

tests: testcases
