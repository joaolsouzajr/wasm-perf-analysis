#!/bin/sh

emcc \
  -o example2.js -I. *.c \
  -s WASM=1 -s ONLY_MY_CODE=1 -s EXPORTED_FUNCTIONS="['_ex2_add','_ex2_circle_area']"
