cmake_minimum_required(VERSION 3.20)

project(planetFactory VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(SOURCES
    src/main.cpp
    src/player.cpp
)

add_executable(planetFactory ${SOURCES})

target_include_directories(planetFactory PRIVATE include)

find_package(raylib QUIET)

if (NOT raylib_FOUND)
    include(FetchContent)

    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5  # or latest stable
    )

    FetchContent_MakeAvailable(raylib)
endif()

target_link_libraries(planetFactory raylib)

target_compile_options(planetFactory PRIVATE
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O2>
)

target_compile_options(planetFactory PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
