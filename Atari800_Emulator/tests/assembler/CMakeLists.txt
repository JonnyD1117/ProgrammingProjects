# Build Test Executable
set( target unit_tests_6502_assembler ) 

set( source
    main.cpp
    test_6502_assembler_UT.cpp
)

set( libs 
    GTest::gtest 
    GTest::gtest_main
)

add_executable( ${target} ${source} )
        
target_link_libraries( ${target} PUBLIC ${libs} )

include(GoogleTest)

# Allow GTest to Register test with CTest
gtest_discover_tests( ${target} PROPERTIES ENVIRONMENT "GTEST_COLOR=$ENV{GTEST_COLOR}")