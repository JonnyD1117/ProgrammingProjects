# OpenGL Game Engine Project

The high level objectives of this repository are ...

1. Learn OpenGL graphics API
2. Learn Computer Graphics through practice
3. Build the skills, structures, and abstraction required to create a basic game/game engine
4. Assuming success above, recreate (and possibly improve) [Danger From The Deep](http://dangerdeep.sourceforge.net).

## Development Requirements

The following requirements are not strictly speaking necessary for this project
to succeed; however, they are a method of forcing me get comfortable with large projects and industry standard
tooling for C++.

- Enforce Cross-Platform Compatibility (at all levels of the project)
- Modern C++ (e.g. C++ 23 or newer)
- Use Clang Compiler (and tools like Clang-Tidy & Clang-Format)
- Use minimal external libraries (STL, OpenGL, GLAD, GLFW, ImGUI...etc.)
- Conan C++ Package Manager (external dependency management)
- CMake Build-System-Generator
- Ninja Build-System
- In-source documentation (document as you code)

## OpenGL, Computer Graphics, & Game Engine Design

The main component of this repo is the code that renders objects on the screen.
The goal is to write a moderately performant C++ renderer/game engine that will enable
me to explor computer graphics and to build skills with.

OpenGL was selected as the graphics API of choice as it has a lot of resource and "everyone"
says that it is the best starting point for learning computer graphics. From my current experience,
only a limited number of constructs will interact directly with OpenGL and it appears that most
of the effort in building a renderer/game engine revolve around building systems and constructs that
to given OpenGL what it wants to renderer a scene.

## Danger From The Deep - Free and Open Source - Simulation Game

The final goal of this project is to clone/improve the FOSS WWII submarine simulator game [Danger From The Deep](http://dangerdeep.sourceforge.net)
(DFTD) that I played as a kid for before I ever had any expectations of being able to actually develop something similar.
While I love this game as is, as a software engineer I have several gripes with the source code and executation
of the project once I forked the repo.

### DFTF Critiques

1. Coherent Build Systems
2. Directory Structure (Renderer & Game Code Structures)
3. Documentation
4. Testing
5. Dependency Management
6. Project Performance, Issue, & Development Tracking
7. Main Program Entry Point


<ins>**Build System:**</ins>

DFTD uses CMake as its build system which is a solid and industry standard choice for any C++
project. However, in my opinion, the way the build system was assembled and constructed yields complex and convoluted
structure in which the intend of the game developer is not clear without a SUPER deep dive into the entire build process.
While I believe that this is a consequence of the nature of homebrew development of this game, I would like to implement
a more standardized implementation of a CMake project that tries to prevent CMake being the barrier to entry for learning
how to build and develop my version of this game.

<ins>**Directory Structre:**</ins>

By far, my current biggest gripe about the original source is how flat the directory structure is. While
I acknowledge that there is no single correct way of designing a project structure, in my opinion, the lack of a meaning directory
hierarchy is extremely detrimental in being able to dissect code and understand what part of the code is responsible for which systems.
Counter point, the idea of directory hierarchy can be taken TOOO far and can cause undesired fragmentation of a project; however, in the case
of DFTD, I feel that there are so many differnt systems which should be structured in a way that makes it clear to devs what that
section of code is responsible for. This makes it hard to understand sub-system architecture and provides no real context or meta-data
to devs to be able to approach the system from a conceptual model and then zoom into technical nuance as they dive into a specifc topic.
I would like to structure my project in a "sensible" way that makes it easy not only understand where files and systems reside, but also "why" they reside there. I would like the grouping of files and libaries to make sense to another developer.

<ins>**Documentation:**</ins>

As I have developed more as a software engineer, I think that I have developed a different sense for the type and purpose
of documentation in a software project. I feel that most devs think of Doxygen and that it is super cool to be able to generate automatic
pdf or web-based docs for their project. While I don't deny this, I think that documentation which just "shows" you code and classes is not
very helpful unless your project is an important dependency that other systems will need to reference. I have found that the "type" of documentation
I find more useful to me is a more akin to a wiki that describes the projects and conceptually breaks down constructs and how they are implemented.
This provides other devs an idea about WHY code is written the way it is. If a developer has a modest amount of competency, they will be able to
look at code and understand at a very basic level what that code is doing, but they might have no idea about WHY that code is doing what its doing
or HOW that code gets integrated into the larger system. If I get that far in developing my version of this game, I will try to address this
issue (as much as is in my power) and document the larger concepts, structures, contexts, and design of why and how things exist how they are.
That is NOT saying that that implementation is correct, but should hopefully give a basis for the current state of the project.

<ins>**Testing:**</ins>

I felt that a subtle but important drawback present in the original project was that (in my opinion), I don't believe the project
was structured, from the beginning, to contain a test framework. I feel that while "testing" is not the end-all-be-all of software developement,
provides confidence (especially in distributed development environments) that systems work as intented. I think that having a place for tests
built into the structure of the project, and a standard framework, methodology, and tooling for testing helps to make a project more maintainable.
The ability to perform unit and integration tests without having to hack it into the sub-structure of a project or clutter up a directory with
test files leads to "possibility" that testing will have a more beneficial outcome on the project.

<ins>**Dependency Management:**</ins>

While the dependencies of the original DFTD was not crazy, I think the project suffered (like a lot of C++) projects,
with the inability to incorporate third-party dependencies into the system without the build system going nuts, or having to write custom setup
scripts that configure the entire system so that it can work. I want to use this project a test run for how I think I will be structuring all
of my C++ projects in the future, and how these projects will interact with dependencies. I don't personally enjoy having to learn how to build
each dependency I need from scratch or installing precompiled binaries. I would much rather have a system similar to Python's virtual environments with PIP that aggregate all of the dependencies into a single spot and let the program reference everything it needs from that spot, instead of
doing the "normal" CMake `install` paradigm. [Conan2](https://docs.conan.io/2/) is a C & C++ package manager, written in Python that
makes managing dependencies "almost" painless in my limited experience. That said, this project will utilize Conan as a way of aggregating
dependencies and enabling CMake to build them into the project. Conan also has the benefit of being cross-platform and enabling this project to
directly install OpenGL & GLAD which is a challange that stops many devs who want to learn computer graphics.

<ins>**Project Tracking:**</ins>

It's not perfect but I would like to self-host my game development on a [Gitea](https://about.gitea.com/) repository.
This enables me to completely own the development and rules without being beholding to the big tech giants, while still providing tools
like "Pull Requests", "Issues", and other project tracking tools, as well as a limited for of CI/CD. Gonna give it a shot. I think that
GitHub, GitLab, or Gitea would all be a better alternative than the SoureForge repository that it currently exists in for the legacy game.

<ins>**DFTD Main Entry-Point:**</ins>

I spend WAY longer that I should have to find the main entry point for this game and which C++ files actually are
responsible for the runtime execution of this game once compiled. I feel like it should be painfully obvious where the `main()` function is
for a game/engine source code. In my version of this project, I would like to make "main entry-points" obvious and clear. My philosophy here
is that good code might ask you to trust an abstraction but will never prevent you from understanding how that abstraction is implemented.
This may sound benign but I have run into issue (both in personal and work projects) where a tool or system will ask you to trust it
instead of making it easy to understand the whole project. Understanding where the `main()` is and making that clear is a small price to pay
for helping others be "able" to self-learn your system without constantly asking where "that" came from or how tf "this" thing even runs.

### DFTF-Reloaded Goals & Features

Assuming that I have been able pull of the massive tasks of creating a functional renderer, game engine, math library,
simulation framework, and video game... here are some of the features I think it would be cool to have. We'll see how
far this ever gets.

- [ ] Clean CMake structure
- [ ] Accurate rendering of Stars
- [ ] Sextant Navigation tool by stars
- [ ] Networked Multiplayer
- [ ] Accurate time of day modeling
- [ ] Dynamic weather (cloud cover, wind, swell...etc.)
- [ ] Capable of being played through a web-browser from server hosted via docker
- [ ] Support Linux, Windows, and MacOS
- [ ] Ability to enable Raytracing
- [ ] Fully model internal submarine
- [ ] FPV ability to explore submarine
- [ ] Submarine Dry dock build and ability to start a campaign from port
- [ ] Airplane simulator
- [ ] Be able to switch between "legacy" DFTD mode (for the OGs) and updated version
- [ ] Entity Component System
- [ ] Material System
- [ ] Basic Animation System
- [ ] Fully supported (internal) simulation framework
- [ ] Create Tooling for Simulation framework to be documented using latex write ups to explain the physics works.
- [ ] Ability to Script and edit game objects via GameEngine without having to hard code everything (think Unity)
- [ ] Upgrade path from OpenGL to Vulkan.
- [ ] Expand the ability for the user to interact directly and control the submarine via the actual sub controls
