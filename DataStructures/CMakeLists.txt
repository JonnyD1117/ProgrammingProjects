cmake_minimum_required( VERSION 3.28 )

project( DataStructures_and_Algorithms )

# Find Packages 
find_package(GTest REQUIRED)

# Enable CTest
enable_testing()

# Add Project Subdirectories
add_subdirectory(src)
add_subdirectory(tests)