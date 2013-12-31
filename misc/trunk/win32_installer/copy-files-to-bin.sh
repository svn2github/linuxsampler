#!/bin/sh -ex

# This script is primarily made for the linuxsampler build server. It
# copies all files to be included in the installer from the
# installation directories on the build server to the bin directory.

# win32 -----------------------------------------------------------

BIN=`pwd`/bin
DIST=$BIN/686
WIN=/home/persson/win32
rm -rf $DIST
mkdir -p $DIST
cd $WIN/bin
cp libgig-6.dll libsndfile-1.dll libsqlite3-0.dll \
    libFLAC-8.dll libogg-0.dll libvorbis-0.dll libvorbisenc-2.dll \
    rifftree.exe dlsdump.exe gigdump.exe gigextract.exe gigmerge.exe \
    gig2mono.exe linuxsampler.exe \
    gigedit.exe \
    liblscp-6.dll qsampler.exe \
    $DIST
cd $WIN/gtkmm/redist
cp libatk-1.0-0.dll libatkmm-1.6-1.dll libcairo-2.dll \
    libcairomm-1.0-1.dll libgdkmm-2.4-1.dll \
    libgdk_pixbuf-2.0-0.dll libgdk-win32-2.0-0.dll \
    libgio-2.0-0.dll libgiomm-2.4-1.dll libglib-2.0-0.dll \
    libglibmm-2.4-1.dll libgmodule-2.0-0.dll \
    libgobject-2.0-0.dll libgthread-2.0-0.dll \
    libgtkmm-2.4-1.dll libgtk-win32-2.0-0.dll \
    intl.dll jpeg62.dll libpango-1.0-0.dll \
    libpangocairo-1.0-0.dll libpangomm-1.4-1.dll \
    libpangowin32-1.0-0.dll libpng12-0.dll libsigc-2.0-0.dll \
    libtiff3.dll zlib1.dll \
    $DIST
cd $WIN/lib/bin
cp libgigedit-2.dll liblinuxsampler-3.dll $DIST
cp $WIN/lib/vst/LinuxSampler.dll $DIST
mkdir -p $DIST/plugins
cp $WIN/lib/linuxsampler/plugins/libgigeditlinuxsamplerplugin.dll \
$DIST/plugins
cd $DIST
(cd $WIN/gtkmm ; tar cf - \
    etc/gtk-2.0/gtkrc \
    etc/gtk-2.0/gdk-pixbuf.loaders \
    lib/gtk-2.0/2.10.0/engines/libwimp.dll \
    lib/gtk-2.0/2.10.0/loaders \
    share/themes/MS-Windows \
    share/locale/de/LC_MESSAGES/gtk20.mo \
    share/locale/sv/LC_MESSAGES/gtk20.mo) | tar xf -
(cd $WIN ; tar cf - \
    share/locale/de/LC_MESSAGES/gigedit.mo \
    share/locale/sv/LC_MESSAGES/gigedit.mo) | tar xf -
cd $WIN/qt/bin
cp QtCore4.dll QtGui4.dll mingwm10.dll libgcc_s_dw2-1.dll $DIST
cd $WIN/qt/translations
cp qt_ru.qm qt_cs.qm $DIST/share/locale
cd $WIN/share/locale
cp qsampler_ru.qm qsampler_cs.qm $DIST/share/locale
cd $WIN/share
cp qsampler.version gigedit.version $DIST
cd $WIN/lib/pkgconfig
cp gig.pc linuxsampler.pc sndfile.pc $DIST

# win32sse --------------------------------------------------------

DIST=$BIN/686sse
WIN=/home/persson/win32sse

rm -rf $DIST
mkdir -p $DIST
cd $WIN/bin
cp libgig-6.dll \
    rifftree.exe dlsdump.exe gigdump.exe gigextract.exe gigmerge.exe \
    gig2mono.exe linuxsampler.exe \
    $DIST
cd $WIN/lib/bin
cp liblinuxsampler-3.dll $DIST
cp $WIN/lib/vst/LinuxSampler.dll $DIST


# win64 -----------------------------------------------------------

DIST=$BIN/64
WIN=/home/persson/win64

rm -rf $DIST
mkdir -p $DIST
cd $WIN/bin
cp libgig-6.dll libsndfile-1.dll libsqlite3-0.dll \
    libFLAC-8.dll libogg-0.dll libvorbis-0.dll libvorbisenc-2.dll \
    rifftree.exe dlsdump.exe gigdump.exe gigextract.exe gigmerge.exe \
    gig2mono.exe linuxsampler.exe gigedit.exe \
    $DIST
cd $WIN/gtkmm/bin
cp libatk-1.0-0.dll libatkmm-1.6-1.dll libcairo-2.dll \
    libcairomm-1.0-1.dll libgdkmm-2.4-1.dll \
    libgdk_pixbuf-2.0-0.dll libgdk-win32-2.0-0.dll \
    libgio-2.0-0.dll libgiomm-2.4-1.dll libglib-2.0-0.dll \
    libglibmm-2.4-1.dll libgmodule-2.0-0.dll \
    libgobject-2.0-0.dll libgthread-2.0-0.dll \
    libgtkmm-2.4-1.dll libgtk-win32-2.0-0.dll \
    libintl-8.dll libpango-1.0-0.dll libfontconfig-1.dll \
    libpangocairo-1.0-0.dll libpangomm-1.4-1.dll \
    libpangowin32-1.0-0.dll libpng14-14.dll libsigc-2.0-0.dll \
    zlib1.dll libexpat-1.dll libfreetype-6.dll \
    libpangoft2-1.0-0.dll \
    $DIST
cd ../../..
mkdir -p $DIST/etc/gtk-2.0
echo "gtk-theme-name = \"MS-Windows\"" > $DIST/etc/gtk-2.0/gtkrc
cd mingw64/x86_64-w64-mingw32/lib
cp libgcc_s_sjlj-1.dll libstdc++-6.dll $DIST
cd $WIN/lib/bin
cp libgigedit-2.dll liblinuxsampler-3.dll $DIST
cp $WIN/lib/vst/LinuxSampler.dll $DIST
mkdir -p $DIST/plugins
cp $WIN/lib/linuxsampler/plugins/libgigeditlinuxsamplerplugin.dll \
    $DIST/plugins
cd $DIST
(cd $WIN/gtkmm ; tar cf - \
    lib/gtk-2.0/2.10.0/engines/libwimp.dll \
    share/themes/MS-Windows \
    share/locale/de/LC_MESSAGES/gtk20.mo \
    share/locale/sv/LC_MESSAGES/gtk20.mo) | tar xf -
(cd $WIN ; tar cf - \
    share/locale/de/LC_MESSAGES/gigedit.mo \
    share/locale/sv/LC_MESSAGES/gigedit.mo) | tar xf -
cd $DIST


# Fantasia --------------------------------------------------------

cp /home/persson/share/java/Fantasia-0.9.jar $BIN
