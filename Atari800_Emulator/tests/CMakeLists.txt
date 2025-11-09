
# Create Sub-System Test Libraries
add_subdirectory( assembler )
add_subdirectory( atari800 )
add_subdirectory( screen )

# Build Test Executable
set( target atari800_unit_tests ) 

set( source
    main.cpp
)

set( libs 
    assembler_tests
    atari_tests
    screen_tests
)

add_executable( ${target} ${source} )
        
target_link_libraries( ${target} PUBLIC ${libs} )

include(GoogleTest)

# Allow GTest to Register test with CTest
gtest_discover_tests( ${target} PROPERTIES ENVIRONMENT "GTEST_COLOR=$ENV{GTEST_COLOR}")