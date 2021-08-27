#/bin/sh
build_dir=build/
build_linux_dir=build/linux

if [ ! -d "$build_dir" ]; then
    mkdir $build_dir
fi

if [ ! -d "$build_linux_dir" ]; then
    mkdir -p $build_linux_dir
    cd $build_linux_dir
    cmake -G "Unix Makefiles" ../..
fi

cd $build_linux_dir
make



