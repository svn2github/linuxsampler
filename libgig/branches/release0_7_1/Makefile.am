SUBDIRS = doc man src

# to prevent compile errors on some systems
AM_CXXFLAGS = -pedantic

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libgig.pc

doc: Doxyfile
	@echo '*** Running doxygen ***'
	doxygen Doxyfile
