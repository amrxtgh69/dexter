cmake_minimum_required(VERSION 3.10)

project(dexter LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(dexter src/main.c src/parsers/parser.c src/handlers/prompt_handler.c src/handlers/command_handler.c src/commands/commands.c)

install(TARGETS dexter RUNTIME DESTINATION bin)

