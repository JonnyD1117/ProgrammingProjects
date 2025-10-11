
set( target engine_resources_managers )


set( sources 
    MeshManager.cpp
)

set( headers 
    MeshManager.hpp
)

set( libs 
    engine_interfaces
    engine_importers
    engine_types
)

add_library(${target} STATIC ${sources} )

target_link_libraries(${target} PUBLIC ${libs} ) 
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})