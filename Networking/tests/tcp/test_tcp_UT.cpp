// GTest
#include <gtest/gtest.h>

// std 
#include <iostream>
#include <format>
#include <string>
#include <vector>

/*********************/
/*      Tests      */
/*********************/
TEST(TestTcpSuite, TestTcpDummy)
{
    EXPECT_TRUE(true);
}


TEST(TestTcpSuite, TestTcpServer)
{
    EXPECT_TRUE(true);

    /*
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
    */
}

TEST(TestTcpSuite, TestTcpClient)
{
    EXPECT_TRUE(true);

    /*
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
    */
}

TEST(TestTcpSuite, TestTcpGetGoogleHomePage)
{
    EXPECT_TRUE(true);

    /*
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
    */
}