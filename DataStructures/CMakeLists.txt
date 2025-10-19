cmake_minimum_required( VERSION 3.28 )

project( DataStructures_and_Algorithms )

# Option to turn on ASan
option(ENABLE_ASAN "Enable AddressSanitizer" OFF)

if(ENABLE_ASAN)
    message(STATUS "AddressSanitizer enabled")
    
    # Add compiler flags
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
        add_link_options(-fsanitize=address)
    else()
        message(WARNING "ASan not supported for this compiler")
    endif()
endif()

# Find Packages 
find_package(GTest REQUIRED)

# Enable CTest
enable_testing()

# Add Project Subdirectories
add_subdirectory(src)
add_subdirectory(tests)