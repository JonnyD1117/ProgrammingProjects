#############################
#     Data Struct. Tests    #
#############################

include(GoogleTest)

set( target engine_unit_tests ) 

# Collect all test source files recursively
file(GLOB_RECURSE ENGINE_TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp"
)

set( libs 
        GTest::gtest 
        GTest::gtest_main
        engine
)

add_executable( ${target} ${ENGINE_TEST_SOURCES})
        
target_link_libraries( ${target} PUBLIC ${libs} )

# Allow GTest to Register test with CTest
gtest_discover_tests( ${target} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})