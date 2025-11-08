cmake_minimum_required(VERSION 3.28)

project(CppArgumentParser LANGUAGES CXX)

# Set Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Required Packages
find_package(GTest    REQUIRED)
find_package(jsoncons REQUIRED)
find_package(yaml-cpp REQUIRED)

# Add Project Sources
add_subdirectory( src )

# Enable CTest
enable_testing()
add_subdirectory( tests )