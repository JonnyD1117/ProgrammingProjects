// std
#include <iostream>
#include <print>
#include <string>

// local 
#include "ArgumentParser.hpp"

int main(int argc, char* argv[])
{
    // Create CLI Argument Parser
    ArgumentParser parser;
    parser.add_argument("test3", 3, false, "Test String for test3");
    parser.add_argument("test2", 2, false, "Test String for test2");
    parser.add_argument("test1", 1, false, "Test String for test1");

    parser.parse_options(argc, argv);

    // Extract argument value
    std::string value = parser.get<std::string>("test1");
    // int         value = parser.get<int>        ("test1"); // DOESN'T work now because my handling of std::variant is NOT complete

    std::cout << "Arg Parser Test: Value(str) = " << value << std::endl;


    return 0;
}