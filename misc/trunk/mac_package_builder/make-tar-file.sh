#!/bin/sh -xe

# This script is primarily made for the linuxsampler build server. It
# copies the files created by the previous Max OS X build steps, and
# creates universal binaries from the i686, x86_64 and powerpc
# files. Finally, it packs everything in a tar.bz2 archive.

LIPO=x86_64-apple-darwin9-lipo
P=/home/persson/mac
D=linuxsampler_`date +%Y%m%d`

createuniv ()
{
    $LIPO -create "$P/x86_64/$1" "$P/i686/$1" "$P/powerpc/$1" \
        -output "$D/${2-$1}"
}


rm -rf linuxsampler_*
mkdir -p "$D/LinuxSampler" "$D/lib"


# linuxsampler, libgig and dependencies

createuniv lib/libogg.0.dylib
createuniv lib/libvorbis.0.dylib
createuniv lib/libvorbisenc.2.dylib
createuniv lib/libFLAC.8.2.0.dylib
ln -s libFLAC.8.2.0.dylib "$D/lib/libFLAC.8.dylib"
createuniv lib/libsndfile.1.dylib
createuniv lib/libgig.6.dylib
createuniv lib/linuxsampler/liblinuxsampler.3.dylib lib/liblinuxsampler.3.dylib
createuniv bin/linuxsampler LinuxSampler/linuxsampler
cp README "$D"
cp licenses.txt "$D/LinuxSampler"

# AU plugin

cp -r "$P/i686/Components/LinuxSamplerAU.component" "$D"
createuniv Components/LinuxSamplerAU.component/Contents/MacOS/LinuxSamplerAU LinuxSamplerAU.component/Contents/MacOS/LinuxSamplerAU


# VST plugin

cp -r "$P/i686/VST/LinuxSampler.vst" "$D"
createuniv VST/LinuxSampler.vst/Contents/MacOS/LinuxSampler LinuxSampler.vst/Contents/MacOS/LinuxSampler


# Fantasia

cp -r "$P/Fantasia.app" "$D/LinuxSampler"


# QSampler

./make-qsampler-app.sh
mv qsampler.app "$D/LinuxSampler"


# Gigedit

# no powerpc build of gigedit
createuniv ()
{
    $LIPO -create "$P/x86_64/$1" "$P/i686/$1" \
        -output "$D/${2-$1}"
}

mkdir -p "$D/LinuxSampler/gigedit.app/Contents/MacOS" \
    "$D/lib/gdk-pixbuf-2.0/2.10.0/loaders" \
    "$D/lib/pango/1.8.0/modules" \
    "$D/lib/gtk-2.0" \
    "$D/lib/locale/sv/LC_MESSAGES" \
    "$D/lib/locale/de/LC_MESSAGES" \
    "$D/lib/linuxsampler/plugins"

createuniv lib/gigedit/libgigedit.2.dylib lib/libgigedit.2.dylib
createuniv bin/gigedit LinuxSampler/gigedit.app/Contents/MacOS/gigedit
createuniv lib/linuxsampler/plugins/libgigeditlinuxsamplerplugin.so

for x in libatk-1.0.0.dylib libatkmm-1.6.1.dylib libcairo.2.dylib \
    libcairomm-1.0.1.dylib libffi.6.dylib libfontconfig.1.dylib \
    libfreetype.6.dylib libgailutil.18.dylib libgdkmm-2.4.1.dylib \
    libgdk_pixbuf-2.0.0.dylib libgdk-quartz-2.0.0.dylib libgio-2.0.0.dylib \
    libgiomm-2.4.1.dylib libglib-2.0.0.dylib libglibmm-2.4.1.dylib \
    libgmodule-2.0.0.dylib libgobject-2.0.0.dylib libgthread-2.0.0.dylib \
    libgtkmm-2.4.1.dylib libgtk-quartz-2.0.0.dylib libintl.8.dylib \
    libjpeg.8.dylib libpango-1.0.0.dylib libpangocairo-1.0.0.dylib \
    libpangomm-1.4.1.dylib libpixman-1.0.dylib libpng15.15.dylib \
    libsigc-2.0.0.dylib libtiff.3.dylib \
    gdk-pixbuf-2.0/2.10.0/loaders/libpixbufloader-xpm.so \
    pango/1.8.0/modules/pango-basic-coretext.so
do
    $LIPO -create "/home/persson/macgtk64/lib/$x" \
        "/home/persson/macgtk32/lib/$x" \
        -output "$D/lib/$x"
done

cp PkgInfo Info.plist "$D/LinuxSampler/gigedit.app/Contents"
cp pango.modules "$D/lib/pango/pango.modules"
cp gdk-pixbuf.loaders "$D/lib/gtk-2.0"
cp $P/x86_64/share/locale/de/LC_MESSAGES/gigedit.mo "$D/lib/locale/de/LC_MESSAGES"
cp $P/x86_64/share/locale/sv/LC_MESSAGES/gigedit.mo "$D/lib/locale/sv/LC_MESSAGES"
cp /home/persson/macgtk64/share/locale/de/LC_MESSAGES/gtk20.mo "$D/lib/locale/de/LC_MESSAGES"
cp /home/persson/macgtk64/share/locale/sv/LC_MESSAGES/gtk20.mo "$D/lib/locale/sv/LC_MESSAGES"


# package

tar cjf "$D.tar.bz2" "$D"
