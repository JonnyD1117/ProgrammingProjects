# Build Test Executable
set( target unit_tests ) 

file(GLOB_RECURSE test_sources
    "${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp"
)

set( libs 
    # GTest::gtest 
    GTest::gtest_main
    engine
)

add_executable( ${target} ${test_sources} )
        
target_link_libraries( ${target} PRIVATE ${libs} )

include(GoogleTest)

# Allow GTest to Register test with CTest
gtest_discover_tests( ${target} PROPERTIES ENVIRONMENT "GTEST_COLOR=$ENV{GTEST_COLOR}")

# gtest_discover_tests(${target}
#     PROPERTIES
#         ENVIRONMENT "GTEST_COLOR=1"
# )