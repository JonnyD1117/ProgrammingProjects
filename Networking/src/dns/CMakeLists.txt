set( target dns_lib )
set( sources dns.hpp )

add_library( ${target} INTERFACE ${sources} )

# add_subdirectory( msgs )
# add_subdirectory( types )

target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# add_executable(${target}_exe main.cpp)
# target_link_libraries(${target}_exe PUBLIC http_lib_v1_1 TCP::tcp_lib)

# target_include_directories(
#     ${taget} 
#     INTERFACE 
#     ${CMAKE_CURRENT_SOURCE_DIR}
# )

# # Export TCP Lib CMake target for external project usage.
# export(
#     TARGETS ${taget}
#     FILE ${PROJ_ROOT_DIR}/exports/DnsLibTarget.cmake    
#     NAMESPACE DNS::
# )