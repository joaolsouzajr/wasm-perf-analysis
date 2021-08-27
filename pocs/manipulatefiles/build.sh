#!/bin/sh
rm -fr build
mkdir -p build
cd  build
cmake ..

make

emcc build/libfilemgr.a -s WASM=1 -o ../public/filemgr.js

emcc build/libminigzip.a build/libz.a -s WASM=1 -o ../public/minigzip.html
