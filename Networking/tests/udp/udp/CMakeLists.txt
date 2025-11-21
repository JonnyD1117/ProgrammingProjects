# Client Executable Target
add_executable(test_udp_client test_udp_client.cpp)

set_target_properties(
    test_udp_client 
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)

# Server Executable Target
add_executable(test_udp_server test_udp_server.cpp)

set_target_properties(
    test_udp_server 
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)


target_link_libraries(test_udp_server PUBLIC udp_lib)
target_link_libraries(test_udp_client PUBLIC udp_lib)
