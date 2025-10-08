set( target test_engine_rendering)

# Create list of Cpp src files
set( sources 

)

# Create list libraries to be linked with
set( libs 
    GTest::gtest
)

# Create new lib based on target name 
add_library(${target} OBJECT ${sources})

# Link libraries & define include paths
target_link_libraries(${target} PRIVATE ${libs} ) 
target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})