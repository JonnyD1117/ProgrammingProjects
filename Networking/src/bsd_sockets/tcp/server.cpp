/*
 * Simple TCP/IP Server Example
 */

#include "network_headers.hpp"

#define PORT_NUM 80

int main(int argc, char* argv[]) {


    char serv_msg[256] = "You have reached the server";

    int socket_desc;
    struct sockaddr_in server;
    socket_desc = socket(AF_INET, SOCK_STREAM,0);

    if (socket_desc == -1)
    {
        printf("Could not create socket \n");
    }
    else
    {
        printf("Socket has been successfully created \n");
    }


    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT_NUM);


    int status = bind(socket_desc, (struct sockaddr*)&server, sizeof(server));

    if(status == -1)
    {
        printf("Server Socket Bind failed");
    }

    else
    {
        printf("Server Socket Bind succeeded");
    }

    listen(socket_desc, 5);

    int client_socket;
    client_socket = accept(socket_desc, NULL, NULL);


    send(client_socket, serv_msg, sizeof(serv_msg), 0);

    shutdown(socket_desc, 2);

    return 0;
}
