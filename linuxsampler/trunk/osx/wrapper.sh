export BUILD_BASE_DIR=$PWD/../temp_build
export WITH_INSTALL=1
export CONFIG_OPTIONS="--disable-shared --enable-signed-triang-algo=intmathabs --enable-unsigned-triang-algo=intmathabs"
export CFLAGS="-I$BUILD_BASE_DIR/$BUILD_STYLE/local/include"
export CXXFLAGS=$CFLAGS
export PKG_CONFIG_PATH="$BUILD_BASE_DIR/$BUILD_STYLE/local/lib/pkgconfig"
export HAVE_UNIX98=1
source $PROJECT_DIR/autoconf_builder.sh
