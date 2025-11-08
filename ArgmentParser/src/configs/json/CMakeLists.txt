set(target arg_parser_json)

set(libs
    jsoncons
    arg_parser_types
    arg_parser_interfaces
)

add_library(${target} INTERFACE)

target_link_libraries(${target} INTERFACE ${libs})
target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})