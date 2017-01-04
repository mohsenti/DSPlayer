
add_executable(scroll scroll/main.cpp)
target_link_libraries(scroll ${GTKMM_LIBRARIES})

add_executable(mainLoop mainLoop/main.cpp)
target_link_libraries(mainLoop ${GTKMM_LIBRARIES})

add_executable(thread thread/main.cpp)
target_link_libraries(thread ${CMAKE_THREAD_LIBS_INIT})