
set(target dsna_datastructures)

add_library(${target} 
        INTERFACE
        array.hpp
        linked_list.hpp
        vector.hpp
        binary_search_tree.hpp
)

target_include_directories( ${target} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )