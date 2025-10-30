add_library(assembler_tests OBJECT test_assembler_UT.cpp)

target_link_libraries(assembler_tests PUBLIC GTest::gtest GTest::gtest_main)

