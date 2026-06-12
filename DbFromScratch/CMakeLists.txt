cmake_minimum_required(VERSION 3.28)

project(CppTemplate LANGUAGES CXX)

# Enable CTest
include(CTest)
enable_testing()

# Set Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Required Packages
find_package(GTest    REQUIRED)

# Add Project Sources
add_subdirectory( src )

# Project Tests
# add_subdirectory( tests )