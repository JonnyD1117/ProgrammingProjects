// GTest
#include <gtest/gtest.h>

// std 
#include <iostream>
#include <format>
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

// TEST(TestArugmentParser, TestBooleanOption)
// {
//     std::vector<std::string> args = { 
//                                         "./ArgumentParser",
//                                         "--test_bool1",
//                                         "--test_bool2",
//                                     };

//     std::vector<char*> cli_args = createCmdLineInputs(args);

//     ArgumentParser parser;
//     parser.add_argument("test_bool1",      false,  "Test Boolean1 Handling");
//     parser.add_argument("test_bool2",      true, "Test Boolean2 Handling");
//     parser.add_argument("test_bool_true",  true,  "Test Boolean True Handling");
//     parser.add_argument("test_bool_false", false, "Test Boolean False Handling");

//     parser.parse_options(cli_args.size(), cli_args.data());

//     // Extract argument value
//     bool value_bool1 = parser.get<bool>("test_bool1");
//     bool value_bool2 = parser.get<bool>("test_bool2");
//     bool value_boolt = parser.get<bool>("test_bool_true");
//     bool value_boolf = parser.get<bool>("test_bool_false");

//     // Test 
//     EXPECT_TRUE (value_bool1);
//     EXPECT_FALSE(value_bool2);
//     EXPECT_TRUE (value_boolt);
//     EXPECT_FALSE(value_boolf);
// }

TEST(TestArugmentParser, TestMixedOption)
{
    std::vector<std::string> args = { 
                                        "./ArgumentParser",
                                        "--test_int",   "42",
                                        "--test_double","69.0",
                                        "--test_string","testing_123",
                                        "--test_bool"
                                    };

    std::vector<char*> cli_args = createCmdLineInputs(args);


    ArgumentParser parser;
    parser.add_argument("test_int",    42,           "Test Integer Handling");
    parser.add_argument("test_double", 69.0,         "Test Double Handling");
    parser.add_argument("test_string", "LoremIpsum", "Test String Handling");
    parser.add_argument("test_bool",   false,        "Test Boolean Handling");

    parser.parse_options(cli_args.size(), cli_args.data());

    // Extract argument value
    std::string value_str    = parser.get<std::string>("test_string");
    int         value_int    = parser.get<int>("test_int");
    double      value_double = parser.get<double>("test_double");
    bool        value_bool   = parser.get<bool>("test_bool");

    // Test 
    EXPECT_EQ(value_str,    "testing_123");
    EXPECT_EQ(value_int,    42);
    EXPECT_EQ(value_double, 69.0);
    // EXPECT_TRUE(value_bool);
}

TEST(TestArugmentParser, TestGluedOptions)
{
    std::vector<std::string> args = { 
                                        "./ArgumentParser",
                                        "--test_glued1=testing",
                                        "--test_glued2=one_two_three",
                                    };

    std::vector<char*> cli_args = createCmdLineInputs(args);

    // Create CLI Argument Parser
    ArgumentParser parser;
    parser.add_argument("test_glued1", "whatever",         "Test1 String Handling");
    parser.add_argument("test_glued2", "should_be_useful", "Test2 String Handling");

    // Parse Options
    parser.parse_options(cli_args.size(), cli_args.data());

    // Extract Options from Parser
    std::string value_1 = parser.get<std::string>("test_glued1");
    std::string value_2 = parser.get<std::string>("test_glued2");

    // Test 
    EXPECT_EQ(value_1, "testing");
    EXPECT_EQ(value_2, "one_two_three");
}

TEST(TestArgumentParser, TestYAMLConfigFileOption)
{
    std::vector<std::string> args = { 
                                        "./ArgumentParser", "--help"

                                    };

    std::vector<char*> cli_args = createCmdLineInputs(args);

    std::string confPath = "/home/indy/repos/ProgrammingProjects/ArgmentParser/tests/data/test_config1.yml";

    ArgumentParser parser;
    parser.add_config( confPath );

    // Last thing to Perform (e.g after add_config() && add_argument())
    parser.parse_options(cli_args.size(), cli_args.data());

    // Extract argument value
    std::string my_string = parser.get<std::string>("my_string");
    int         my_int    = parser.get<int>("my_int");
    double      my_double = parser.get<double>("my_double");
    bool        my_bool   = parser.get<bool>("my_bool");

    // Test 
    EXPECT_EQ(my_string, "testing_1234");
    EXPECT_EQ(my_int,    120);
    EXPECT_EQ(my_double, 123.456);
    EXPECT_TRUE(my_bool);
}