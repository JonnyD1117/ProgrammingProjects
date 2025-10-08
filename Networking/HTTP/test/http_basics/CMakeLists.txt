
set(TCP_CMAKE_PATH /home/indy/repos/CodingProjects/4_Libraries/TcpLibTarget.cmake)

include (${TCP_CMAKE_PATH})


# Simple Google Client 
add_executable(main main.cpp)

set_target_properties(
    main 
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)

# Add 'socket_header.hpp' to client target include path
target_include_directories(
    main
    PRIVATE 
    ${PROJ_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(main PUBLIC TCP::tcp_lib)

