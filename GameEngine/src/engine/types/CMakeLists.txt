
# Set Library Name
set( target engine_types )

# Create list of Hpp headers
set( headers 
    MeshData.hpp
    MeshTypes.hpp
)

# Create list libraries to be linked with
set( libs 
    glfw 
    glad::glad 
    OpenGL::OpenGL
    glm::glm
)

# Create new lib based on target name 
add_library(${target} INTERFACE)

# Link libraries & define include paths
target_link_libraries(${target} INTERFACE ${libs} ) 
target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})