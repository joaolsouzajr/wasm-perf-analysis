#!/bin/sh

emcc hello.c -s WASM=1 -o hello.html
