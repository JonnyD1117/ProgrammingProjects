# Add Configurator Sources
add_subdirectory(yaml)
add_subdirectory(json)

set(target arg_parser_configs)

set(libs 
    arg_parser_types
    arg_parser_interfaces
    arg_parser_yaml
    arg_parser_json
)

add_library(${target} INTERFACE)
target_link_libraries(${target} INTERFACE ${libs})
