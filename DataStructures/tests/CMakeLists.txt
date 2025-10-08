#############################
#     Data Struct. Tests    #
#############################

include(GoogleTest)

set( target dsna_unit_tests ) 

set( libs 
        GTest::gtest 
        GTest::gtest_main
        dsna_datastructures
        dsna_algorithms
)

set( source
        array_ut.cpp
        bst_ut.cpp
        deque_ut.cpp
        list_ut.cpp
        vector_ut.cpp 
)

add_executable( ${target} ${source} )
        
target_link_libraries( ${target} PUBLIC ${libs} )

# Allow GTest to Register test with CTest
gtest_discover_tests( ${target} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})