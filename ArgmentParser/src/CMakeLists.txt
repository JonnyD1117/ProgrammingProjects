set(target arg_parser_core)

# Add Sources
add_subdirectory(types)
add_subdirectory(interfaces)
add_subdirectory(configs)
add_subdirectory(parser)

# Set Project Libaries
set(libs 
    arg_parser_types
    arg_parser_interfaces
    arg_parser_configs
    arg_parser_parser
)

# Create Libary
add_library(${target} INTERFACE )

target_link_libraries(${target} INTERFACE ${libs})
target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})