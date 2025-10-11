


################################
#  Add All Engine Directories  #
################################

add_subdirectory(managers)
# add_subdirectory(serialization)

set( target engine_resources )

set( libs 
    engine_resources_managers
    # engine_resources_serialization
)

add_library(${target} INTERFACE )

target_link_libraries(${target} INTERFACE ${libs} ) 
target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})