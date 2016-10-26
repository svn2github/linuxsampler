#!/bin/bash -ex

# This script is primarily made for the linuxsampler build server. It
# copies all files to be included in the installer from the
# installation directories on the build server to the bin directory.

# win32 -----------------------------------------------------------

BIN=`pwd`/bin
DIST=$BIN/686
WIN=/home/persson/win32
MINGW=/home/persson/msys2/mingw32
rm -rf $DIST
mkdir -p $DIST
cd $WIN/bin
cp rifftree.exe dlsdump.exe gigdump.exe gigextract.exe gigmerge.exe \
    gig2mono.exe gig2stereo.exe \
    korg2gig.exe korgdump.exe akaidump.exe akaiextract.exe \
    sf2dump.exe sf2extract.exe \
    linuxsampler.exe \
    gigedit.exe \
    liblscp-6.dll qsampler.exe \
    $DIST
cd $MINGW/bin
cp libgcc_s_dw2-1.dll libwinpthread-1.dll libstdc++-6.dll \
   libsndfile-1.dll libsqlite3-0.dll \
   libFLAC-8.dll libogg-0.dll libvorbis-0.dll libvorbisenc-2.dll \
   libspeex-1.dll \
   Qt5Core.dll Qt5Gui.dll Qt5Widgets.dll libbz2-1.dll libfreetype-6.dll \
   libglib-2.0-0.dll libgraphite2.dll libharfbuzz-0.dll libiconv-2.dll \
   libicudt57.dll libicuin57.dll libicuuc57.dll libintl-8.dll \
   libpcre-1.dll libpcre16-0.dll libpng16-16.dll zlib1.dll \
   libatk-1.0-0.dll libatkmm-1.6-1.dll libcairo-2.dll libcairo-gobject-2.dll \
   libcairomm-1.0-1.dll libepoxy-0.dll libexpat-1.dll libffi-6.dll \
   libfontconfig-1.dll libgdk_pixbuf-2.0-0.dll libgdk-3-0.dll \
   libgdkmm-3.0-1.dll libgio-2.0-0.dll libgiomm-2.4-1.dll \
   libglibmm-2.4-1.dll libgmodule-2.0-0.dll libgobject-2.0-0.dll \
   libgtk-3-0.dll libgtkmm-3.0-1.dll \
   libpango-1.0-0.dll libpangocairo-1.0-0.dll libpangoft2-1.0-0.dll \
   libpangomm-1.4-1.dll libpangowin32-1.0-0.dll \
   libpixman-1-0.dll libsigc-2.0-0.dll \
   $DIST
cd $MINGW/lib/pkgconfig
cp sndfile.pc $DIST
cd $DIST
(cd $MINGW/share/qt5 ; \
 tar cf - \
     plugins/platforms/qwindows.dll) | tar xf -
cd $WIN/lib/bin
cp libgig-7.dll libakai-0.dll libgigedit-3.dll liblinuxsampler-4.dll $DIST
cp $WIN/lib/vst/LinuxSampler.dll $DIST
mkdir -p $DIST/plugins
cp $WIN/lib/linuxsampler/plugins/libgigeditlinuxsamplerplugin.dll \
$DIST/plugins
cd $DIST
(cd $MINGW ; \
 tar cf - \
     share/glib-2.0/schemas/gschemas.compiled \
     share/icons/Adwaita/16x16/actions/document-open-recent-symbolic.symbolic.png \
     share/icons/Adwaita/16x16/actions/edit-clear-symbolic.symbolic.png \
     share/icons/Adwaita/16x16/actions/edit-find-symbolic.symbolic.png \
     share/icons/Adwaita/16x16/actions/folder-new-symbolic.symbolic.png \
     share/icons/Adwaita/16x16/actions/list-add-symbolic.symbolic.png \
     share/icons/Adwaita/16x16/actions/list-remove-symbolic.symbolic.png \
     share/icons/Adwaita/16x16/actions/media-eject-symbolic.symbolic.png \
     share/icons/Adwaita/16x16/actions/pan-down-symbolic.symbolic.png \
     share/icons/Adwaita/16x16/actions/pan-end-symbolic.symbolic.png \
     share/icons/Adwaita/16x16/actions/pan-start-symbolic.symbolic.png \
     share/icons/Adwaita/16x16/actions/pan-up-symbolic.symbolic.png \
     share/icons/Adwaita/16x16/actions/system-run.png \
     share/icons/Adwaita/16x16/actions/window-close-symbolic.symbolic.png \
     share/icons/Adwaita/16x16/actions/window-maximize-symbolic.symbolic.png \
     share/icons/Adwaita/16x16/actions/window-minimize-symbolic.symbolic.png \
     share/icons/Adwaita/16x16/actions/window-restore-symbolic.symbolic.png \
     share/icons/Adwaita/16x16/devices/drive-harddisk-symbolic.symbolic.png \
     share/icons/Adwaita/16x16/devices/drive-optical-symbolic.symbolic.png \
     share/icons/Adwaita/16x16/emblems/emblem-default.png \
     share/icons/Adwaita/16x16/mimetypes/text-x-generic.png \
     share/icons/Adwaita/16x16/places \
     share/icons/Adwaita/16x16/status/dialog-error.png \
     share/icons/Adwaita/16x16/status/dialog-warning-symbolic.symbolic.png \
     share/icons/Adwaita/32x32/devices/drive-harddisk.png \
     share/icons/Adwaita/48x48/status/dialog-warning.png \
     share/icons/Adwaita/96x96/actions/edit-find-symbolic.symbolic.png \
     share/icons/Adwaita/icon-theme.cache \
     share/icons/Adwaita/index.theme \
     share/locale/{de,sv}/LC_MESSAGES/gtk30.mo) | tar xf -
(cd $WIN ; tar cf - \
    share/locale/{de,sv}/LC_MESSAGES/gigedit.mo) | tar xf -
cd $MINGW/share/qt5/translations
cp qt{,base,script,quick1,multimedia,xmlpatterns}_{cs,ru}.qm $DIST/share/locale
cd $WIN/share/locale
cp qsampler_{cs,ru}.qm $DIST/share/locale
cd $WIN/share
cp qsampler.version gigedit.version $DIST
cd $WIN/lib/pkgconfig
cp gig.pc linuxsampler.pc $DIST

# win32sse --------------------------------------------------------

DIST=$BIN/686sse
WIN=/home/persson/win32sse

rm -rf $DIST
mkdir -p $DIST
cd $WIN/bin
cp rifftree.exe dlsdump.exe gigdump.exe gigextract.exe gigmerge.exe \
    gig2mono.exe gig2stereo.exe \
    korg2gig.exe korgdump.exe akaidump.exe akaiextract.exe \
    sf2dump.exe sf2extract.exe linuxsampler.exe \
    $DIST
cd $WIN/lib/bin
cp libgig-7.dll libakai-0.dll liblinuxsampler-4.dll $DIST
cp $WIN/lib/vst/LinuxSampler.dll $DIST


# win64 -----------------------------------------------------------

DIST=$BIN/64
WIN=/home/persson/win64

rm -rf $DIST
mkdir -p $DIST
cd $WIN/bin
cp libsndfile-1.dll libsqlite3-0.dll \
    libFLAC-8.dll libogg-0.dll libvorbis-0.dll libvorbisenc-2.dll \
    rifftree.exe dlsdump.exe gigdump.exe gigextract.exe gigmerge.exe \
    gig2mono.exe gig2stereo.exe \
    korg2gig.exe korgdump.exe akaidump.exe akaiextract.exe \
    sf2dump.exe sf2extract.exe \
    linuxsampler.exe gigedit.exe \
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
cp libgig-7.dll libakai-0.dll libgigedit-3.dll liblinuxsampler-4.dll $DIST
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
