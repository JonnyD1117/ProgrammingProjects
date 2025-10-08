# OpenGL Game Engine

The objective of this repository is ...

1. Learn OpenGL & Computer Graphics
2. Build the skills & structure to create a basic game & game engine
3. Use this project as the basis for a [Danger From The Deep](http://dangerdeep.sourceforge.net) clone/refresh

## Game Engine & Rendering

The main component of this repo is the code that renders objects on the screen.
The goal is to write a moderately performant C++ renderer/game engine that will enable
me to explor computer graphics and to build skills with.

OpenGL was selected as the graphics API of choice as it has a lot of resource and "everyone"
says that it is the best starting point for learning computer graphics. From my current experience,
only a limited number of constructs will interact directly with OpenGL and it appears that most
of the effort in building a renderer/game engine revolve around building systems and constructs that
to given OpenGL what it wants to renderer a scene.

That being said, the complexity of a renderer/game engine really has to be capped at some level of
realistic level to be of any use or to actually be completed. The following are the requirements and
capabilities that I would like this system to possess.

## Danger From The Deep - Free and Open Source - Simulation Game

The final goal of this project is to clone/improve the FOSS WWII submarine simulator game [Danger From The Deep](http://dangerdeep.sourceforge.net)
(DFTD) that I played as a kid for before I ever had any expectations of being able to actually develop something similar.
While I love this game as is, as a software engineer I have several gripes with the source code and executation
of the project once I forked the repo. Instead of trying to modernize DFTF, I decided to try and learn how to build
a large C++ project, computer graphics, simulation framework, and video game at the same time.

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
