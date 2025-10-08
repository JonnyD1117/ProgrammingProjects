# C++ Best Practices & Standards

___

## Naming Convention

## File Extension

In this project, I want to be consistent in how I name my files and in how they are used.
While it is an arbitrary preference, I feel that when programming in C++, source files
should end with `.cpp` extension and that header files should end with `.hpp` extensions.

While I am aware that using other extensions will not break the code, I feel that it is missing
and opportunity to encode "meta-data" about the system into the general context of the project.
In other teams I have worked with, `.cc` & `.cpp` or `.h` & `.hpp` files have been interchanged
without any decernable reason. I feel that establishing conventions helps to create meta-data
about the project that is helpful to developers. In this case, I feel that C files benefit from
using `.c` & `.h` extensions while C++ project benefit from being labels `.cpp` & `.hpp`. This
not only removes ambiguity from what type of file a developer is working with, but it also
removes the burden of "having to choose" from the developer. It is a simple and effective convention
that provides clarity at effectively no-cost to the user/maintainer.

## C++ Source & Header Doc String

```cpp
/**

* @file Engine.cpp
* @brief Implementation of the class/functions defined in Engine.hpp
* @author Jonathan Dorsey
* @date Creation date: 2025-05-07
*
* This class contains all of the logic for running the Engine and
* creating/operation of a rendering window in GLFW
 */
```

```cpp
/**

* @file Engine.hpp
* @brief Engine class to run OpenGL tutorial. Handles functions like GLFW setup.
* @author Jonathan Dorsey
* @date Creation date: YYYY-MM-DD
 */
```
