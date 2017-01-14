cmake_minimum_required(VERSION 3.6)
project(DSPlayer)

#set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt4 4.4.3 REQUIRED QtCore QtGui)

set(SOURCE_FILES main.cpp UI/Application.cpp UI/Application.h UI/PlayerWindow.cpp UI/PlayerWindow.h Core/CoreTools.h UI/Components/SeekBar.cpp UI/Components/SeekBar.h)
add_executable(DSPlayer ${SOURCE_FILES})

find_package(Threads)

target_link_libraries(DSPlayer Qt4::QtCore Qt4::QtGui)

#add_subdirectory(OldGtkmmTests)