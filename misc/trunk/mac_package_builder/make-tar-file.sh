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
cp REAMDE "$D"
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


# package

tar cjf "$D.tar.bz2" "$D"
