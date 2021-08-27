cmake_minimum_required (VERSION 3.7)
project (manipulatefiles)

# The version number.
set (manipulatefiles_VERSION_MAJOR 1)
set (manipulatefiles_VERSION_MINOR 0)

set(CMAKE_C_COMPILER "emcc")
set(CMAKE_CXX_COMPILER "emcc")

set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/build)

add_library(filemgr STATIC src/filemgr.cpp)
target_include_directories(filemgr PUBLIC
  include
)

add_subdirectory(thirdparty/zlib)
add_library(minigzip STATIC src/minigzip.c)
target_link_libraries(minigzip zlib)
target_include_directories(minigzip PUBLIC
  thirdparty/zlib
)
