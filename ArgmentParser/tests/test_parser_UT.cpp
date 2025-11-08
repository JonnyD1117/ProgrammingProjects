// GTest
#include <gtest/gtest.h>

// std 
#include <iostream>
#include <string>
#include <vector>

// local
#include "ArgumentParser.hpp"


/*********************/
/*      Helpers      */
/*********************/
std::vector<char*> createCmdLineInputs(std::vector<std::string>& args)
{
    // Initialize Argc & Argv
    std::vector<char*> argv;

    // Populate Argv
    for(auto& str : args)
    {
        argv.push_back(str.data());
    }

    argv.shrink_to_fit();

    return argv;
}


/*********************/
/*      Tests      */
/*********************/
TEST(TestArugmentParser, TestIntegerOption)
{
    std::vector<std::string> args = { 
                                        "./ArgumentParser",
                                        "--test_int1","1",
                                        "--test_int2","2",
                                    };

    std::vector<char*> cli_args = createCmdLineInputs(args);

    // Create CLI Argument Parser
    ArgumentParser parser;
    parser.add_argument("test_int1", -1,    "Test1 Integer Handling");
    parser.add_argument("test_int2", -2,    "Test2 Integer Handling");
    parser.add_argument("test_int3", -3,    "Test3 Integer Handling");

    // Parse Options
    parser.parse_options(cli_args.size(), cli_args.data());

    // Extract Options from Parser
    int value_1 = parser.get<int>("test_int1");
    int value_2 = parser.get<int>("test_int2");
    int value_3 = parser.get<int>("test_int3");

    // Test 
    EXPECT_EQ(value_1, 1);
    EXPECT_EQ(value_2, 2);
    EXPECT_EQ(value_3,-3);
}

TEST(TestArugmentParser, TestDoubleOption)
{
    std::vector<std::string> args = { 
                                        "./ArgumentParser",
                                        "--test_double1","1.0",
                                        "--test_double2","2.0",
                                    };

    std::vector<char*> cli_args = createCmdLineInputs(args);

    // Create CLI Argument Parser
    ArgumentParser parser;
    parser.add_argument("test_double1", -1.0,    "Test1 Double Handling");
    parser.add_argument("test_double2", -2.0,    "Test2 Double Handling");
    parser.add_argument("test_double3", -3.0,    "Test3 Double Handling");

    // Parse Options
    parser.parse_options(cli_args.size(), cli_args.data());

    // Extract Options from Parser
    double value_1 = parser.get<double>("test_double1");
    double value_2 = parser.get<double>("test_double2");
    double value_3 = parser.get<double>("test_double3");

    // Test 
    EXPECT_EQ(value_1, 1.0);
    EXPECT_EQ(value_2, 2.0);
    EXPECT_EQ(value_3,-3.0);
}

TEST(TestArugmentParser, TestStringOption)
{
    std::vector<std::string> args = { 
                                        "./ArgumentParser",
                                        "--test_str1","testing",
                                        "--test_str2","one_two_three",
                                    };

    std::vector<char*> cli_args = createCmdLineInputs(args);

    // Create CLI Argument Parser
    ArgumentParser parser;
    parser.add_argument("test_str1", "whatever",         "Test1 String Handling");
    parser.add_argument("test_str2", "should_be_useful", "Test2 String Handling");
    parser.add_argument("test_str3", "default_string",   "Test3 String Handling");

    // Parse Options
    parser.parse_options(cli_args.size(), cli_args.data());

    // Extract Options from Parser
    std::string value_1 = parser.get<std::string>("test_str1");
    std::string value_2 = parser.get<std::string>("test_str2");
    std::string value_3 = parser.get<std::string>("test_str3");

    // Test 
    EXPECT_EQ(value_1, "testing");
    EXPECT_EQ(value_2, "one_two_three");
    EXPECT_EQ(value_3, "default_string");
}

TEST(TestArugmentParser, TestMixedOption)
{
    std::vector<std::string> args = { 
                                        "./ArgumentParser",
                                        "--test_int",   "42",
                                        "--test_double","69.0",
                                        // "--test_string"," testing_123",
                                    };

    std::vector<char*> cli_args = createCmdLineInputs(args);


    ArgumentParser parser;
    parser.add_argument("test_int",    42,           "Test Integer Handling");
    parser.add_argument("test_double", 69.0,         "Test Double Handling");
    parser.add_argument("test_string", "LoremIpsum", "Test String Handling");
    // parser.add_argument("test_bool",   false, "Test Boolean Handling");

    parser.parse_options(cli_args.size(), cli_args.data());

    // Extract argument value
    std::string value_str    = parser.get<std::string>("test_string");
    int         value_int    = parser.get<int>("test_int");
    double      value_double = parser.get<double>("test_double");
    // bool        value_bool   = parser.get<bool>("test_bool");

    // Test 
    EXPECT_EQ(value_str,    "LoremIpsum");
    EXPECT_EQ(value_int,    42);
    EXPECT_EQ(value_double, 69.0);
}

// TEST(TestArugmentParser, TestBooleanOption)
// {
//     EXPECT_TRUE(true);
// }
