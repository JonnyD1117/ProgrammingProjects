# Add Mesh Parser Sub-Libraries
add_subdirectory( formats )

# Create Mesh Parser Library
set( target engine_mesh_importer )

set( sources 
    MeshImporter.cpp
)

set( headers 
    MeshImporter.hpp
)

set (libs 
    engine_mesh_formats
    engine_types
)

# Create Mesh Parser Library
add_library(${target} STATIC ${sources})
target_link_libraries(${target} PUBLIC ${libs} ) 
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})