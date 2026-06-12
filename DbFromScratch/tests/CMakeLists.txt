# Build Test Executable
set( target unit_tests ) 

# Enable Valgrind within CTest
set(MEMORYCHECK_COMMAND "valgrind" CACHE STRING "Memory checker")
set(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --track-origins=yes" CACHE STRING "Valgrind options")

set( source
    main.cpp
    test_dummy_UT.cpp
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