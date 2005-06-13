AUTOMAKE_OPTIONS = dist-bzip2

SUBDIRS = doc man src debian

# to prevent compile errors on some systems
AM_CXXFLAGS = -pedantic

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gig.pc

docs: Doxyfile
	@echo '*** Running doxygen ***'
	doxygen Doxyfile
