export WITH_INSTALL=1
export BUILD_BASE_DIR=$PWD/../temp_build
export CONFIG_OPTIONS="--disable-shared"
export CFLAGS="-I$BUILD_BASE_DIR/$BUILD_STYLE/local/include -framework CoreFoundation -Wl,-headerpad_max_install_names"
export CXXFLAGS=$CFLAGS
export PKG_CONFIG_PATH="/opt/local/lib/pkgconfig:$BUILD_BASE_DIR/$BUILD_STYLE/local/lib/pkgconfig"
export HAVE_UNIX98=1
export UB_PRODUCTS=bin/gigedit
export GMSGFMT="msgfmt"
PATH=/opt/local/sbin:/opt/local/bin:$PATH  #  To use MacPorts
source $PROJECT_DIR/autoconf_builder.sh
