cmake_minimum_required (VERSION 3.7)
project (lyff2)

set(CMAKE_C_COMPILER "emcc")
set(CMAKE_CXX_COMPILER "emcc")

set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/build)

add_library(output src/lyff.c)
target_include_directories(output PUBLIC
  include
)
