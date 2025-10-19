
set( target emulator )

set (sources 
    main.cpp
    emulator.cpp
)

set( libs 

)

# Compile Library
add_executable( ${target} ${sources} )
target_link_libraries(${target} PUBLIC ${libs})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})