/**
 * @file Engine.cpp
 * @brief Implementation of the class/functions defined in Engine.hpp
 * @author Jonathan Dorsey
 * @date Creation date: 2025-05-07
 * 
 * This class contains all of the logic for running the Engine and 
 * creating/operation of a rendering window in GLFW
 */


 /*
        Future Ideas to Implement:
            1) Game Config (game engine can understand how to switch between games & assets) Yaml Config?
            2) Scene Manager/Configurator (controls which items to render in current scene )
                2.1) Mesh Manager - Abstraction for handling importing/serialization and rendering of Mesh Objects
                2.2) Camera Manager - 
                2.3) Texture Manager? Don't know whether this is a real thing

        Once you have a Mesh abstraction, your rendering code becomes cleaner, and your 
            renderer can receive the data it needs in a structured form.

            What the renderer should be passed:
                A reference to the Mesh (encapsulating VAO, VBO, EBO)
                The Shader (with uniforms already set, or renderer can help set them)
                The Texture(s) (already bound or managed by a material system)
                The Camera (or its matrix — typically viewProj)
                Possibly a Transform matrix (model matrix)
        NEXT STEPS AFTER CREATING A MESH CLASS... 
        
        Moving VBO/VAO/EBO setup logic out of main
        Creating a high-level object (Mesh) that the renderer can interact with
        Thinking about future scalability (collections of meshes, batching, material systems)
        Once you're comfortable with this layer, you’ll naturally move toward things like:
        A Material class that wraps shader + texture(s)
        A Renderable component that combines Mesh + Material + Transform
        Scene-level submission (e.g., scene.submit(renderer))
    
    */


// sstd
#include <cassert>

// local 
#include "Engine.hpp"


namespace OpenGlTutorial
{

Engine::Engine()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }
}

Engine::~Engine()
{
    glfwTerminate();    // glfw: terminate, clearing all previously allocated GLFW resources.
}

int Engine::run()
{
    // HARD CODE: Test the mesh & rendering in OpenGL
    std::string teaPotPath = "/home/indy/repos/ProgrammingProjects/GameEngine/src/assets/meshes/teapot.obj";
    // m_meshManager.setAssimp(true);
    std::shared_ptr<MeshData>mesh_data = m_meshManager.getMeshfromFile(teaPotPath);  
    
    glEnable(GL_DEPTH_TEST);    // Helps with Z-Shearing

    // // glEnable(GL_CULL_FACE);
    // // glCullFace(GL_BACK);
    // // glFrontFace(GL_CCW);  // default, CCW = front-facing
    // // -----------
    while (!glfwWindowShouldClose(window))
    {   
        // Clear the Renderer Scene
        // - Remove ALL objects from previous scene? (might be inefficient? but clean lol)

        // Handle Wind & Mouse inputs (translate to camera movement)
        // processInput(window);    // Window Controls
        
        // Scene Update 
        // - Update the scene (camera inputs, lights, shaders, textures...etc)

        // Render Scenes
        // -  render.Draw( meshes, camera, lights, shaders, textures...etc) 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Engine::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

} // end namespace OpenGlTutorial