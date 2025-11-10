# cmake_minimum_required(VERSION 3.20)

# project(Implement_HTTP_Project)

# # Set C++ Version & Standard
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# option(V1_1 "HTTP Version 1.1" ON)
# option(V2 "HTTP Version 2" OFF)


# # Set Project Local Include Path
# set(PROJ_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
# set(PROJ_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# include(./libs/TcpLibTarget.cmake)

# # Sub Directories for CMake to Parse
# add_subdirectory(src)
# # add_subdirectory(test)



# # Build HTTP Version Libraries
# add_subdirectory( v1_1 )


# # Build Container Http Library
# set( target http_lib )

# set(sources http.hpp )

# add_library(${target} INTERFACE )
# target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


# add_executable(${target}_exe main.cpp)



# target_link_libraries(${target}_exe PUBLIC http_lib_v1_1 TCP::tcp_lib)



