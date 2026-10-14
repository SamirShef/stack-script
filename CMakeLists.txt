cmake_minimum_required(VERSION 3.20)
project(stack-script)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "src/*.c")
add_executable(stack-script ${SOURCES})
target_include_directories(stack-script PRIVATE include)
target_link_libraries(stack-script m)
