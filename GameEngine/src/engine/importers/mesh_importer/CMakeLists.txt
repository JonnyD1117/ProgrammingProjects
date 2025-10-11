# Add Mesh Parser Sub-Libraries
add_subdirectory( types )
add_subdirectory( formats )

# Create Mesh Parser Library
set( target engine_mesh_importer )

set( sources 
    mesh_importer.cpp
)

set( headers 
    mesh_importer.hpp
)

set (libs 
    engine_mesh_formats
    engine_mesh_types
    engine_types
)

# Create Mesh Parser Library
add_library(${target} STATIC ${sources})
target_link_libraries(${target} PUBLIC ${libs} ) 
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})