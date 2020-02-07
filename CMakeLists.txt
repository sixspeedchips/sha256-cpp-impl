cmake_minimum_required(VERSION 3.15)
project(sha256)

set(CMAKE_CXX_STANDARD 17)
add_executable(sha256 main.cpp sha256.cc sha256.h)
target_link_libraries(sha256 libfmt.a)