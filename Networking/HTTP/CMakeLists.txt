cmake_minimum_required(VERSION 3.20)

project(Implement_HTTP_Project)

# Set C++ Version & Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(V1_1 "HTTP Version 1.1" ON)
option(V2 "HTTP Version 2" OFF)


# Set Project Local Include Path
set(PROJ_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROJ_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include(./libs/TcpLibTarget.cmake)

# Sub Directories for CMake to Parse
add_subdirectory(src)
# add_subdirectory(test)
