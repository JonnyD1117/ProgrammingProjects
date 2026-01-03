
# Set Library Name
set( target engine_rendering )

# Create list of Cpp src files
set( sources 
    Camera.cpp
    IndexBuffer.cpp
    Mesh.cpp
    Renderer.cpp
    Shader.cpp
    stb_image_impl.cpp
    Texture.cpp
    VertexArray.cpp
    VertexBuffer.cpp
)

# Create list of Hpp headers
set( headers 
    Camera.hpp
    IndexBuffer.hpp
    Mesh.hpp
    Renderer.hpp
    Shader.hpp
    Texture.hpp
    VertexArray.hpp
    VertexBuffer.hpp
)

# Create list libraries to be linked with
set( libs 
    glfw 
    glad::glad 
    OpenGL::OpenGL
    stb::stb
    glm::glm
)

# Create new lib based on target name 
add_library(${target} STATIC ${sources})

# Link libraries & define include paths
target_link_libraries(${target} PUBLIC ${libs} ) 
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})