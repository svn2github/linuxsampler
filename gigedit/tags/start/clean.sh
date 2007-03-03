find . -type l | xargs rm -f


rm -rf *~ autom4te.cache aclocal.m4 config.* configure COPYING m4 \
    depcomp INSTALL install-sh Makefile Makefile.in missing mkinstalldirs \
    stamp-h1 intltool-* gigedit-*.tar.gz core.* \
    po/*~ po/Makefile* po/POTFILES po/stamp-it* po/*.gmo po/*.pot \
    src/*.o src/gigedit src/Makefile.in src/Makefile src/.deps src/*~ \
    src/tags src/core.* src/a.out

