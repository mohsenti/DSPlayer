cmake_minimum_required(VERSION 3.6)
project(DSPlayer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(DSPlayer ${SOURCE_FILES})

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(
        ${GTKMM_LIBRARY_DIRS})

include_directories(
        ${GTKMM_INCLUDE_DIRS})

target_link_libraries(DSPlayer
        ${GTKMM_LIBRARIES})