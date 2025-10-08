#include "socket_headers.hpp"
#include <iostream> 
#include <string>
#include "tcp_client.hpp"

int main(int argc, char **argv) 
{
    // TCP::Client client("192.168.0.78", 8080);
    TCP::Client client("172.217.12.142", 8080);
    
    // client.Connect(); 

    // std::string message = "GET / HTTP/1.1\r\n\r\n";

    // client.Send(message);
    // std::cout << client.Receive() << std::endl;

    // client.Close();
    return 0; 
}