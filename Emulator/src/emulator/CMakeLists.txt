
set( target emulator )

set (sources 
    emulator.cpp
)

set( libs 
    # yaml-cpp::yaml-cpp
)

# Compile Library
add_executable( ${target} ${sources} )
target_link_libraries(${target} PUBLIC ${libs})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})