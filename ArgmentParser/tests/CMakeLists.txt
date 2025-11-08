# Build Test Executable
set( target cpp_argument_parser_unit_tests ) 

set( source
    main.cpp
    test_parser_UT.cpp
)

set( libs 
    GTest::gtest 
    GTest::gtest_main
    ArgumentParser
)

add_executable( ${target} ${source} )
        
target_link_libraries( ${target} PUBLIC ${libs} )

include(GoogleTest)

# Allow GTest to Register test with CTest
gtest_discover_tests( ${target} )