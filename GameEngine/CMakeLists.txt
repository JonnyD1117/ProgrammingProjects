cmake_minimum_required(VERSION 4.3)

project(GameEngine_DangerFromTheDeep LANGUAGES CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Packages
find_package(glfw3  REQUIRED)
find_package(glad   REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(GTest  REQUIRED)
find_package(stb    REQUIRED)
find_package(glm    REQUIRED)
find_package(assimp REQUIRED)

# Add project source
add_subdirectory( src )

# Enable CTest
enable_testing()

# Testing
add_subdirectory(tests)