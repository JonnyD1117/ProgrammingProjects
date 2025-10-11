################################
#  Add All Engine Directories  #
################################
add_subdirectory( types )
add_subdirectory( interfaces )
add_subdirectory( importers ) 
add_subdirectory( rendering ) 
add_subdirectory( resources )
# add_subdirectory( utils ) 

set( target engine )

set( sources 
    Engine.cpp
)

set( headers 
    Engine.hpp
)

set( libs 
    engine_interfaces
    engine_importers
    engine_rendering
    # engine_utils
)

add_library(${target} STATIC ${sources})

target_link_libraries(${target} PUBLIC ${libs} ) 
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})