


# add_subdirectory(6502)
# add_subdirectory(devices)
add_subdirectory(screen)


set( target atari800 )

set (sources 
    main.cpp
)

set( libs 
    # 6502
    screen
)

# Compile Library
add_executable( ${target} ${sources} )
target_link_libraries(${target} PUBLIC ${libs})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})