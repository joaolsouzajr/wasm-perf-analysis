# Open CV

## Instalação 

Baixar cósdigo fonte e fazer build na plataforma alvo.

    git clone https://github.com/opencv/opencv.git
    git clone https://github.com/opencv/opencv_contrib.git


Necessario configurar os repositorios para versão 4.0.1

    cd opencv
    git checkout tags/4.0.1

Para o projeto TCCWASM as bibliotecs do opencv devem seer compiladas para Linker estatico.
Por isso a compilação p/ Linux e WIndows deve ser feita de maneira estatica.

## Linux

    cd opencv
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS=-m32 -DCMAKE_INSTALL_PREFIX=/usr/local -DBUILD_SHARED_LIBS=OFF ..
    make -j7
    sudo make install

## Windows

Pré requisitos

* Visual Studdio Community 15 2017 versão 32 bits.
* Python 3.7 32 bits
* Python 3.7 64 bits
* Python 2.7 32 bits
* .\python.exe -m pip install numpy

    Configurar cmake e fazer build com Visual Studio Community, versão 15 ou superior.
    cd opencv
    mkdir build
    cd build
    cmake.exe -G "Visual Studio 15 2017" -A Win32 -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF ..
    cmake.exe --build . --config Release --target INSTALL

Após execução dos comando logo acima uma pasta 

## WASM

    cd opencv
    python ./platforms/js/build_js.py build_wasm --build_wasm

## Referências

* [OpenCV no Linux](https://docs.opencv.org/4.0.1/d7/d9f/tutorial_linux_install.html)
* [OpenCV no Windows](https://docs.opencv.org/4.0.1/d5/de5/tutorial_py_setup_in_windows.html)
* [OpenCV JS](https://docs.opencv.org/4.0.1/d4/da1/tutorial_js_setup.html)

https://perso.uclouvain.be/allan.barrea/opencv/cmake_config.html
https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1
