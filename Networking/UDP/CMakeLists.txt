cmake_minimum_required(VERSION 3.20)

project(UDP)

# Set C++ Version & Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Set Project Root & Include Directories
set(PROJ_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJ_INCLUDE_DIR ${PROJ_ROOT_DIR}/include)

# Sub Directories for CMake to Parse
add_subdirectory(src)
add_subdirectory(test)