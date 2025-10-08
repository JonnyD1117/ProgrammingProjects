# Add Mesh Parser Sub-Libraries
add_subdirectory( types )
add_subdirectory( formats )

# Create Mesh Parser Library
set( target engine_mesh_parsers )

set( headers 
    mesh_parser.hpp
)

set (libs 
    engine_mesh_formats
    engine_mesh_types
)

# Create Mesh Parser Library
add_library(${target} INTERFACE )
target_link_libraries(${target} INTERFACE ${libs} ) 
target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})