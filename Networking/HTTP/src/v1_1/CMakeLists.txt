
set( target_v1 http_lib_v1_1 )

set(sources 
    http_server.hpp
    http_client.hpp
)

add_library(${target_v1} INTERFACE )
target_include_directories(${target_v1} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${target_v1} INTERFACE TCP::tcp_lib)

# add_subdirectory( exceptions )
# add_subdirectory( messages )
add_subdirectory( parser )
# add_subdirectory( request )
# add_subdirectory( response )
add_subdirectory( types )


