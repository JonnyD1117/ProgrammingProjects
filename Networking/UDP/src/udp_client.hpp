#include "socket_headers.hpp"

#include <string>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <bits/stdc++.h>
#include <vector> 


namespace UDP
{
    // const int MAX_BUFFER_SIZE = 4096;         // Max Number of Bytes

    class Client
    {
        static const int MAX_BUFFER_SIZE = 128;         // Max Number of Bytes

    public:

        int m_socket_fd; 
        size_t m_port;
        std::string m_ip_address;
        struct sockaddr_in m_server_addr, m_client_addr ;

        char send_buffer[MAX_BUFFER_SIZE] = "hello from Client \0"; 
        char recv_buffer[MAX_BUFFER_SIZE]; 


        Client(std::string ip_addr, size_t port): m_ip_address(ip_addr), m_port(port)
        {
            // Attempt to Create the Socket
            m_socket_fd = socket(AF_INET, SOCK_DGRAM, 0); 

            // Error Handling
            if(m_socket_fd == -1) { std::cout << "TCP Client Socket Creation returned Error" << std::endl; }

            // Filling server information 
            m_server_addr.sin_family = AF_INET; 
            m_server_addr.sin_port = htons(m_port); 
            m_server_addr.sin_addr.s_addr = INADDR_ANY; //inet_addr("8.8.8.8"); 
            
            int n;
            socklen_t len = sizeof(m_client_addr);
            
            sendto(m_socket_fd, send_buffer, sizeof(send_buffer), 0 , (const struct sockaddr *) &m_server_addr,  len); 
                
            n = recvfrom(m_socket_fd, recv_buffer, sizeof(recv_buffer),  0, (struct sockaddr *) &m_client_addr, &len);

            for( size_t idx = 0; idx < n ; idx++)
            {
                char tmp = recv_buffer[idx]; 

                if( tmp == '\0')
                {
                    break;
                }
                else{
                    std::cout << tmp;
                }

                
            }

            std::cout << std::endl;
        
            close(m_socket_fd); 
        }

        ~Client()
        {
            close(m_socket_fd); 
        }

    };

} // end UDP