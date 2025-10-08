# Client Executable Target
add_library(udp_lib INTERFACE udp.hpp)

# Add 'socket_header.hpp' to client target include path
target_include_directories(
    udp_lib 
    INTERFACE 
    ${PROJ_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)


# Export TCP Lib CMake target for external project usage.
export(
    TARGETS udp_lib
    FILE ${PROJ_ROOT_DIR}/exports/UdpLibTarget.cmake    
    NAMESPACE UDP::
)