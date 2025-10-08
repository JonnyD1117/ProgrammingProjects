#include <iostream>
#include "http.hpp"
#include "tcp.hpp"

int main()
{

    TCP::Client client("192.168.0.78", 8080);

    std::cout << "Hello HTTP" << std::endl;

    client.Close();

    return 0; 
}