#!/bin/sh
# zlib
git clone https://github.com/madler/zlib.git $HOME/zlib

# opencv
git clone https://github.com/opencv/opencv.git $HOME/opencv
git clone https://github.com/opencv/opencv_contrib.git  $HOME/opencv_contrib

#install help scripts
git clone https://github.com/lourencoccc/help.git $HOME/help

# emsdk
git clone https://github.com/emscripten-core/emsdk.git $HOME/emsdk

# install emsdk
cd $HOME/emsdk
./emsdk install latest
./emsdk activate latest

echo 'source $HOME/emsdk/emsdk_env.sh --build=Release' >> .bashrc
echo 'source $HOME/emsdk/emsdk_env.sh --build=Release' >> .zshrc
