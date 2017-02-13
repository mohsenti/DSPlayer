cmake_minimum_required(VERSION 3.6)
project(DSPlayer)
#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(SOURCE_FILES main.cpp UI/Application.cpp UI/Application.h UI/PlayerWindow.cpp UI/PlayerWindow.h
        Core/CoreTools.h UI/Components/SeekBar.cpp UI/Components/SeekBar.h Core/DateTimeHelper.h
        Core/Core.h Core/DateTimeHelper.cpp UI/Components/AudioTreeWidgetItem.cpp UI/Components/AudioTreeWidgetItem.h
        Core/CoreTypes.h UI/Components/TreeView.cpp UI/Components/TreeView.h
        Core/UnixDomainSocket.h Core/UnixDomainSocket.cpp Core/Pipe.cpp Core/Pipe.h UI/CommunicateThread.cpp UI/CommunicateThread.h Core/CoreFileSystem.cpp Core/CoreFileSystem.h)
add_executable(DSPlayer ${SOURCE_FILES})

# Qt4 support
#add_definitions(-DQt4)
#add_definitions(-DUSE_QT)
#find_package(Qt4 4.4 REQUIRED QtCore QtGui)
#target_link_libraries(DSPlayer Qt4::QtCore Qt4::QtGui)

#Threads Support
find_package(Threads)
target_link_libraries(DSPlayer Threads::Threads)

# Qt5 support
add_definitions(-DQt5)
add_definitions(-DUSE_QT)
find_package(Qt5 5.0 REQUIRED Core Gui Widgets Multimedia)
target_link_libraries(DSPlayer Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Multimedia)

#taglib
#add_subdirectory(3rdParties/taglib)
#add_dependencies(DSPlayer tag)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdParties/taglib/taglib/includes)
#target_link_libraries(DSPlayer tag)

#mediainfo
add_subdirectory(3rdParties/mediainfo/MediaInfoLib/Project/CMake)
add_dependencies(DSPlayer mediainfo)
include_directories(3rdParties/mediainfo/MediaInfoLib/Source)
include_directories(3rdParties/mediainfo/ZenLib/Source)
target_link_libraries(DSPlayer mediainfo)


#add_subdirectory(OldGtkmmTests)

add_subdirectory(Tests)