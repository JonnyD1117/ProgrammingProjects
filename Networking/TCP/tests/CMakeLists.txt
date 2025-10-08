# Client Executable Target
add_executable(test_tcp_client test_tcp_client.cpp)

# Server Executable Target
add_executable(test_tcp_server test_tcp_server.cpp)

# Simple Google Client 
add_executable(test_get_google_homepage test_get_google_homepage.cpp)

target_link_libraries(test_tcp_server PUBLIC tcp_library)
target_link_libraries(test_tcp_client PUBLIC tcp_library)
target_link_libraries(test_get_google_homepage PUBLIC tcp_library)
