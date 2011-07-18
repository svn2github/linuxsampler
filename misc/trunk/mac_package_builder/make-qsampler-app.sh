#!/bin/sh -xe

P=/home/persson/mac
LIPO=i686-apple-darwin9-lipo
INSTALL_NAME_TOOL=i686-apple-darwin9-install_name_tool

rm -rf qsampler.app
cp -r "$P/i686/bin/qsampler.app" .
$LIPO -create "$P/i686/bin/qsampler.app/Contents/MacOS/qsampler" "$P/powerpc/bin/qsampler.app/Contents/MacOS/qsampler" -output qsampler.app/Contents/MacOS/qsampler 
$LIPO -create "$P/i686/lib/liblscp.6.dylib" "$P/powerpc/lib/liblscp.6.dylib" -output qsampler.app/Contents/Resources/liblscp.6.dylib

cp "$P"/i686/share/locale/qsampler_*.qm qsampler.app/Contents/Resources
cp "$P/qt/Developer/Applications/Qt/translations/qt_cs.qm" qsampler.app/Contents/Resources
cp "$P/qt/Developer/Applications/Qt/translations/qt_ru.qm" qsampler.app/Contents/Resources

cp "$P/Fantasia.app/Contents/Resources/LSCPScript.icns" qsampler.app/Contents/Resources/qsampler.icns
sed '/CFBundleIconFile/,/<key>/s/<string>.*<\/string>/<string>qsampler.icns<\/string>/' "$P/i686/bin/qsampler.app/Contents/Info.plist" > qsampler.app/Contents/Info.plist

mkdir -p qsampler.app/Contents/Frameworks
tar cf - -C "$P/qt/Library/Frameworks" --exclude=Headers QtCore.framework QtGui.framework | tar xf - -C qsampler.app/Contents/Frameworks

$INSTALL_NAME_TOOL -change QtCore.framework/Versions/4/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/4/QtCore qsampler.app/Contents/Frameworks/QtGui.framework/QtGui
$INSTALL_NAME_TOOL -change QtCore.framework/Versions/4/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/4/QtCore qsampler.app/Contents/MacOS/qsampler
$INSTALL_NAME_TOOL -change QtGui.framework/Versions/4/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/4/QtGui qsampler.app/Contents/MacOS/qsampler

$INSTALL_NAME_TOOL -change "$P/i686/lib/liblscp.6.dylib" @executable_path/../Resources/liblscp.6.dylib qsampler.app/Contents/MacOS/qsampler
$INSTALL_NAME_TOOL -change "$P/powerpc/lib/liblscp.6.dylib" @executable_path/../Resources/liblscp.6.dylib qsampler.app/Contents/MacOS/qsampler
