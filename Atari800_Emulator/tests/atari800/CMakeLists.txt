
# Test DUmmy Library
add_library(atari_tests OBJECT test_dummy_6502_UT.cpp)

target_link_libraries(atari_tests PUBLIC GTest::gtest GTest::gtest_main)

# Add Tests
# add_subdirectory(6502)
# add_subdirectory(devices)