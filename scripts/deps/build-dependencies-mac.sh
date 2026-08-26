#!/bin/bash

set -e

merge_binaries() {
  X86DIR=$1
  ARMDIR=$2
  echo "Merging ARM64 binaries from $ARMDIR into fat binaries at $X86DIR..."

  IFS="
"
  pushd "$X86DIR"
  for X86BIN in $(find . \
    -path '*/CMakeFiles/*' -prune -o \
    -type f \
    \( -name '*.dylib' -o -name '*.a' -o -perm +111 \) \
    -print); do
    if file "$X86DIR/$X86BIN" | grep "Mach-O " >/dev/null; then
      ARMBIN="${ARMDIR}/${X86BIN}"
      echo "Merge $ARMBIN to $X86BIN..."
      lipo -create "$X86BIN" "$ARMBIN" -o "$X86BIN"
    fi
  done
  popd
}

if [ "$#" -ne 1 ]; then
    echo "Syntax: $0 <output directory>"
    exit 1
fi

export MACOSX_DEPLOYMENT_TARGET=11.0

NPROCS="$(getconf _NPROCESSORS_ONLN)"
SCRIPTDIR=$(realpath $(dirname "${BASH_SOURCE[0]}"))
INSTALLDIR="$1"
if [ "${INSTALLDIR:0:1}" != "/" ]; then
	INSTALLDIR="$PWD/$INSTALLDIR"
fi

FREETYPE=2.13.3
HARFBUZZ=9.0.0
SDL3=3.4.14
ZSTD=1.5.6
LIBPNG=1.6.43
LIBJPEGTURBO=3.0.3
LIBWEBP=1.4.0
PLUTOSVG=0.0.8
# PlutoVG pin rationale:
# - selected as current upstream release
# - satisfies PlutoSVG 0.0.8 CMake requirement: find_package(plutovg 1.0.0 ...)
PLUTOVG=1.3.3
FFMPEG=7.1.5
MOLTENVK=1.2.9
QT=6.7.2
SHADERC=2026.3

CPUINFO=66ee79c038d70dad9f08705b2c9b3e58f6d8f512
SPIRV_CROSS=vulkan-sdk-1.3.290.0

mkdir -p deps-build
cd deps-build

export PKG_CONFIG_PATH="$INSTALLDIR/lib/pkgconfig:$PKG_CONFIG_PATH"
export LDFLAGS="-L$INSTALLDIR/lib $LDFLAGS"
export CFLAGS="-I$INSTALLDIR/include $CFLAGS"
export CXXFLAGS="-I$INSTALLDIR/include $CXXFLAGS"
CMAKE_COMMON=(
	-DCMAKE_BUILD_TYPE=Release
	-DCMAKE_SHARED_LINKER_FLAGS="-dead_strip -dead_strip_dylibs"
	-DCMAKE_PREFIX_PATH="$INSTALLDIR"
	-DCMAKE_INSTALL_PREFIX="$INSTALLDIR"
	-DCMAKE_INSTALL_NAME_DIR='$<INSTALL_PREFIX>/lib'
)
CMAKE_ARCH_X64=-DCMAKE_OSX_ARCHITECTURES="x86_64"
CMAKE_ARCH_ARM64=-DCMAKE_OSX_ARCHITECTURES="arm64"
CMAKE_ARCH_UNIVERSAL=-DCMAKE_OSX_ARCHITECTURES="x86_64;arm64"

cat > SHASUMS <<EOF
0550350666d427c74daeb85d5ac7bb353acba5f76956395995311a9c6f063289  freetype-$FREETYPE.tar.xz
b7e481b109d19aefdba31e9f5888aa0cdfbe7608fed9a43494c060ce1f8a34d2  harfbuzz-$HARFBUZZ.tar.gz
6a5ca0652392a2d7c9db2ae5b40210843c0bbc081cbd410825ab00cc59f14a6c  libpng-$LIBPNG.tar.xz
343e789069fc7afbcdfe44dbba7dbbf45afa98a15150e079a38e60e44578865d  libjpeg-turbo-$LIBJPEGTURBO.tar.gz
61f873ec69e3be1b99535634340d5bde750b2e4447caa1db9f61be3fd49ab1e5  libwebp-$LIBWEBP.tar.gz
30d4aa2b3037718142b32dffd4e72f917ebb6cc5227150e7bb9c45efb2153aeb  SDL3-$SDL3.tar.gz
8c29e06cf42aacc1eafc4077ae2ec6c6fcb96a626157e0593d5e82a34fd403c1  zstd-$ZSTD.tar.gz
de668509caf9e35e3cd162473441fdb29538c6d96ed080292b3cf9e6fc5d558f  ffmpeg-$FFMPEG.tar.xz
f415a09385030c6510a936155ce211f617c31506db5fbc563e804345f1ecf56e  v$MOLTENVK.tar.gz
c5f22a5e10fb162895ded7de0963328e7307611c688487b5d152c9ee64767599  qtbase-everywhere-src-$QT.tar.xz
e1a1d8785fae67d16ad0a443b01d5f32663a6b68d275f1806ebab257485ce5d6  qtimageformats-everywhere-src-$QT.tar.xz
fb0d1286a35be3583fee34aeb5843c94719e07193bdf1d4d8b0dc14009caef01  qtsvg-everywhere-src-$QT.tar.xz
58e855ad1b2533094726c8a425766b63a04a0eede2ed85086860e54593aa4b2a  qttools-everywhere-src-$QT.tar.xz
9845780b5dc1b7279d57836db51aeaf2e4a1160c42be09750616f39157582ca9  qttranslations-everywhere-src-$QT.tar.xz
e3d09aa27ec50da6310da45d1ec6b2e903c367a1455d8ee350bda12b9dedf556  cpuinfo-$CPUINFO.tar.gz
49d5cfe772d3aa10cd4879f2f6e189f5083c08e4c8ea01bf3d5b87c97dfca7d2  plutosvg-$PLUTOSVG.tar.gz
2b0d17a6e016f47b86f9c00e2cb82600041b1ea1f7d2a00c2d46ae542cbfed3c  plutovg-$PLUTOVG.tar.gz
ee493ccf1b3038b4ef2fe024664c5eb2dc4bcc1f6b05b33e3909de0e19c81024  shaderc-$SHADERC.tar.gz
EOF

curl -L \
	-o "freetype-$FREETYPE.tar.xz" "https://sourceforge.net/projects/freetype/files/freetype2/$FREETYPE/freetype-$FREETYPE.tar.xz/download" \
	-o "harfbuzz-$HARFBUZZ.tar.gz" "https://github.com/harfbuzz/harfbuzz/archive/refs/tags/$HARFBUZZ.tar.gz" \
	-O "https://downloads.sourceforge.net/project/libpng/libpng16/$LIBPNG/libpng-$LIBPNG.tar.xz" \
	-O "https://github.com/libjpeg-turbo/libjpeg-turbo/releases/download/$LIBJPEGTURBO/libjpeg-turbo-$LIBJPEGTURBO.tar.gz" \
	-O "https://storage.googleapis.com/downloads.webmproject.org/releases/webp/libwebp-$LIBWEBP.tar.gz" \
	-O "https://github.com/libsdl-org/SDL/releases/download/release-$SDL3/SDL3-$SDL3.tar.gz" \
	-O "https://github.com/facebook/zstd/releases/download/v$ZSTD/zstd-$ZSTD.tar.gz" \
	-O "https://ffmpeg.org/releases/ffmpeg-$FFMPEG.tar.xz" \
	-O "https://github.com/KhronosGroup/MoltenVK/archive/refs/tags/v$MOLTENVK.tar.gz" \
	-O "https://download.qt.io/archive/qt/${QT%.*}/$QT/submodules/qtbase-everywhere-src-$QT.tar.xz" \
	-O "https://download.qt.io/archive/qt/${QT%.*}/$QT/submodules/qtimageformats-everywhere-src-$QT.tar.xz" \
	-O "https://download.qt.io/archive/qt/${QT%.*}/$QT/submodules/qtsvg-everywhere-src-$QT.tar.xz" \
	-O "https://download.qt.io/archive/qt/${QT%.*}/$QT/submodules/qttools-everywhere-src-$QT.tar.xz" \
	-O "https://download.qt.io/archive/qt/${QT%.*}/$QT/submodules/qttranslations-everywhere-src-$QT.tar.xz" \
	-o "cpuinfo-$CPUINFO.tar.gz" "https://github.com/pytorch/cpuinfo/archive/$CPUINFO.tar.gz" \
	-o "plutosvg-$PLUTOSVG.tar.gz" "https://github.com/sammycage/plutosvg/archive/refs/tags/v$PLUTOSVG.tar.gz" \
	-o "plutovg-$PLUTOVG.tar.gz" "https://github.com/sammycage/plutovg/archive/refs/tags/v$PLUTOVG.tar.gz" \
	-o "shaderc-$SHADERC.tar.gz" "https://github.com/google/shaderc/archive/refs/tags/v$SHADERC.tar.gz"
shasum -a 256 --check SHASUMS

# Have to clone with git, because it does version detection.
if [ ! -d "SPIRV-Cross" ]; then
  git clone https://github.com/KhronosGroup/SPIRV-Cross/ -b $SPIRV_CROSS --depth 1
fi

echo "Installing libpng..."
rm -fr "libpng-$LIBPNG"
tar xf "libpng-$LIBPNG.tar.xz"
cd "libpng-$LIBPNG"
cmake "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_X64" \
	-DBUILD_SHARED_LIBS=ON \
	-DPNG_TESTS=OFF \
	-DPNG_FRAMEWORK=OFF \
	-B build
make -C build "-j$NPROCS"
cmake "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_ARM64" \
	-DBUILD_SHARED_LIBS=ON \
	-DPNG_TESTS=OFF \
	-DPNG_ARM_NEON=on \
	-DPNG_FRAMEWORK=OFF \
	-B build-arm64
make -C build-arm64 "-j$NPROCS"
merge_binaries $(realpath build) $(realpath build-arm64)
make -C build install
cd ..

echo "Building libjpeg..."
rm -fr "libjpeg-turbo-$LIBJPEGTURBO"
tar xf "libjpeg-turbo-$LIBJPEGTURBO.tar.gz"
cd "libjpeg-turbo-$LIBJPEGTURBO"
cmake "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_X64" \
	-DENABLE_STATIC=OFF \
	-DENABLE_SHARED=ON \
	-B build
make -C build "-j$NPROCS"
cmake "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_ARM64" \
	-DENABLE_STATIC=OFF \
	-DENABLE_SHARED=ON \
	-B build-arm64
make -C build-arm64 "-j$NPROCS"
merge_binaries $(realpath build) $(realpath build-arm64)
make -C build install
cd ..

echo "Installing Zstd..."
rm -fr "zstd-$ZSTD"
tar xf "zstd-$ZSTD.tar.gz"
cd "zstd-$ZSTD"
cmake "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_X64" \
	-DBUILD_SHARED_LIBS=ON \
	-DZSTD_BUILD_PROGRAMS=OFF \
	-B build-dir build/cmake
make -C build-dir "-j$NPROCS"
cmake "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_ARM64" \
	-DBUILD_SHARED_LIBS=ON \
	-DZSTD_BUILD_PROGRAMS=OFF \
	-B build-dir-arm64 build/cmake
make -C build-dir-arm64 "-j$NPROCS"
merge_binaries $(realpath build-dir) $(realpath build-dir-arm64)
make -C build-dir install
cd ..

echo "Building FreeType without HarfBuzz..."
rm -fr "freetype-$FREETYPE"
tar xf "freetype-$FREETYPE.tar.xz"
cd "freetype-$FREETYPE"
cmake "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_UNIVERSAL" \
	-DBUILD_SHARED_LIBS=ON \
	-DFT_REQUIRE_ZLIB=ON \
	-DFT_REQUIRE_PNG=ON \
	-DFT_DISABLE_BZIP2=TRUE \
	-DFT_DISABLE_BROTLI=TRUE \
	-DFT_DISABLE_HARFBUZZ=TRUE \
	-B build
cmake --build build --parallel
cmake --install build
cd ..

echo "Building HarfBuzz..."
rm -fr "harfbuzz-$HARFBUZZ"
tar xf "harfbuzz-$HARFBUZZ.tar.gz"
cd "harfbuzz-$HARFBUZZ"
cmake "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_UNIVERSAL" \
	-DBUILD_SHARED_LIBS=ON \
	-DHB_BUILD_UTILS=OFF \
	-B build
cmake --build build --parallel
cmake --install build
cd ..

echo "Building FreeType with HarfBuzz..."
rm -fr "freetype-$FREETYPE"
tar xf "freetype-$FREETYPE.tar.xz"
cd "freetype-$FREETYPE"
cmake "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_UNIVERSAL" \
	-DBUILD_SHARED_LIBS=ON \
	-DFT_REQUIRE_ZLIB=ON \
	-DFT_REQUIRE_PNG=ON \
	-DFT_DISABLE_BZIP2=TRUE \
	-DFT_DISABLE_BROTLI=TRUE \
	-DFT_REQUIRE_HARFBUZZ=TRUE \
	-B build
cmake --build build --parallel
cmake --install build
cd ..

echo "Installing WebP..."
rm -fr "libwebp-$LIBWEBP"
tar xf "libwebp-$LIBWEBP.tar.gz"
cd "libwebp-$LIBWEBP"
cmake "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_X64" \
	-DWEBP_BUILD_ANIM_UTILS=OFF \
	-DWEBP_BUILD_CWEBP=OFF \
	-DWEBP_BUILD_DWEBP=OFF \
	-DWEBP_BUILD_GIF2WEBP=OFF \
	-DWEBP_BUILD_IMG2WEBP=OFF \
	-DWEBP_BUILD_VWEBP=OFF \
	-DWEBP_BUILD_WEBPINFO=OFF \
	-DWEBP_BUILD_WEBPMUX=OFF \
	-DWEBP_BUILD_EXTRAS=OFF \
	-DBUILD_SHARED_LIBS=ON \
	-B build
make -C build "-j$NPROCS"
cmake "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_ARM64" \
	-DWEBP_BUILD_ANIM_UTILS=OFF \
	-DWEBP_BUILD_CWEBP=OFF \
	-DWEBP_BUILD_DWEBP=OFF \
	-DWEBP_BUILD_GIF2WEBP=OFF \
	-DWEBP_BUILD_IMG2WEBP=OFF \
	-DWEBP_BUILD_VWEBP=OFF \
	-DWEBP_BUILD_WEBPINFO=OFF \
	-DWEBP_BUILD_WEBPMUX=OFF \
	-DWEBP_BUILD_EXTRAS=OFF \
	-DBUILD_SHARED_LIBS=ON \
	-B build-arm64
make -C build-arm64 "-j$NPROCS"
merge_binaries $(realpath build) $(realpath build-arm64)
make -C build install
cd ..

echo "Installing SDL3..."
rm -fr "SDL3-$SDL3"
tar xf "SDL3-$SDL3.tar.gz"
cd "SDL3-$SDL3"
cmake "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_UNIVERSAL" \
	-DSDL_X11=OFF \
	-DBUILD_SHARED_LIBS=ON \
	-DSDL_TESTS=OFF \
	-DSDL_TEST_LIBRARY=OFF \
	-B build \
	-G Ninja
cmake --build build --parallel "$NPROCS"
cmake --install build
cd ..

echo "Installing FFmpeg..."
rm -fr "ffmpeg-$FFMPEG"
tar xf "ffmpeg-$FFMPEG.tar.xz"
cd "ffmpeg-$FFMPEG"
mkdir build
cd build
LDFLAGS="-dead_strip $LDFLAGS" CFLAGS="-Os $CFLAGS" CXXFLAGS="-Os $CXXFLAGS" \
	../configure --prefix="$INSTALLDIR" \
	--enable-cross-compile --arch=x86_64 --cc='clang -arch x86_64' --cxx='clang++ -arch x86_64' --disable-x86asm \
	--disable-all --disable-autodetect --disable-static --enable-shared \
	--enable-avcodec --enable-avformat --enable-avutil --enable-swresample --enable-swscale \
	--enable-audiotoolbox --enable-videotoolbox \
	--enable-encoder=ffv1,qtrle,pcm_s16be,pcm_s16le,*_at,*_videotoolbox \
	--enable-muxer=avi,matroska,mov,mp3,mp4,wav \
	--enable-protocol=file
make "-j$NPROCS"
cd ..
mkdir build-arm64
cd build-arm64
LDFLAGS="-dead_strip $LDFLAGS" CFLAGS="-Os $CFLAGS" CXXFLAGS="-Os $CXXFLAGS" \
	../configure --prefix="$INSTALLDIR" \
	--enable-cross-compile --arch=arm64 --cc='clang -arch arm64' --cxx='clang++ -arch arm64' --disable-x86asm \
	--disable-all --disable-autodetect --disable-static --enable-shared \
	--enable-avcodec --enable-avformat --enable-avutil --enable-swresample --enable-swscale \
	--enable-audiotoolbox --enable-videotoolbox \
	--enable-encoder=ffv1,qtrle,pcm_s16be,pcm_s16le,*_at,*_videotoolbox \
	--enable-muxer=avi,matroska,mov,mp3,mp4,wav \
	--enable-protocol=file
make "-j$NPROCS"
cd ..
merge_binaries $(realpath build) $(realpath build-arm64)
cd build
make install
cd ../..

# MoltenVK already builds universal binaries, nothing special to do here.
echo "Installing MoltenVK..."
rm -fr "MoltenVK-${MOLTENVK}"
tar xf "v$MOLTENVK.tar.gz"
cd "MoltenVK-${MOLTENVK}"
./fetchDependencies --macos
make macos
cp Package/Latest/MoltenVK/dynamic/dylib/macOS/libMoltenVK.dylib "$INSTALLDIR/lib/"
cd ..

echo "Installing Qt Base..."
rm -fr "qtbase-everywhere-src-$QT"
tar xf "qtbase-everywhere-src-$QT.tar.xz"
cd "qtbase-everywhere-src-$QT"

# Temporary Qt 6.7.2 compatibility workaround for Apple Clang 21.
#
# Apple Clang 21 reports __has_builtin(__yield) but requires <arm_acle.h> to
# declare it. Prefer the ARM-specific builtin, as current upstream Qt does.
# Remove this patch when upgrading Qt to 6.12 or a version that contains the
# upstream ordering change.
patch -u src/corelib/thread/qyieldcpu.h <<EOF
--- qyieldcpu.h
+++ qyieldcpu.h
@@ -31,8 +31,22 @@
 #ifdef __cplusplus
     noexcept
 #endif
 {
-#if __has_builtin(__yield)
+#if __has_builtin(__builtin_arm_yield)
+    __builtin_arm_yield();
+
+/*
+ * Temporary Apple Clang 21 workaround. Qt 6.7.2 originally tested
+ * __yield first:
+ *
+ * #if __has_builtin(__yield)
+ *     __yield();              // Generic
+ * #endif
+ *
+ * Remove this comment and the preceding __builtin_arm_yield branch when
+ * upgrading Qt to a release that contains the upstream fix.
+ */
+#elif __has_builtin(__yield)
     __yield();              // Generic
 #elif defined(_YIELD_PROCESSOR) && defined(Q_CC_MSVC)
     _YIELD_PROCESSOR();     // Generic; MSVC's <atomic>
EOF

# since we don't have a direct reference to QtSvg, it doesn't deployed directly from the main binary
# (only indirectly from iconengines), and the libqsvg.dylib imageformat plugin does not get deployed.
# We could run macdeployqt twice, but that's even more janky than patching it.

# https://github.com/qt/qtbase/commit/7b018629c3c3ab23665bf1da00c43c1546042035
# The QProcess default wait time of 30s may be too short in e.g. CI environments where processes may be blocked
# for a longer time waiting for CPU or IO.

patch -u src/tools/macdeployqt/shared/shared.cpp <<EOF
--- shared.cpp
+++ shared.cpp
@@ -152,7 +152,7 @@
     LogDebug() << " inspecting" << binaryPath;
     QProcess otool;
     otool.start("otool", QStringList() << "-L" << binaryPath);
-    otool.waitForFinished();
+    otool.waitForFinished(-1);

     if (otool.exitStatus() != QProcess::NormalExit || otool.exitCode() != 0) {
         LogError() << otool.readAllStandardError();
@@ -1122,14 +1122,8 @@
         addPlugins(QStringLiteral("networkinformation"));
     }

-    // All image formats (svg if QtSvg is used)
-    const bool usesSvg = deploymentInfo.containsModule("Svg", libInfix);
-    addPlugins(QStringLiteral("imageformats"), [usesSvg](const QString &lib) {
-        if (lib.contains(QStringLiteral("qsvg")) && !usesSvg)
-            return false;
-        return true;
-    });
-
+    // All image formats
+    addPlugins(QStringLiteral("imageformats"));
     addPlugins(QStringLiteral("iconengines"));

     // Platforminputcontext plugins if QtGui is in use
EOF

cmake "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_UNIVERSAL" \
	-DFEATURE_dbus=OFF \
	-DFEATURE_framework=OFF \
	-DFEATURE_icu=OFF \
	-DFEATURE_opengl=OFF \
	-DFEATURE_sql=OFF \
	-DFEATURE_gssapi=OFF \
	-DFEATURE_system_png=ON \
	-DFEATURE_system_jpeg=ON \
	-DFEATURE_system_zlib=ON \
	-DFEATURE_system_freetype=ON \
	-DFEATURE_system_harfbuzz=ON \
	-B build
make -C build "-j$NPROCS"
make -C build install
cd ..

echo "Installing Qt SVG..."
rm -fr "qtsvg-everywhere-src-$QT"
tar xf "qtsvg-everywhere-src-$QT.tar.xz"
cd "qtsvg-everywhere-src-$QT"
mkdir build
cd build
"$INSTALLDIR/bin/qt-configure-module" .. -- "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_UNIVERSAL"
make "-j$NPROCS"
make install
cd ../..

echo "Installing Qt Image Formats..."
rm -fr "qtimageformats-everywhere-src-$QT"
tar xf "qtimageformats-everywhere-src-$QT.tar.xz"
cd "qtimageformats-everywhere-src-$QT"
mkdir build
cd build
"$INSTALLDIR/bin/qt-configure-module" .. -- "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_UNIVERSAL" -DFEATURE_system_webp=ON
make "-j$NPROCS"
make install
cd ../..

echo "Installing Qt Tools..."
rm -fr "qttools-everywhere-src-$QT"
tar xf "qttools-everywhere-src-$QT.tar.xz"
cd "qttools-everywhere-src-$QT"
mkdir build
cd build
"$INSTALLDIR/bin/qt-configure-module" .. -- "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_UNIVERSAL" -DFEATURE_assistant=OFF -DFEATURE_clang=OFF -DFEATURE_designer=ON -DFEATURE_kmap2qmap=OFF -DFEATURE_linguist=ON -DFEATURE_pixeltool=OFF -DFEATURE_pkg_config=OFF -DFEATURE_qev=OFF -DFEATURE_qtattributionsscanner=OFF -DFEATURE_qtdiag=OFF -DFEATURE_qtplugininfo=OFF
make "-j$NPROCS"
make install
cd ../..

echo "Installing Qt Translations..."
rm -fr "qttranslations-everywhere-src-$QT"
tar xf "qttranslations-everywhere-src-$QT.tar.xz"
cd "qttranslations-everywhere-src-$QT"
mkdir build
cd build
"$INSTALLDIR/bin/qt-configure-module" .. -- "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_UNIVERSAL"
make "-j$NPROCS"
make install
cd ../..

echo "Building shaderc..."
rm -fr "shaderc-$SHADERC"
tar xf "shaderc-$SHADERC.tar.gz"
cd "shaderc-$SHADERC"
./utils/git-sync-deps
cmake "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_UNIVERSAL" \
	-DSHADERC_SKIP_TESTS=ON \
	-DSHADERC_SKIP_EXAMPLES=ON \
	-DSHADERC_SKIP_COPYRIGHT_CHECK=ON \
	-B build
make -C build "-j$NPROCS"
make -C build install
cd ..

echo "Building SPIRV-Cross..."
cd SPIRV-Cross
rm -fr build
cmake "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_UNIVERSAL" \
	-DSPIRV_CROSS_SHARED=ON \
	-DSPIRV_CROSS_STATIC=OFF \
	-DSPIRV_CROSS_CLI=OFF \
	-DSPIRV_CROSS_ENABLE_TESTS=OFF \
	-DSPIRV_CROSS_ENABLE_GLSL=ON \
	-DSPIRV_CROSS_ENABLE_HLSL=OFF \
	-DSPIRV_CROSS_ENABLE_MSL=ON \
	-DSPIRV_CROSS_ENABLE_CPP=OFF \
	-DSPIRV_CROSS_ENABLE_REFLECT=OFF \
	-DSPIRV_CROSS_ENABLE_C_API=ON \
	-DSPIRV_CROSS_ENABLE_UTIL=ON \
	-B build
cmake --build build --parallel
cmake --install build
cd ..

echo "Building cpuinfo..."
rm -fr "cpuinfo-$CPUINFO"
tar xf "cpuinfo-$CPUINFO.tar.gz"
cd "cpuinfo-$CPUINFO"
cmake "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_X64" \
	-DCPUINFO_LIBRARY_TYPE=shared \
	-DCPUINFO_RUNTIME_TYPE=shared \
	-DCPUINFO_LOG_LEVEL=error \
	-DCPUINFO_LOG_TO_STDIO=ON \
	-DCPUINFO_BUILD_TOOLS=OFF \
	-DCPUINFO_BUILD_UNIT_TESTS=OFF \
	-DCPUINFO_BUILD_MOCK_TESTS=OFF \
	-DCPUINFO_BUILD_BENCHMARKS=OFF \
	-DUSE_SYSTEM_LIBS=ON \
	-B build
make -C build "-j$NPROCS"
cmake "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_ARM64" \
	-DCPUINFO_LIBRARY_TYPE=shared \
	-DCPUINFO_RUNTIME_TYPE=shared \
	-DCPUINFO_LOG_LEVEL=error \
	-DCPUINFO_LOG_TO_STDIO=ON \
	-DCPUINFO_BUILD_TOOLS=OFF \
	-DCPUINFO_BUILD_UNIT_TESTS=OFF \
	-DCPUINFO_BUILD_MOCK_TESTS=OFF \
	-DCPUINFO_BUILD_BENCHMARKS=OFF \
	-DUSE_SYSTEM_LIBS=ON \
	-B build-arm64
make -C build-arm64 "-j$NPROCS"
merge_binaries $(realpath build) $(realpath build-arm64)
make -C build install
cd ..

echo "Building plutovg..."
rm -fr "plutovg-$PLUTOVG"
tar xf "plutovg-$PLUTOVG.tar.gz"
cd "plutovg-$PLUTOVG"
cmake "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_UNIVERSAL" \
	-DBUILD_SHARED_LIBS=ON \
	-DPLUTOVG_BUILD_EXAMPLES=OFF \
	-B build \
	-G Ninja
cmake --build build --parallel
ninja -C build install
cd ..

echo "Building plutosvg..."
rm -fr "plutosvg-$PLUTOSVG"
tar xf "plutosvg-$PLUTOSVG.tar.gz"
cd "plutosvg-$PLUTOSVG"
cmake "${CMAKE_COMMON[@]}" "$CMAKE_ARCH_UNIVERSAL" \
	-DBUILD_SHARED_LIBS=ON \
	-DPLUTOSVG_BUILD_EXAMPLES=OFF \
	-B build \
	-G Ninja
cmake --build build --parallel
ninja -C build install
cd ..

echo "Cleaning up..."
cd ..
rm -rf deps-build
