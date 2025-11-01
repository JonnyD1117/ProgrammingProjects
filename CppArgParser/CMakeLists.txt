cmake_minimum_required(VERSION 3.28)

project(CppArgumentParser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Add Project Sources
add_subdirectory( src )

# Enable CTest
enable_testing()
find_package(GTest  REQUIRED)
add_subdirectory( tests )