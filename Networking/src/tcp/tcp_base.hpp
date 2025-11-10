
#pragma once

#include "socket_headers.hpp"
#include "tcp_exceptions.hpp"

#include <string>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <bits/stdc++.h>
#include <vector> 

namespace TCP
{
    const int MAX_BUFFER_SIZE = 4096;         // Max Number of Bytes
    
    class TcpBase
    {
        public: 

        virtual void Send(std::string message) = 0; 
        virtual std::string Receive() = 0; 
        
        void Close()
        {
            for (auto fd : socket_vect)
            {
                int status = shutdown(fd, SHUT_RDWR);
                
                if(status == 0)
                {
                    close(fd);
                }
            }
        }

        protected:

        void send_message(std::string message, int socket_fd)
        {    
            message = append_termination_delimiter(message);                                   // Add Deliminator
            size_t message_num_chars = message.length() + 1;                            

            if(message_num_chars <= MAX_BUFFER_SIZE)
            {   
                clear_buffer(send_buffer, MAX_BUFFER_SIZE);                                   // TODO: dynamic buffer size adaptation, E.G> (char msg_buffer[message.length() + 1];)  
                size_t msg_len = message.copy(send_buffer, message_num_chars);                    // NOTE: <string>.length() does not include the NULL (Add +1 to accout for NULL Term) 
                send(socket_fd, send_buffer, msg_len, 0);
            }
            else
            {              
                size_t msg_split_index = 0;                                                  // Index for keeping track of where payload string was split
                size_t num_chars_left = message_num_chars;                                   // Running Tally for how many chars are left to copy into the buffer
                size_t buffer_size = MAX_BUFFER_SIZE;
                size_t num_sends = sends_required(message_num_chars, MAX_BUFFER_SIZE);  
                
                for(int i=0; i < num_sends; ++i)
                {
                    // NOTE: TCP Just needs to send all of the bytes across the network, TCP will keep track of the ordering. 
                    clear_buffer(send_buffer, MAX_BUFFER_SIZE);
                    
                    // Determine the number of characters to be copied to the buffer. 
                    buffer_size = (num_chars_left > MAX_BUFFER_SIZE) ? MAX_BUFFER_SIZE : num_chars_left; 
                    size_t msg_len = message.copy(send_buffer, buffer_size, msg_split_index); 

                    // Book Keeping for Splitting of Message into Buffer sized chunks
                    num_chars_left -= msg_len; 
                    msg_split_index += MAX_BUFFER_SIZE; 

                    // Send the Data over the socket
                    send(socket_fd, send_buffer, msg_len, 0);
                }
            }
        }

        std::string receive_message(int socket_fd)
        {   
            // Uniform Size Data Buffer w/ Null Termination delimiter
            size_t bytes_read;                                          // Number of Bytes Read at each `recv()`
            std::string received_msg;                                   // String representation of entire message
            size_t delimiterPos;                                        // Position of Null Terminated parsed from received buffer

            // Loop Until Null Terminator Delimiter has been detected. 
            while (true) { 
                bytes_read = 0; 
                bytes_read = recv(socket_fd, recv_buffer, MAX_BUFFER_SIZE, 0);

                if (bytes_read <= 0) {
                    // Handle connection closure or error
                    break;
                }

                // Load received char[] into string for processsing
                std::string msg_buffer_str(recv_buffer, bytes_read);

                // Test if Null Terminator Exists Inside of String
                delimiterPos = msg_buffer_str.find('\0');

                // Detect Null Terminator Delimiter 
                if(delimiterPos == std::string::npos)
                {
                    // Null Terminator Not Received Keep Receiving Client Data.
                    received_msg.append(msg_buffer_str);
                    msg_buffer_str.clear();
                    clear_buffer(recv_buffer, sizeof(MAX_BUFFER_SIZE));
                }
                else 
                {
                    // Null Terminator Received Handle & stop receiving from client
                    received_msg.append(msg_buffer_str, 0, delimiterPos);
                    break;
                }
            }
            return received_msg;
        }

        std::vector<int> socket_vect;                    
        const int num_creation_attempts = 3; 
        char send_buffer[MAX_BUFFER_SIZE]; 
        char recv_buffer[MAX_BUFFER_SIZE];

        virtual void populate_address_struct() = 0; 

        int create_socket(int num_attempts) 
        { 
            int socket_fd; 

            for(int attempt_num=0; attempt_num < num_attempts; ++attempt_num)
            {
                try
                {
                    // Attempt to Create the Socket
                    socket_fd = socket(AF_INET, SOCK_STREAM, 0); 
                    socket_vect.push_back(socket_fd);
                    if(socket_fd == -1) { throw TcpClientSocketCreationFailed("TCP Client Socket Creation returned Error"); }
                    break;
                }

                catch(TcpClientSocketCreationFailed& error)
                {   
                    if(attempt_num == (num_attempts -1)) 
                    { 
                        std::string attempt_error = "TCP Client Socket Creation was ReAttempted & failed!";
                        TcpClientSocketCreationReAttemptFailed ReAttemptFailed( attempt_error.c_str());  
                        throw ReAttemptFailed; 
                    }
                }
                catch(TcpClientSocketCreationReAttemptFailed& error)
                {
                    throw std::runtime_error(error.what());
                }
            }   

            return socket_fd;                            
        }

        void clear_buffer(char* buffer, size_t buffer_len)  
        { 
            for(int i=0; i< buffer_len; ++i) buffer[i] = 0;
        }

        size_t sends_required(size_t num_chars_in_message, size_t buffer_size)
        {
            if(num_chars_in_message % buffer_size == 0)
            {
                return (num_chars_in_message / buffer_size);
            }
            return ((num_chars_in_message / buffer_size) + 1);
        }

        std::string append_termination_delimiter(std::string message) 
        {  
            message += '\0'; 
            return message ; 
        }
    };
}
