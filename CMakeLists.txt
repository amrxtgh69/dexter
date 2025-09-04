cmake_minimum_required(VERSION 3.10)

project(dexter LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(dexter src/main.cpp)

install(TARGETS dexter RUNTIME DESTINATION bin)

