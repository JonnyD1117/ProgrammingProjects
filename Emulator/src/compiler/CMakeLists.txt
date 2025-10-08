
set( target 6502_emulator )

set (sources 
    emulator.cpp
)

find_package(yaml-cpp REQUIRED)

set( libs 
    yaml-cpp::yaml-cpp
)

# Compile Library
add_library( ${target}  ${sources} )
target_link_libraries(${target} PUBLIC ${libs})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


set( libs 
    assembler_lib
)

add_executable( emulator main.cpp )
target_link_libraries(emulator PUBLIC ${libs}) 