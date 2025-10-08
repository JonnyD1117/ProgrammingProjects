cmake_minimum_required(VERSION 3.28)

project(TCPinCPP LANGUAGES CXX)

# Enable CTest
enable_testing()

find_package(GTest  REQUIRED)
include(GoogleTest)

add_subdirectory( src )
add_subdirectory( tests )