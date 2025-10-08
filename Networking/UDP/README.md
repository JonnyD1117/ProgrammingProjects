# TCP Client/Server 

The goal of this project is to understand the basics of a TCP/IP client and server by building one from scratch. This TCP/IP client/server are not attempting to compete with any real world solution; however, are intended to be learning experience to understand the basics of socket based networking between Unix-like machines. This project is implmenent in C++, using CMake and Make to build the project. 

## Export Library Target
While the direct goal of this project is to implement the TCP/IP stack in isolation, there is a non-zero chance that I would like to use the code in this project for other learning/micro projects that I am interested in. To make the process of using the code in this project as painless as possible I am going to export CMake targets OR generic C/C++ style library file which can be linked directly with any application that wishes to utilize this TCP/IP implementation. 

The goal with this structure is to allow implementations to be contained within specific projects but to allow the `4_Libraries` directory to symlink to libraries (e.g. TCP library). This would allow for a single implementation to be maintained locally but allow other projects to import that library from a standard location. 
