cmake_minimum_required(VERSION 3.28)

project(OpenGlTutorial LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)

# Enable CTest
enable_testing()

find_package(glfw3  REQUIRED)
find_package(glad   REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(GTest  REQUIRED)
find_package(stb    REQUIRED)
find_package(glm    REQUIRED)
find_package(assimp REQUIRED)

add_subdirectory( src )

add_executable( my_app main.cpp )
target_link_libraries(my_app PUBLIC engine) 