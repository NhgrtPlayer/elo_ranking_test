cmake_minimum_required (VERSION 2.8.9)

project (EloRankingGenerator)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)

add_subdirectory(source)