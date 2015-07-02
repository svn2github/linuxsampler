#!/bin/sh -xe

# This script is primarily made for the linuxsampler build server. It
# copies the files created by the previous Max OS X build steps, and
# creates universal binaries from the i686, x86_64 and powerpc
# files. Then it packs all components as a .pkg Mac installer package and
# finally it wraps everything in a tar.bz2 archive.

LIPO=x86_64-apple-darwin9-lipo
P=/home/persson/mac
D=linuxsampler_`date +%Y%m%d`

# command line tools shipped with libgig
gigtools_bins="akaidump akaiextract dlsdump gig2mono gig2stereo gigdump gigextract gigmerge korg2gig korgdump rifftree sf2dump sf2extract"

createuniv ()
{
    $LIPO -create "$P/x86_64/$1" "$P/i686/$1" "$P/powerpc/$1" \
        -output "$D/${2-$1}"
}


rm -rf linuxsampler_*
rm -rf components
rm -rf linuxsampler.prepkg
rm -rf LinuxSampler.pkg
mkdir -p "$D/LinuxSampler" "$D/lib"


# linuxsampler, libgig and dependencies

createuniv lib/libogg.0.dylib
createuniv lib/libvorbis.0.dylib
createuniv lib/libvorbisenc.2.dylib
createuniv lib/libFLAC.8.2.0.dylib
ln -s libFLAC.8.2.0.dylib "$D/lib/libFLAC.8.dylib"
createuniv lib/libsndfile.1.dylib
createuniv lib/libgig/libgig.6.dylib lib/libgig.6.dylib
createuniv lib/linuxsampler/liblinuxsampler.3.dylib lib/liblinuxsampler.3.dylib
createuniv bin/linuxsampler LinuxSampler/linuxsampler
createuniv bin/lscp LinuxSampler/lscp
cp README "$D"
cp licenses.txt "$D/LinuxSampler"

# AU plugin

cp -r "$P/i686/Components/LinuxSamplerAU.component" "$D"
createuniv Components/LinuxSamplerAU.component/Contents/MacOS/LinuxSamplerAU LinuxSamplerAU.component/Contents/MacOS/LinuxSamplerAU


# VST plugin

cp -r "$P/i686/VST/LinuxSampler.vst" "$D"
createuniv VST/LinuxSampler.vst/Contents/MacOS/LinuxSampler LinuxSampler.vst/Contents/MacOS/LinuxSampler


# gigtools

for x in $gigtools_bins
do
    createuniv "bin/$x" "LinuxSampler/$x"
done


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


# generate OS X .pkg package / installer ...

component="codecs"
dlib="components/$component.pkg/lib"
mkdir -p $dlib
for f in `ls $D/lib/libFLAC* $D/lib/libogg* $D/lib/libsndfile* $D/lib/libvorbis*`; do
    cp $f $dlib
done

component="fantasia"
dlib="components/$component.pkg/LinuxSampler"
mkdir -p $dlib
cp -r $D/LinuxSampler/Fantasia.app $dlib

component="gigedit"
dlib="components/$component.pkg/LinuxSampler"
mkdir -p $dlib
cp -r $D/LinuxSampler/$component.app $dlib

component="libgig"
dlib="components/$component.pkg/lib"
mkdir -p $dlib
for f in `ls $D/lib/libgig.*`; do
    cp $f $dlib
done

component="gigtools"
dlib="components/$component.pkg/bin"
mkdir -p $dlib
for f in $gigtools_bins; do
    cp $D/LinuxSampler/$f $dlib
done
dlib="components/$component.pkg/share/man/man1"
mkdir -p $dlib
for f in $gigtools_bins; do
    cp $P/i686/share/man/man1/$f.1 $dlib
done

component="libgigedit"
dlib="$PWD/components/$component.pkg/lib"
mkdir -p $dlib
(
    cd $D/lib/
    for f in `ls -d linuxsampler libgigedit* locale/*/LC_MESSAGES/gigedit.mo`; do
        cp -r --parents $f $dlib
    done
)

component="libgtk"
dlib="$PWD/components/$component.pkg/lib"
mkdir -p $dlib
(
    cd $D/lib/
    for f in `ls -d gdk* gtk* locale/*/LC_MESSAGES/gtk20.mo pango libatk* libcairo* libffi* libfont* libfreetype* libgailutil* libgdk* libgio* libglib* libgmodule* libgobject* libgthread* libgtk* libintl* libjpeg* libpango* libpixman* libpng* libsigc* libtiff*`; do
        cp -r --parents $f $dlib
    done
)

component="liblinuxsampler"
dlib="components/$component.pkg/lib"
mkdir -p $dlib
for f in `ls $D/lib/liblinuxsampler*`; do
    cp $f $dlib
done
mkdir -p "$dlib/linuxsampler/plugins"

component="linuxsampler"
dlib="components/$component.pkg/bin"
mkdir -p $dlib
for f in `ls $D/LinuxSampler/linuxsampler $D/LinuxSampler/lscp`; do
    cp $f $dlib
done

component="linuxsampler_au"
dlib="components/$component.pkg"
mkdir -p $dlib
cp -r $D/LinuxSamplerAU.component $dlib

component="linuxsampler_vst"
dlib="components/$component.pkg"
mkdir -p $dlib
cp -r $D/LinuxSampler.vst $dlib

component="qsampler"
dlib="components/$component.pkg/LinuxSampler"
mkdir -p $dlib
cp -r $D/LinuxSampler/$component.app $dlib


mkdir linuxsampler.prepkg
cp linuxsampler.unpkg/Distribution linuxsampler.prepkg
rsync -r --exclude='.svn' linuxsampler.unpkg/Resources linuxsampler.prepkg
(
    cd components
    for d in `ls -d *.pkg`; do
        mkdir -p ../linuxsampler.prepkg/$d
        (
            cd $d
            find . | cpio -o --format odc --owner 0:80 | gzip -c
        ) > ../linuxsampler.prepkg/$d/Payload
        mkbom -u 0 -g 80 $d ../linuxsampler.prepkg/$d/Bom
        size_kb=`du -sk $d | cut -f 1`
        entries_count=`find . | wc -l`
        cp ../linuxsampler.unpkg/$d/PackageInfo ../linuxsampler.prepkg/$d
        xmltxt=`xmlstarlet ed -u '/pkg-info/payload/@numberOfFiles' -v $entries_count ../linuxsampler.prepkg/$d/PackageInfo | xmlstarlet ed -u '/pkg-info/payload/@installKBytes' -v $size_kb -`
        echo $xmltxt > ../linuxsampler.prepkg/$d/PackageInfo
        identifier=`xmlstarlet sel -t -v '/pkg-info/@identifier' ../linuxsampler.prepkg/$d/PackageInfo`
        xmltxt=`xmlstarlet ed -u "/installer-gui-script/pkg-ref[@id='$identifier']/@installKBytes" -v $size_kb ../linuxsampler.prepkg/Distribution`
        echo $xmltxt > ../linuxsampler.prepkg/Distribution
    done
)
(
    cd linuxsampler.prepkg
    xar --compression none -cf ../LinuxSampler.pkg .
)

tar cjf "$D.tar.bz2" README LinuxSampler.pkg
