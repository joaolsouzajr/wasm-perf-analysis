#!/bin/sh

em++ \
  -o example3.js --bind --std=c++11 -I. *.cpp \
  -s WASM=1
