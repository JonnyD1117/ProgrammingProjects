################################
#   Add All Test Directories   #
################################
# add_subdirectory( core )
# add_subdirectory( parsers )
# add_subdirectory( rendering )
# add_subdirectory( utils )

###############################
#    Test Exectuable Tests    #
###############################
# set(target engine_unit_tests)

# add_executable( ${target} test_engine_main.cpp )#parsers/obj_parser_test.cpp)

# target_link_libraries( 
#     ${target} PUBLIC 
#     GTest::gtest_main
#     # Engine Libraries
#     engine_parsers

#     # Engine Object Libraries from Testing Libs
#     $<TARGET_OBJECTS:test_engine_parsers>
# )


# get_filename_component(TEST_EXECUTABLE_PATH "${BIN_DIR}/engine_unit_tests" ABSOLUTE)

# add_test(NAME ${target} COMMAND ${TEST_EXECUTABLE_PATH} )

# set_tests_properties(${target} PROPERTIES WORKING_DIRECTORY ${BIN_DIR})
