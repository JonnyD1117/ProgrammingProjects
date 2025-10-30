add_library(screen_tests OBJECT test_screen_UT.cpp)

target_link_libraries(screen_tests PUBLIC GTest::gtest GTest::gtest_main)
