set( target engine_utils_strings )

set( sources 
)

set( headers 
    string_search.hpp
)

set( libs 
)

add_library(${target} INTERFACE ${headers})

# target_link_libraries(${target} PUBLIC ${libs} ) 
target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})