cmake_minimum_required(VERSION 3.6)
project(DSPlayer)

add_definitions(-DUSE_QT)

#set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt4 4.4.3 REQUIRED QtCore QtGui phonon)

set(SOURCE_FILES main.cpp UI/Application.cpp UI/Application.h UI/PlayerWindow.cpp UI/PlayerWindow.h Core/CoreTools.h UI/Components/SeekBar.cpp UI/Components/SeekBar.h Core/MimeType/MimeType.cpp Core/MimeType/MimeType.h)
add_executable(DSPlayer ${SOURCE_FILES})

find_package(Threads)

target_link_libraries(DSPlayer Qt4::QtCore Qt4::QtGui Qt4::phonon)

#add_subdirectory(OldGtkmmTests)