// std
#include <iostream>
#include <print>
#include <string>
#include <typeinfo>

// local 
#include "ArgumentParser.hpp"

int main(int argc, char* argv[])
{
    // Create CLI Argument Parser
    ArgumentParser parser;
    parser.add_argument("test_int",    69,    "Test Integer Handling");
    parser.add_argument("test_double", 42.0,  "Test Double Handling");
    parser.add_argument("test_string", "idk", "Test String Handling");
    parser.add_argument("test_bool",   false, "Test Boolean Handling");

    parser.parse_options(argc, argv);

    // Extract argument value
    std::string value_str    = parser.get<std::string>("test_string");
    int         value_int    = parser.get<int>("test_int");
    double      value_double = parser.get<double>("test_double");
    bool        value_bool   = parser.get<bool>("test_bool");

    std::cout << "Arg Parser Test: (" << typeid(value_str).name()  << ") --test_string = " << value_str << std::endl;
    std::cout << "Arg Parser Test: (" << typeid(value_int).name()  << ") --test_int = " << value_int << std::endl;
    std::cout << "Arg Parser Test: (" << typeid(value_double).name()  << ") --test_double = " << value_double << std::endl;
    std::cout << "Arg Parser Test: (" << typeid(value_bool).name()  << ") --test_bool = " << value_bool << std::endl;


    return 0;
}