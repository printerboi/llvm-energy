#! /bin/bash

# Builder Script to download and build examples 
#
#

echo "(1/X) Creating folder structure"
mkdir -p download src src/.build

# SQLite

echo "(2/X) Downloading SQLite3"
[ ! -f "download/sqlite3.zip" ] && curl --output download/sqlite3.zip "https://sqlite.org/2025/sqlite-amalgamation-3500400.zip"
if [ ! -d "src/sqlite" ]; then
    unzip -q download/sqlite3.zip -d src/
    mv src/sqlite-amalgamation-3500400 src/sqlite
else
    echo "=> SQLite already satisfied. Continuing..."
fi

echo "(3/X) Downloading SQLite3"
[ ! -f "download/zlib.zip" ] && curl --output download/zlib.zip "https://zlib.net/zlib131.zip"
if [ ! -d "src/zlib" ]; then
    unzip -q download/zlib.zip -d src/
    mv src/zlib-1.3.1 src/zlib
else
    echo "=> Zlib already satisfied. Continuing..."
fi

echo "(4/X) Downloading LibSodium"
[ ! -f "download/libsodium.tar.gz" ] && curl --output download/libsodium.tar.gz "https://download.libsodium.org/libsodium/releases/libsodium-1.0.18.tar.gz"
if [ ! -d "src/libsodium" ]; then
    tar -xzf download/libsodium.tar.gz -C src/
    mv src/libsodium-1.0.18 src/libsodium
    cd src/libsodium && ./configure
else
    echo "=> LibSodium already satisfied. Continuing..."
fi

echo "(5/X) Building SQLite"
mkdir -p src/.build/sqlite
make build-sql

echo "(6/X) Building Zlib"
mkdir -p src/.build/zlib
make build-zlib

echo "(7/X) Building Libsodium"
mkdir -p src/.build/libsodium
make build-libsodium