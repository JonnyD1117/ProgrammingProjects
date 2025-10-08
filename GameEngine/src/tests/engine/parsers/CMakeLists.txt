set( target test_engine_parsers)

# Create list of Cpp src files
set( sources 
    obj_parser_test.cpp
)

# Create list libraries to be linked with
set( libs 
    GTest::gtest
    engine_parsers
)

# Create new lib based on target name 
add_library(${target} OBJECT ${sources})

# Link libraries & define include paths
target_link_libraries(${target} PUBLIC ${libs} ) 
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})