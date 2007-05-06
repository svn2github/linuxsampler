#!/bin/sh
# autoconf_builder.sh
# LinuxSampler
#
# Created by Toshi Nagata on 07/04/18.
# Copyright 2007 __MyCompanyName__. All rights reserved.
#
#  Influential environmental variables:
#  ACTION(*): autoconf - run "make -f Makefile.cvs"; configure - run "configure";
#          make - run "make"; install - run "make install";
#          build (or empty string) - autoconf && configure && make (&& install)
#            "install" step is only done if WITH_INSTALL is non-empty
#  BUILD_STYLE(*): The build style. If it ends with "ppc" or "i386", it also specifies the architecture.
#  WITH_INSTALL: When non-empty, "install" action is automatically done in "build" action.
#  CFLAGS, CXXFLAGS: Compiler flags
#  CONFIG_OPTIONS: Options for "configure"
#  BUILD_BASE_DIR: Temporary building and install directory. By default "$PWD/build".
#  SDKROOT: The root directory for SDK
#
#  The variables marked with (*) are automatically set by Xcode.

BASE_DIR=$PWD
BASE_NAME=`basename $PWD`

function rel2abs () {
	(cd "$1"; pwd)
#	pushd "$1" >/dev/null
#	pwd
#	popd >/dev/null
}

function abs2rel () {
	/usr/bin/perl -e 'use File::Spec; print File::Spec->abs2rel($ARGV[0], $ARGV[1]), "\n";' "$1" "$2"
}

function link_recursive () {
	local arg base i
	arg="$1"
	base=`basename "$arg"`
	if test -d "$arg"; then
		if expr "$base" = "CVS" "|" `rel2abs "$arg"` = "$BUILD_BASE_DIR" >/dev/null; then
			echo "Skipping directory $arg"
		else
			echo "Copying directory $arg"
			mkdir -p "$base"
			cd "$base"
			if ! expr "$arg" : "^/" >/dev/null; then
				arg="../$arg"
			fi
			for i in "$arg"/*; do
				link_recursive "$i"
			done
			cd ..
		fi
	else
		echo "Linking $arg"
		ln -sf $arg
	fi
}

#  Sanity checks
if test "x$BUILD_STYLE" = "x"; then
	BUILD_STYLE="Default"
fi
if test "x$ACTION" = "x"; then
	ACTION="build"
fi
if test "x$BUILD_BASE_DIR" = "x"; then
	BUILD_BASE_DIR=$PWD/build
fi
BUILD_DIR="$BUILD_BASE_DIR/$BUILD_STYLE/$BASE_NAME.build"
mkdir -p "$BUILD_DIR" || exit $?
BUILD_BASE_DIR=`rel2abs "$BUILD_BASE_DIR"`
BUILD_DIR=`rel2abs "$BUILD_DIR"`
CONFIG_OPTIONS="--prefix=$BUILD_BASE_DIR/$BUILD_STYLE/local $CONFIG_OPTIONS"

if test -e "$SDKROOT"; then
	SYSROOT_CFLAGS="-isysroot $SDKROOT"
else
	SYSROOT_CFLAGS=
fi
PATH="/usr/local/bin:$PATH"


ARCH_CFLAGS=""
ARCH_CONFIG_OPTIONS=""
case "$BUILD_STYLE" in
    *ppc)
	ARCH="ppc"
	ARCH_CFLAGS="-arch ppc"
	;;
    *i386)
	ARCH="i386"
	ARCH_CFLAGS="-arch i386 -msse -msse2"
	ARCH_CONFIG_OPTIONS="--host=i386-apple-darwin8"
	;;
    *UB|*Universal)
	ARCH="UB"
	;;
    *)
	echo "Warning: architecture cannot be recognized from the build style"
	ARCH="unknown"
	;;
esac

case "$BUILD_STYLE" in
    Development|Default)
	OPT_CFLAGS="-O2 -g"
	;;
    Deployment*)
	OPT_CFLAGS="-O3"
	;;
esac

export CFLAGS="$SYSROOT_CFLAGS $ARCH_CFLAGS $OPT_CFLAGS $CFLAGS"
export CXXFLAGS="$SYSROOT_CFLAGS $ARCH_CFLAGS $OPT_CFLAGS $CXXFLAGS"

#  Display all environments
set

#  Move to the working directory
cd $BUILD_DIR

#  Clean if specified
if test "x$ACTION" = "xclean"; then
	if test "x$WITH_INSTALL" != "x" -a -e "Makefile"; then
		echo "Doing make uninstall"
		make uninstall
	fi
    echo "Removing files in $BUILD_DIR"
	cd $BASE_DIR
    rm -rf "$BUILD_DIR"
    exit $?
fi

if test "x$ACTION" = "xbuild" -o "x$ACTION" = "xconfigure"; then
	#  Copy the source files if necessary
	if test ! -e Makefile -a ! -e configure -a ! -e Makefile.cvs; then
		echo "Copying the source files to $BUILD_DIR"
		for i in `abs2rel "$BASE_DIR" "$BUILD_DIR"`/*; do
			link_recursive $i
		done
	fi
	#  Make ./configure if necessary
	if test -e Makefile.cvs -a ! -e configure; then
		echo "Running make -f Makefile.cvs"
		make -f Makefile.cvs || exit $?
	fi
	#  Run ./configure if necessary
	if test -e configure -a ! -e Makefile; then
		CONFIG_ARGS="$CONFIG_OPTIONS $ARCH_CONFIG_OPTIONS $CONFIG_ENVS"
		echo "Running configure $CONFIG_ARGS"
		./configure $CONFIG_ARGS || exit $?
	fi
fi

if test "x$ACTION" = "xbuild" -o "x$ACTION" = "xmake"; then
	#  make
	echo "Running make"
	make || exit $?
fi

#  make install if specified
if test "x$ACTION" = "xinstall" -o "(" "x$ACTION" = "xbuild" -a "x$WITH_INSTALL" != "x" ")"; then
    echo "Running make install"
    make install || exit $?
fi
