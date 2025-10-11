
set( target engine_resources_managers )


set( headers 
    MeshManager.hpp
)

set( libs 
    engine_interfaces
    engine_importers
    engine_types
)

add_library(${target} INTERFACE )

target_link_libraries(${target} INTERFACE ${libs} ) 
target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})