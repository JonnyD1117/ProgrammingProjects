#include "socket_headers.hpp"
#include <iostream> 
#include <string>
#include "udp.hpp"


int main(int argc, char **argv) 
{
    UDP::Client client("192.168.0.78", 8080);
    return 0; 
}