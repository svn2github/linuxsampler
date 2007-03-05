dnl Process this file with autoconf to produce a configure script.
AC_INIT(gigedit,0.0.3)
AC_CONFIG_SRCDIR(src/main.cpp)

AC_CONFIG_HEADERS(config.h)

AM_INIT_AUTOMAKE

GETTEXT_PACKAGE=gigedit
AC_SUBST([GETTEXT_PACKAGE])
AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE],["$GETTEXT_PACKAGE"],[Gettext package])

AC_PROG_CXX

IT_PROG_INTLTOOL(0.35.0)
AM_GLIB_GNU_GETTEXT

PKG_CHECK_MODULES(GTKMM, gtkmm-2.4 >= 2.6.1 gthread-2.0)
PKG_CHECK_MODULES(GIG, gig >= 3.1.0)

AC_CONFIG_FILES([
Makefile
src/Makefile
po/Makefile.in
])
AC_OUTPUT
