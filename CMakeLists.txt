cmake_minimum_required(VERSION 3.6)
project(DSPlayer)
#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(SOURCE_FILES main.cpp UI/Application.cpp UI/Application.h UI/PlayerWindow.cpp UI/PlayerWindow.h Core/CoreTools.h UI/Components/SeekBar.cpp UI/Components/SeekBar.h)
add_executable(DSPlayer ${SOURCE_FILES})

# Qt4 support
#add_definitions(-DQt4)
#add_definitions(-DUSE_QT)
#find_package(Qt4 4.4 REQUIRED QtCore QtGui)
#target_link_libraries(DSPlayer Qt4::QtCore Qt4::QtGui)

# Qt5 support
add_definitions(-DQt5)
add_definitions(-DUSE_QT)
find_package(Qt5 5.0 REQUIRED Core Gui Widgets)
target_link_libraries(DSPlayer Qt5::Core Qt5::Gui Qt5::Widgets)




#add_subdirectory(OldGtkmmTests)