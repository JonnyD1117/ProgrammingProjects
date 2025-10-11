set( target engine_mesh_formats)

set( sources
    assimp_parser.cpp
    fbx_parser.cpp
    gltf_parser.cpp
    obj_parser.cpp
)

set( headers 
    assimp_parser.hpp
    fbx_parser.hpp
    gltf_parser.hpp
    obj_parser.hpp
)

set( libs 
    assimp::assimp
    glfw 
    glad::glad 
    OpenGL::OpenGL
    stb::stb
    glm::glm
    engine_types
    engine_interfaces
)

add_library(${target} STATIC ${sources})

target_link_libraries(${target} PUBLIC ${libs} ) 
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})