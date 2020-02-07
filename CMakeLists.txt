cmake_minimum_required(VERSION 3.15)
project(sha256)

set(CMAKE_CXX_STANDARD 17)

add_executable(sha256 src/main.cpp src/sha256.cc src/sha256.h src/operations.cc src/operations.h)
target_link_libraries(sha256 libfmt.a)