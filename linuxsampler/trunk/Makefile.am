# require automake (>= 1.5) due to 'dist-bzip2' option
AUTOMAKE_OPTIONS = 1.5 dist-bzip2

SUBDIRS = man src scripts osx Artwork Documentation debian

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = linuxsampler.pc

EXTRA_DIST = Doxyfile.in \
             linuxsampler.pc.in \
             linuxsampler.kdevelop \
             benchmarks/gigsynth.cpp \
             benchmarks/Makefile \
             benchmarks/triang.cpp

.PHONY: parser testcases

if HAVE_SQLITE3
have_sqlite = "yes"
else
have_sqlite = "no"
endif

install-data-local:
	@if [ ! -e "/var/lib/linuxsampler/instruments.db" -a \
	$(have_sqlite) = "yes" ] ; then \
	mkdir -p /var/lib/linuxsampler && ./src/linuxsampler \
	--create-instruments-db /var/lib/linuxsampler/instruments.db ; \
	fi

# generate parser with yacc
parser:
	@cd $(srcdir)/src/network && make $@

# compile test cases for the LinuxSampler codebase
testcases:
	@cd $(srcdir)/src/testcases && make linuxsamplertest

tests: testcases

docs: Doxyfile
	@echo '*** Running doxygen ***'
	doxygen Doxyfile
