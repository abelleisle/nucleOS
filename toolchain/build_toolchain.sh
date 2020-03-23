#!/bin/bash

set -e

BU_VER="binutils-2.31.1"
GC_VER="gcc-8.2.0"
JOBS=$(nproc)

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

export TARGET=i686-elf
export PREFIX="$DIR/$TARGET"
export PATH="$PREFIX/bin:$PATH"

mkdir -p $PREFIX/bin
mkdir -p $DIR/build
cd $DIR/build

# Download binutils
if [ ! -d ./$BU_VER ]; then
    wget https://ftp.gnu.org/gnu/binutils/$BU_VER.tar.xz
    tar xf $BU_VER.tar.xz
    rm $BU_VER.tar.xz
fi

# Download gcc
if [ ! -d ./$GC_VER ]; then
    wget https://ftp.gnu.org/gnu/gcc/$GC_VER/$GC_VER.tar.xz
    tar xf $GC_VER.tar.xz
    rm $GC_VER.tar.xz
fi

# Build binutils
if ! [ -x "$(command -v $TARGET-as)" ]; then
    pushd $BU_VER
        # Build binutils
        mkdir -p build
        pushd build
            ../configure --prefix=$PREFIX --target=$TARGET --with-sysroot --disable-nls --disable-werror
            make -j$JOBS
            make install
        popd
    popd
else
    echo "Binutils already built, skipping.."
fi

# Build gcc
if ! [ -x "$(command -v $TARGET-gcc)" ]; then
    pushd $GC_VER
        # Build gcc
        mkdir -p build
        pushd build
            ../configure --prefix=$PREFIX --target=$TARGET --disable-nls --enable-languages=c,c++ --without-headers
            make all-gcc all-target-libgcc -j$JOBS
            make install-gcc install-target-libgcc -j$JOBS
        popd
    popd
else
    echo "gcc already built, skipping.."
fi
