export BUILD_BASE_DIR=$PWD/../temp_build
export WITH_INSTALL=1
export CONFIG_OPTIONS="--disable-shared"
export PKG_CONFIG_PATH="$BUILD_BASE_DIR/$BUILD_STYLE/local/lib/pkgconfig"
source $PROJECT_DIR/autoconf_builder.sh
