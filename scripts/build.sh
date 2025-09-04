# this file will containe all the build scripts

cmake_minimum_required(VERSION 3.10)

project(smol-shell LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(my_program src/main.c)
