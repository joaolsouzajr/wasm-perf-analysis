#!/bin/sh

cmake ..

make

emcc build/liboutput.a -o output.js -s ONLY_MY_CODE=1 -s WASM=1 -s EXPORTED_FUNCTIONS="['_board_step','_board_init','_board_ref']"
