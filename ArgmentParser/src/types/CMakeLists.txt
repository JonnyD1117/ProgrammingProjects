set(target arg_parser_types)

set(libs

)

add_library(${target} INTERFACE)
target_link_libraries(${target} INTERFACE ${libs})
target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})