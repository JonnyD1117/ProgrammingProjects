cmake_minimum_required(VERSION 3.28)

project(6502Emulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)

# Enable CTest
enable_testing()

find_package(GTest  REQUIRED)

add_subdirectory( src )
# add_subdirectory( tests )