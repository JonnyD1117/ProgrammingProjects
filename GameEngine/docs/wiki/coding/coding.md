# Coding Structure, Standards, & Best Practices

This project has been written in `C++23` to force myself to be able to learn a modern style of C++,
with modern tools, features, and structures that any modern coding project would incorporate.

## Quick Reference

- [Building Project](./building.md)
- [Coding Practices & Standards](./best_practices_and_standards.md)

___

## Third-Party Dependencies

While this project attempts to create as much as it can from scratch, it is inevitable that it will
require third-dependencies to build

## Compiler, Build-System Generator, & Build System

### Compiler: Clang++

Clang++ is a C++ compiler built using [LLVM](https://llvm.org/). While `gcc` (GNU C Compiler) can be used,
Clang is considered by most to be a more modern, reliable, and developer friendly compiler. I made the choice
to use this compiler as a way of forcing myself to integrate into a Clang-based project so that I could personally
evaluate the merits of this compiler.

### Build-System-Generator: CMake

This project uses the CMake as its `build-system-generator`. This means that CMake functions as a cross-platform
intermediary which can tie into several different build systems. This means that we are not tied down into a single
computer architecture or operating system, so l

### Build-System: Ninja

[Ninja](https://ninja-build.org/) is a modern C/C++ build system that focuses on speed of compilation, parrallelism,
and being small and lightweight. While I usually use Unix Makefiles, I also decided to choose to use Ninja as a way
of testing out its merits, against my previous experience with GNU Makefiles.

## Dependency Managment: Conan

After many years of working only on smaller sized projects, I have started to realize the importance of having a
method of integrating dependencies into a project so that the project and quickly and simply add new functionality
from libraries that already exist.

In my experience with CMake-based projects, this usually meansing installing
pre-built binaries OR building dependencies from source and installing them system-wide so that CMake package
management could find and link with them. BOTH of these options are kind of horrible and manual approaches.
Since I have been exposed to [Conan](https://conan.io/) I have begun to use it in all of my projects. It provides
a package management system that is more like python's `pip install -r requirements.txt` system. Enabling declarative
configuration of dependencies from a repository.

## Linting & Auto-Formatting: Clang-Tidy & Clang-Format

I would like this project to have some standard set of tools to be able to produce consistent and clear code without
requiring myself (or others) to have to manually maintain everything. Additionally this will give me a chance to
experience for myself how these tools with in comparison with tools that I have previously used.

This project will be using `clang-tidy` as its' linter to make sure that syntax and sematics of the code are inline with
best practices in modern C++. Additionally, it will be using `clang-format` as its auto-formatting tool. Both of these,
have been integrated directly into my VSCode IDE; however, the configuration files for these are standard and can be hooked
up in any fashion that a developer would prefer for their own development environment and setup.

[Clang Tidy & Format Intro](https://lpc.events/event/7/contributions/803/attachments/660/1213/Using_clang-tidy_and_clang-format.pdf)

## Google Test Framework

One of the features that I felt was missing from the Danger from the Deep repository was a standardized methodology for creating
and implementing Unit Test. I have selected [GoogleTest](https://google.github.io/googletest/) as the testing framework for this
project since it is fairly common in the C++ industry and is well understood and supported. I think that having a location and
template for creating tests will not only be helpful but will encourage development practices.
