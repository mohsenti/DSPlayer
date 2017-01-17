add_executable(MediaInfoTest MediaInfo/main.cpp)
target_link_libraries(MediaInfoTest mediainfo Threads::Threads)
