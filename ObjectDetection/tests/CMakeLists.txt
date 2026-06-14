set(target unit_tests)

set( source
    main.cpp
    test_dummy_ut.cpp
)

set( libs 
    GTest::gtest 
    GTest::gtest_main
#     dsna_algorithms
    dsna_datastructures
)

add_executable( ${target} ${source} )
        
target_link_libraries( ${target} PUBLIC ${libs} )

include(GoogleTest)

# Allow GTest to Register test with CTest
gtest_discover_tests( ${target} PROPERTIES ENVIRONMENT "GTEST_COLOR=$ENV{GTEST_COLOR}")