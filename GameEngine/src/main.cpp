#include "Engine.hpp"
#include <iostream>

int main()
{
    // Engine handles GLFW windowing context & calls to Renderer
    OpenGlTutorial::Engine engine;

    // Run Application
    int exit_code = engine.run();

    return exit_code;

    int x = 200;
}