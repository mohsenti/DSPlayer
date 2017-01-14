
add_executable(scale scale/main.cpp)
target_link_libraries(scale ${GTKMM_LIBRARIES})

add_executable(mainLoop mainLoop/main.cpp)
target_link_libraries(mainLoop ${GTKMM_LIBRARIES})

add_executable(gtkp gtkp/main.cpp)
target_link_libraries(gtkp ${GTKMM_LIBRARIES})

add_executable(zetcode zetcode/main.cpp zetcode/mycpu.cpp zetcode/mycpu.h)
target_link_libraries(zetcode ${GTKMM_LIBRARIES})

add_executable(thread thread/main.cpp)
target_link_libraries(thread ${CMAKE_THREAD_LIBS_INIT})