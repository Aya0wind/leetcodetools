cmake_minimum_required(VERSION 3.17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(leetcodeCPP)
set(CMAKE_CXX_STANDARD 20)
aux_source_directory(src SOURCES)
add_executable(leetcodeCPP ${SOURCES})
