######################################
#  Add Engine Parsers Sub-Libraries  #
######################################
add_subdirectory( mesh_importer )


#################################
#  Create Engine Parser Libary  #
#################################
set( target engine_importers )

set( libs 
    engine_mesh_importer   # Mesh Parsers for loading mesh data from files
)

add_library( ${target} INTERFACE )

target_link_libraries( ${target} INTERFACE ${libs} ) 