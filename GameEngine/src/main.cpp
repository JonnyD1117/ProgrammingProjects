#include "Engine.hpp"
#include <iostream>

int main()
{
    // Engine handles GLFW windowing context & calls to Renderer
    OpenGlTutorial::Engine engine;

    // Run Application
    [[maybe_unused]] int exit_code = engine.run();

    return 0;
}