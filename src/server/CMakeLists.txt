set(server_sources
    dataserver.cpp
    reqchannel.cpp
    network_req_channel.cpp
    server_socket.cpp
    client_socket.cpp
    sockets.cpp
)
add_library(server ${server_sources})
add_executable(data_server ${server_sources})
target_link_libraries(server pthread)
target_link_libraries(data_server pthread)
