######################################
#  Add Engine Parsers Sub-Libraries  #
######################################
add_subdirectory( mesh_parsers )


#################################
#  Create Engine Parser Libary  #
#################################
set( target engine_parsers )

set( libs 
    engine_mesh_parsers   # Mesh Parsers for loading mesh data from files
)

add_library( ${target} INTERFACE )

target_link_libraries( ${target} INTERFACE ${libs} ) 