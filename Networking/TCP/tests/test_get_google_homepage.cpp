#include "socket_headers.hpp"
#include <iostream> 
#include <string>
#include "tcp.hpp"


std::string pad_string(std::string msg, size_t num_sends=5)
{   
    msg[msg.length()] = ';';
    for(int i = msg.length()+1; i < (num_sends*4096); ++i)
    {
        msg += "0";
    }

    return msg;
}

int main(int argc, char **argv) 
{
    TCP::Client client("192.168.0.78", 8080);
    // TCP::Client client("172.217.12.142", 8080);
    
    client.Connect(); 

    std::string message = "GET / HTTP/1.1\r\n\r\n";

    client.Send(message);
    std::cout << client.Receive() << std::endl;

    client.Close();
    return 0; 
}