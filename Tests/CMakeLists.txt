add_executable(MediaInfoTest MediaInfo/main.cpp)
target_link_libraries(MediaInfoTest mediainfo Threads::Threads)

add_executable(UnixDomainSocketServer UnixDomainSocket/server.cpp)
add_executable(UnixDomainSocketClient UnixDomainSocket/client.cpp)