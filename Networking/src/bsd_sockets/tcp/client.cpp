/*
 * BSD Socket Client In C++
 */

// std
#include <iostream>
#include <print>
#include <format>
#include <string>

// local
#include "network_headers.hpp"


int main(int argc, char* argv[]) 
{

    int socket_desc;
    struct sockaddr_in server;

    socket_desc = socket(AF_INET, SOCK_STREAM,0);

    if (socket_desc == -1)
    {
        printf("Could not create socket \n");
    }
    else
    {
        printf("Client Socket has been successfully created \n");
    }


    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    int connection_status = connect(socket_desc, (struct sockaddr *)&server, sizeof(server));

    // Connect to remote server
    if(connection_status == -1)
    {
        puts("connection error");
        return 1;
    }

    puts("Connection Established");

    char resp[256];
    recv(socket_desc, &resp, sizeof(resp), 0);

    printf("%s", resp);

    shutdown(socket_desc, 2);
    return 0;
}
