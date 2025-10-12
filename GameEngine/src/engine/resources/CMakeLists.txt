


################################
#  Add All Engine Directories  #
################################

add_subdirectory(managers)
add_subdirectory(serializers)

set( target engine_resources )

set( libs 
    engine_resources_managers
    engine_resources_serializers
)

add_library(${target} INTERFACE )

target_link_libraries(${target} INTERFACE ${libs} ) 
target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})