# Build Test Executable
set( target cpp_argument_parser_unit_tests ) 

set( source
    main.cpp
)

add_library(screen_tests OBJECT test_parser_UT.cpp)

target_link_libraries(screen_tests PUBLIC GTest::gtest GTest::gtest_main)


set( libs 

)

add_executable( ${target} ${source} )
        
target_link_libraries( ${target} PUBLIC ${libs} )

include(GoogleTest)

# Allow GTest to Register test with CTest
gtest_discover_tests( ${target} )