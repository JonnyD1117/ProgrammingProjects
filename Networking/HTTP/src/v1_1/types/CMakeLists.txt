
target_sources(
    ${target_v1} INTERFACE
    commands.hpp
    status.hpp
)

target_include_directories(${target_v1} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})