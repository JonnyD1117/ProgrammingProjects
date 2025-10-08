
#pragma once


#include "socket_headers.hpp"
// #include "tcp_exceptions.hpp"
#include "tcp_base.hpp"

#include <string>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <bits/stdc++.h>
#include <vector> 


namespace TCP
{
    class Client : public TcpBase
    {
        public: 
        Client(std::string ip_address, size_t port) : ip_address(ip_address), port(port)
        {
            populate_address_struct();
            socket_fd = create_socket(num_creation_attempts);
        }

        void Bind()
        {
            // Optional - Bind Client Socket to IP Address and TCP Port
            // NOT IMPLEMENTED
            TcpMethodNotImplemented MethodNotImplemented("Client Side Bind Method Has not been Implemented"); 
            throw MethodNotImplemented; 
        }

        void Connect(const int num_attempts=3)
        {
            int connection_status;

            if(socket_fd < 0) { std::cout << "Client Socket was not successfully created!" << std::endl; }

            for(int attempts=0; attempts<num_attempts; ++attempts)
            {
                try
                {
                    connection_status = connect(socket_fd, (struct sockaddr*)&socket_addr, sizeof(socket_addr));

                    if(connection_status == -1) 
                    {   
                        std::cout << "Connection Failed: " << connection_status << std::endl;
                        TcpClientConnectFailed ConnectionFailed("TCP Client Connection Failed: Reattempting now...");
                        throw ConnectionFailed;
                    }
                    break;

                }
                catch(const TcpClientConnectFailed& e)
                {
                    if(attempts == (num_attempts-1))
                    throw std::runtime_error("TCP Client Connection Failed: Attempts at establishing a Connection have failed");
                }   
            }
        }
    
        void Send(std::string message)
        {    
            send_message(message, socket_fd);
        }

        std::string Receive()
        {   
            return receive_message(socket_fd);
        }

        protected:

        int socket_fd; 
        size_t port;
        std::string ip_address;
        struct sockaddr_in socket_addr ;

        void populate_address_struct()
        {
            char* ip_addr_char = strdup(ip_address.c_str());
            socket_addr.sin_family = AF_INET;
            socket_addr.sin_port = htons(port);
            socket_addr.sin_addr.s_addr = inet_addr(ip_addr_char);
        }

    };

    class Server : public TcpBase
    {
        public: 
        Server(std::string ip_address, size_t port) :  ip_address(ip_address), port(port) 
        {
            populate_address_struct();
            s_socket_fd = create_socket(num_creation_attempts);
        }

        void Bind()
        {
            if(bind(s_socket_fd, (struct sockaddr*)&host_addr, sizeof(host_addr))<0)
            {
                std::cout << "Server BIND Failed!" << std::endl;
            }
        }
        
        void Listen()
        {
            if(listen(s_socket_fd, 10) == -1 )
            {
                std::cout << "Server LISTENed Failed." << std::endl;
            }
        }
        
        void Accept()
        {
            int addr_len = sizeof(client_addr);

           c_socket_fd = accept(s_socket_fd, (struct sockaddr*)&client_addr, (socklen_t*)&addr_len);
           socket_vect.push_back(c_socket_fd);

            if(c_socket_fd == -1) { std::cout << "Accept Error" << std::endl; }
        }

        void Send(std::string message) { send_message(message, c_socket_fd); }

        std::string Receive() { return receive_message(c_socket_fd); }

        protected:

        int s_socket_fd, c_socket_fd, port; 
        std::string ip_address;
        struct sockaddr_in host_addr, client_addr; 
        
        void populate_address_struct()
        {
            host_addr.sin_family = AF_INET;
            host_addr.sin_port = htons(port);
            host_addr.sin_addr.s_addr = INADDR_ANY;
        }
    };
}