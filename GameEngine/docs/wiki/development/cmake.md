# CMake Development 

This project uses CMake as it's primary build system configurator and follows the following principles. 

1. CMakeLists.txt files "should" (in most cases) ONLY operate on their subtrees 
2. Avoid CMake MACROs as these are confusing and almost impossible to debug (unless there is NO other way of building the system correctly)
