set( target engine_mesh_types )


set( headers 
    mesh_types.hpp
)

set( libs 
    assimp::assimp
    glfw 
    glad::glad 
    OpenGL::OpenGL
    stb::stb
    glm::glm
)

add_library(${target} INTERFACE ${sources})

target_link_libraries(${target} INTERFACE ${libs} ) 
target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})