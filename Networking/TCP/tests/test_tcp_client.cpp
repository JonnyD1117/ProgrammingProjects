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
    // TCP::Client client("127.0.0.1", 8080);
    
    client.Connect(); 

    std::cout << "Write something... " << std::endl;
    
    while(1)
    {
        std::string message;
        std::getline (std::cin,message);
        if (message == "exit") { break; }
        client.Send(message);
        std::cout << client.Receive() << std::endl;
    }

    client.Close();
    return 0; 
}