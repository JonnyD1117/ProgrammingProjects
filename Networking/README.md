# Networking 

This project is my small attempt at creating a C++ implementations of a few socket-based networking 
protocols. 

### TCP & UDP

The code for both TCP & UDP are simple attempts at creating a C++ wrappers for hooking into the 
socket layer provided my the Linux Kernel. These libraries were only intended to run on BSD sockets
and soo this code will not work on Windows. 

### HTTP

The code for this HTTP server/client is a learning project to help me become better at the fundamentals
of parsing text. This project utilizes the TCP libary from the previous project as the actual transport
layer, upon which it builds its application layer.