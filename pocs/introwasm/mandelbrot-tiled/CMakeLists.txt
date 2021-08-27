cmake_minimum_required (VERSION 3.7)
project (crosscompile)

# The version number.
set (crosscompile_VERSION_MAJOR 1)
set (crosscompile_VERSION_MINOR 0)


if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(UNIX)
    message(STATUS ">>> Linux/OSx")
    include_directories("~/emsdk/emscripten/1.38.28/system/include/")
    if(WASM)
        message(">>> WebAssembly - WASM=${WASM}")
        set(CMAKE_C_COMPILER "em++")
        set(CMAKE_CXX_COMPILER "em++")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
    endif()
elseif(WIN32)
    message(STATUS ">>> Windows")
    set(CMAKE_CXX_STANDARD 17)
    include_directories("D:/Apps/emsdk/fastcomp/emscripten/system/include/emscripten")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

set(BUILD_SHARED_LIBS OFF)

include_directories("include/")

if(NOT WASM)
    add_executable(crosscompile src/main.cpp src/mycalc.cpp)
else()
    add_library(mandelbrot STATIC mandelbrot.cpp )
endif()

