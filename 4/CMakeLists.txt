cmake_minimum_required(VERSION 3.28)
project(pi-bite C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(mpfr REQUIRED)

add_library(${PROJECT_NAME} SHARED countmodule.c)

target_link_libraries(${PROJECT_NAME} mpfr::mpfr)