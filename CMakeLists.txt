cmake_minimum_required(VERSION 3.6)
project(DSPlayer)

#set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp UI/Application.cpp UI/Application.h UI/PlayerWindow.cpp UI/PlayerWindow.h Core/CoreTools.h UI/Components/BaseWindow.h)
add_executable(DSPlayer ${SOURCE_FILES})

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-2.4)

link_directories(
        ${GTKMM_LIBRARY_DIRS})

include_directories(
        ${GTKMM_INCLUDE_DIRS})

target_link_libraries(DSPlayer
        ${GTKMM_LIBRARIES})

find_package(Threads)

add_subdirectory(Tests)