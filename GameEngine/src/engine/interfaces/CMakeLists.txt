set( target engine_interfaces )


set( headers 
    IMeshParser.hpp
    engine_interfaces.hpp
)

set (libs 
    glad::glad 
    OpenGL::OpenGL
    glm::glm
)


add_library(${target} INTERFACE )

target_link_libraries(${target} INTERFACE ${libs} ) 
target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})