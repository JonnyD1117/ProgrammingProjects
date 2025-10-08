#include "socket_headers.hpp"
#include <iostream> 
#include <string>
#include "udp.hpp"


int main(int argc, char **argv) 
{
    UDP::Server server("127.0.0.1", 8080);

    return 0; 
}