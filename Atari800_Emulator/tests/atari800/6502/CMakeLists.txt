# Fetch Google Test
# include(FetchContent)
# FetchContent_Declare(
#         googletest
#         URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
# )

# FetchContent_MakeAvailable(googletest)
# include(GoogleTest)


add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

# Create Test Executable
add_executable( test_6502_asm test_6502_asm.cpp)
add_executable( test_6502_cpu test_6502_cpu.cpp)
add_executable( test_6502_memory test_6502_memory.cpp)
add_executable( test_main test_main.cpp)

# Re-direct binaries to "./bin/tests/"
set_target_properties(test_6502_asm PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJ_BIN_DIR}/tests)
set_target_properties(test_6502_cpu PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJ_BIN_DIR}/tests)
set_target_properties(test_6502_memory PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJ_BIN_DIR}/tests)
set_target_properties(test_main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJ_BIN_DIR}/tests)

# Link Test Executables to GTest & 6502 Components Libraries
target_link_libraries( test_6502_asm GTest::GTest  6502_components )
target_link_libraries( test_6502_cpu GTest::GTest  6502_components )
target_link_libraries( test_6502_memory GTest::GTest  6502_components )
target_link_libraries( test_main GTest::GTest  6502_components )

# Invoke GTest with CTest
gtest_discover_tests(test_6502_asm)
# gtest_discover_tests(test_6502_cpu)
# gtest_discover_tests(test_6502_memory)
# gtest_discover_tests(test_main)