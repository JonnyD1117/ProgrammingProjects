#include "socket_headers.hpp"
#include <iostream> 
#include <string>
#include "tcp.hpp"

int main() 
{
    // std::string message = "GET / HTTP/1.1\r\n\r\n";

    TCP::Server server("127.0.0.1", 8080);

    server.Bind();
    server.Listen();
    server.Accept();
    int ctr =0; 
    
    std::string msg_recv;
    std::string message; 

    while(msg_recv != "exit")
    {
        message.clear();
        message = "<Server Response>: ";
        msg_recv.clear();
        msg_recv = server.Receive();
        std::cout << msg_recv << std::endl;

        message += msg_recv; 
        server.Send(message);
    }
    
    server.Close();
    
    return 0; 
}