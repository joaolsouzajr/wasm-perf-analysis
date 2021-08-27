#/bin/sh
build_dir=build/
build_linux_dir=build/wasm

if [ ! -d "$build_dir" ]; then
    mkdir $build_dir
fi

if [ ! -d "$build_linux_dir" ]; then
    mkdir -p $build_linux_dir
    cd $build_linux_dir
    cmake -G "Unix Makefiles" -DWASM=1 ../..
fi

cd $build_linux_dir
make

em++ libmandelbrot.a --bind --std=c++17 -o ../../mandelbrot_.js -s WASM=1 \
#    -s ALLOW_MEMORY_GROWTH=1 \
#    -s FORCE_FILESYSTEM=1 \
    #-s MODULARIZE=1 \
    #-s EXPORT_NAME='myapp'

#emcc build/libminigzip.a build/libz.a -s WASM=1 -o ../public/minigzip.html


