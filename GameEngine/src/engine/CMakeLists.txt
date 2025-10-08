set( target engine )

################################
#  Add All Engine Directories  #
################################
add_subdirectory( types )
add_subdirectory( interfaces )
# add_subdirectory( audio ) 
# add_subdirectory( core ) 
# add_subdirectory( inputs ) 
add_subdirectory( parsers ) 
add_subdirectory( rendering ) 
# add_subdirectory( resources ) 
add_subdirectory( utils ) 

set( sources 
    Engine.cpp
)

set( headers 
    Engine.hpp
)

set( libs 
    engine_interfaces
    engine_parsers
    engine_rendering
    engine_utils
)

add_library(${target} STATIC ${sources})

target_link_libraries(${target} PUBLIC ${libs} ) 
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})