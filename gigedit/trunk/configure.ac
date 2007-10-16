dnl Process this file with autoconf to produce a configure script.
AC_INIT(configure.ac)
AC_CONFIG_AUX_DIR([.])

#------------------------------------------------------------------------------------
# The following is the current, official release version of gigedit:

GIGEDIT_VER_MAJOR=0
GIGEDIT_VER_MINOR=1
GIGEDIT_VER_RELEASE=0

#------------------------------------------------------------------------------------
# The following is the libtool / shared library version. This doesn't have to
# do anything with the release version. It MUST conform to the following rules:
#
#  1. Start with version information of `0:0:0' for each libtool library.
#  2. Update the version information only immediately before a public release of
#     your software. More frequent updates are unnecessary, and only guarantee
#     that the current interface number gets larger faster.
#  3. If the library source code has changed at all since the last update, then
#     increment revision (`c:r:a' becomes `c:r+1:a').
#  4. If any interfaces have been added, removed, or changed since the last update,
#     increment current, and set revision to 0.
#  5. If any interfaces have been added since the last public release, then increment
#     age.
#  6. If any interfaces have been removed since the last public release, then set age
#     to 0.

LIBGIGEDIT_LT_CURRENT=0
LIBGIGEDIT_LT_REVISION=0
LIBGIGEDIT_LT_AGE=0

SHARED_VERSION_INFO="$LIBGIGEDIT_LT_CURRENT:$LIBGIGEDIT_LT_REVISION:$LIBGIGEDIT_LT_AGE"
AC_LANG_CPLUSPLUS
AC_PROG_CXX
AC_PROG_LIBTOOL
AC_SUBST(SHLIB_VERSION_ARG)
AC_SUBST(SHARED_VERSION_INFO)
AC_SUBST(GIGEDIT_VER_MAJOR)
AC_SUBST(GIGEDIT_VER_MINOR)
AC_SUBST(GIGEDIT_VER_RELEASE)

# configure checks for the following file's existence to make sure that
# the directory that it is told contains the source code in fact does.
# Occasionally people accidentally specify the wrong directory with
# `--srcdir'; this is a safety check.
AC_CONFIG_SRCDIR(src/gigedit/main.cpp)

GETTEXT_PACKAGE=gigedit
AC_SUBST([GETTEXT_PACKAGE])
AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE],["$GETTEXT_PACKAGE"],[Gettext package])

# the libgig header files need this
AC_C_BIGENDIAN

AC_PROG_CXX

IT_PROG_INTLTOOL(0.35.0)
AM_GLIB_GNU_GETTEXT

PKG_CHECK_MODULES(GTKMM, gtkmm-2.4 >= 2.4.10 gthread-2.0)
PKG_CHECK_MODULES(GIG, gig >= 3.2.0)

# check for presence of libsndfile
PKG_CHECK_MODULES(SNDFILE, sndfile >= 1.0.2)
AC_SUBST(SNDFILE_CFLAGS)
AC_SUBST(SNDFILE_LIBS)

# check for loop functionality in libsndfile
gigedit_save_CFLAGS=$CFLAGS
CFLAGS="$SNDFILE_CFLAGS $CFLAGS"
AC_CHECK_MEMBERS([SF_INSTRUMENT.loops],,
		 [AC_MSG_WARN([Your version of libsndfile does not support
    reading of loop information. Gigedit will not be able to
    extract loop information from sample files.])],
		 [#include <sndfile.h>])
CFLAGS=$gigedit_save_CFLAGS

# check for (optional) presence of liblinuxsampler
liblinuxsampler_version="0.5.0"
PKG_CHECK_MODULES(
    LINUXSAMPLER, linuxsampler >= $liblinuxsampler_version,
    have_linuxsampler=1, have_linuxsampler=0
)
LINUXSAMPLER_PLUGIN_DIR=
if test "$have_linuxsampler" = "0"; then
    echo "Required liblinuxsampler version not found!"
    echo "You need to have liblinuxsampler version ${liblinuxsampler_version}"
    echo "installed. Support for on-the-fly editing with LinuxSampler will"
    echo "be disabled."
else
    echo "Found linuxsampler $liblinuxsampler_version"
    echo -n "Retrieving LinuxSampler's plugin dir... "
    LINUXSAMPLER_PLUGIN_DIR=`pkg-config --variable plugindir linuxsampler`
    if test "$LINUXSAMPLER_PLUGIN_DIR" = ""; then
        have_linuxsampler=0
        echo "Error"
        echo "Could not retrieve LinuxSampler's plugin directory. Support"
        echo "for on-the-fly editing with LinuxSampler will be disabled."
    else
        echo "${LINUXSAMPLER_PLUGIN_DIR} "
        # convert absolute LS plugin dir into relative dir
        # (see ch 27.10 of the automake manual,
        #  "Installing to Hard-Coded Locations")
        LINUXSAMPLER_PLUGIN_DIR=`echo "${LINUXSAMPLER_PLUGIN_DIR}" | sed 's/^.*\/lib\//\${libdir}\//g'`
        echo "Relative plugin dir: ${LINUXSAMPLER_PLUGIN_DIR}"
    fi
fi
AC_SUBST(LINUXSAMPLER_CFLAGS)
AC_SUBST(LINUXSAMPLER_LIBS)
AC_SUBST(LINUXSAMPLER_PLUGIN_DIR)
AM_CONDITIONAL(HAVE_LINUXSAMPLER, test $have_linuxsampler = "1")
AC_DEFINE_UNQUOTED(
    HAVE_LINUXSAMPLER, $have_linuxsampler,
    [Define to 1 if you have LinuxSampler installed.]
)

AC_CONFIG_HEADERS(config.h)
AM_INIT_AUTOMAKE(gigedit, "$GIGEDIT_VER_MAJOR.$GIGEDIT_VER_MINOR.$GIGEDIT_VER_RELEASE")

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	src/gigedit/Makefile
	src/plugin/Makefile
	gfx/Makefile
	po/Makefile.in
	debian/Makefile
	doc/Makefile
	doc/quickstart/Makefile
	win32/libgigedit.dev
	win32/gigedit.dev
	win32/gigedit.nsi
	win32/Makefile
])
AC_OUTPUT
