cmake_minimum_required(VERSION 3.28)

project(CppArgumentParser LANGUAGES CXX)


# Add Project Sources
add_subdirectory( src )

# Enable CTest
enable_testing()
find_package(GTest  REQUIRED)
add_subdirectory( tests )