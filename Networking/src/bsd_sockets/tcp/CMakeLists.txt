######################
#   BSD TCP Client
######################
set(target_c bsd_tcp_client)

set(sources_c client.cpp )

# Create Client
add_executable(${target_c} ${sources_c})
target_include_directories(${target_c} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

######################
#   BSD TCP Server
######################
set(target_s bsd_tcp_server)

set(sources_s server.cpp )

# Create Server
add_executable(${target_s} ${sources_s}  )
target_include_directories(${target_s} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})