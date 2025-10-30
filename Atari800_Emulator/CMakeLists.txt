cmake_minimum_required(VERSION 3.28)

project(Atari800_Emulator LANGUAGES CXX)

# Enable CTest
enable_testing()

find_package(GTest  REQUIRED)
# find_package(Curses REQUIRED)

# Add Project Sources & Tests
add_subdirectory( src )
add_subdirectory( tests )