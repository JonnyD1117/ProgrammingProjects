# Programming Projects 

This repo is a collection of small projects for demonstration.

## Requirements
 - GNU/Linux (I am running Ubuntu 24.04 personally)
 - C++ Clang Compiler that supports `C++ 23` 
 - CMake Version 3.28 or newer
 - Conan2 Package Manager

## Projects 
 - Data Structures & Algorithms in C++ 
   - Structures
     - Array
     - Linked List
     - Binary Search Tree
     - Vector
 - Networking
   - TCP & UDP 
   - HTTP 
 - GameEngine (using OpenGL)
 - 6502 CPU Emulator

## Building Projects 

### Conan 2 C++ Package Manager
This repo uses `Conan 2` as the package manager to wrangle the correct version of external libraries required to support the different C++ projects it contains. The reason for opting for Conan is that by an large most packages I would want to use have a Conan recipe already made for it, and after the headache of installing conan, using Conan is a very simple and provides a uniform way for CMake to reliably grab dependecies that doesn't involve `FETCH_CONTENT`. 

### Configuring, Building, & Running Projects
While it maybe considered unorthodox, I personally fine the `Makefiles` make great simple script runners. By utilizing CMake targets, I can quickly invoke dependency installation, cmake configuration & building, and even running and testing C++ executables very simple.

```make
# Install External Dependencies via Conan2
make install_deps

# Configure CMake
make config

# Build/Compile C++ Project
make build
```


