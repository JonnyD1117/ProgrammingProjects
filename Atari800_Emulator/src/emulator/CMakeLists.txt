# Add Source Files
add_subdirectory(6502)
add_subdirectory(devices)
add_subdirectory(screen)

set( target atari800 )

set (sources 
    main.cpp
)

set( libs 
    atari800_6502
    atari800_screen
)

# Compile Library
add_executable( ${target} ${sources} )
target_link_libraries(${target} PUBLIC ${libs})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})