
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
    # GTest::gtest 
    # GTest::gtest_main
    assembler_tests
    atari_tests
    screen_tests
)

add_executable( ${target} ${source} )
        
target_link_libraries( ${target} PUBLIC ${libs} )

include(GoogleTest)

# Allow GTest to Register test with CTest
gtest_discover_tests( ${target} )# WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})