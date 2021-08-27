#/bin/sh
build_dir=build/
build_linux_dir=build/wasm

if [ ! -d "$build_dir" ]; then
    mkdir $build_dir
fi

if [ ! -d "$build_linux_dir" ]; then
    mkdir -p $build_linux_dir
    cd $build_linux_dir
    cmake -DWASM=1 ../..
fi

cp -r assets/ $build_linux_dir/
cd $build_linux_dir
make
