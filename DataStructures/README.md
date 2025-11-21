# Data Structures & Algorithms
This project is my own personal implemention of C++ STL data structures & algorithms, to better learn the STL. 

## Requirements 

 - CMake >= 3.28 (build system generator)
 - Conan2  (package manager)
 - Make (cli command executor)
 - Ninja (build system)

## Usage Instructions

This project uses a `Makefile` as a quick and dirty scripting mechanism to run long commands; however, the underlying build system of this project is `Ninja`. At this point, I'm assuming that if you're this far, you understand how CMake projects work and could manaually build the project if necessary. This however, is dependent on installing all external dependencies first using the `Conan 2.0` package manager. This project will not build without satisfying the Conan dependencies, as these are used for things like `GTest`. 

### Building the Project
Assuming, you have all the build requirements installed and operating, to build and test this project `cd` into project root directory and execute the following make commands.

```makefile

# Clean all binaries and build artifacts
make clean

# Install Conan2 Dependencies
make deps

# Configure & Build Project CMake
make config build

# Run GTests
make test

# Feeling Adventurous? Do them all at one time!
make clean deps config build test
```

NOTE: These `make` commands are just wrappers around standard Conan and CMake commands that could be run manually, please look at the `Makefile` in the root directory to discovery these commands directly.

## Data Structures Implemented
- [x] Vector 
- [x] Array
- [x] Linked-List
- [ ] Ordered Map
    - [ ] Red/Black Tree
    - [ ] AVL Tree
        - [ ] Binary-Search-Tree
- [ ] Deque
- [ ] Stack 
- [ ] Queue 
    - [ ] Normal Queue 
    - [ ] Priority Queue
- [ ] Forward_list 
- [ ] Unordered Map (hash table)
- [ ] Set
