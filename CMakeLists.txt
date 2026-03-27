cmake_minimum_required(VERSION 3.20)

project(planetFactory VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(SOURCES
    src/main.c
)

add_executable(planetFactory ${SOURCES})

target_include_directories(planetFactory PRIVATE include)

target_compile_options(planetFactory PRIVATE
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O2>
)

target_compile_options(planetFactory PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
