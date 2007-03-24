#!/bin/sh

if ! which intltoolize > /dev/null ; then
  echo "Could not find intltoolize, make sure intltool is installed!"
  exit -1
fi
if ! which aclocal > /dev/null ; then
  echo "Could not find aclocal, make sure automake is installed!"
  exit -1
fi
if ! which autoconf > /dev/null ; then
  echo "Could not find autoconf, make sure it is installed!"
  exit -1
fi
if ! which autoheader > /dev/null ; then
  echo "Could not find autoheader, make sure autoconf is installed!"
  exit -1
fi
if ! which automake > /dev/null ; then
  echo "Could not find automake, make sure it is installed!"
  exit -1
fi

intltoolize --force --automake
aclocal
autoconf
autoheader
automake --add-missing
