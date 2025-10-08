# Build HTTP Version Libraries
add_subdirectory( v1_1 )


# Build Container Http Library
set( target http_lib )

set(sources http.hpp )

add_library(${target} INTERFACE )
target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(${target}_exe main.cpp)



target_link_libraries(${target}_exe PUBLIC http_lib_v1_1 TCP::tcp_lib)







