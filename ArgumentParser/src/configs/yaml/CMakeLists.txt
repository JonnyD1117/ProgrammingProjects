set(target arg_parser_yaml)

set(libs
    arg_parser_interfaces
    arg_parser_types
    yaml-cpp::yaml-cpp
)

add_library(${target} INTERFACE)

target_link_libraries(${target} INTERFACE ${libs})
target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})