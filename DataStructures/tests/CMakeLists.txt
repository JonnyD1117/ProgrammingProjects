#############################
#     Data Struct. Tests    #
#############################
set( target unit_tests ) 

set( libs 
        GTest::gtest 
        GTest::gtest_main
        dsna_datastructures
        dsna_algorithms
)

set( sources
        array_ut.cpp
        bst_ut.cpp
        deque_ut.cpp
        list_ut.cpp
        vector_ut.cpp 
)

add_executable( ${target} ${sources} )
target_link_libraries( ${target} PUBLIC ${libs} )

include(GoogleTest)

# Allow GTest to Register test with CTest
gtest_discover_tests( ${target} PROPERTIES ENVIRONMENT "GTEST_COLOR=$ENV{GTEST_COLOR}")