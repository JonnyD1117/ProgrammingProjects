/**
 * @file Engine.cpp
 * @brief Implementation of the class/functions defined in Engine.hpp
 * @author Jonathan Dorsey
 * @date Creation date: 2025-05-07
 * 
 * This class contains all of the logic for running the Engine and 
 * creating/operation of a rendering window in GLFW
 */

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
    //########################################//
    //            Light Shader                //
    //########################################//
    std::string lightVertShaderPath = shader_path  + "light.vert";
    std::string lightFragShaderPath = shader_path  + "light.frag";

    // Create Shader for light objects
    Shader lightShader (lightVertShaderPath, lightFragShaderPath);

    // Light Box 
    glm::vec4 lightColor = glm::vec4(1.f, 0.0f,1.0f,1.0f);
    glm::vec3 lightPos   = glm::vec3(2.0f, 0.8f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);  // Move the light object where the lightPos is defined in world coords?

    // Bind the Light Shader & Add Uniforms
    // lightShader.Bind();
    lightShader.setMatrix4f("model", lightModel);
    lightShader.setVect4f("lightColor", lightColor);

    std::vector<GLfloat> lightVertices =
    { //     COORDINATES     //
        -0.1f, -0.1f,  0.1f, 
        -0.1f, -0.1f, -0.1f,
         0.1f, -0.1f, -0.1f,
         0.1f, -0.1f,  0.1f,
        -0.1f,  0.1f,  0.1f,
        -0.1f,  0.1f, -0.1f,
         0.1f,  0.1f, -0.1f,
         0.1f,  0.1f,  0.1f
    };

    lightVertices.shrink_to_fit();

    std::vector<GLuint> lightIndices =
    {
        0, 1, 2,
        0, 2, 3,
        0, 4, 7,
        0, 7, 3,
        3, 7, 6,
        3, 6, 2,
        2, 6, 5,
        2, 5, 1,
        1, 5, 4,
        1, 4, 0,
        4, 5, 6,
        4, 6, 7
    };


    lightIndices.shrink_to_fit();

    // Light "box" mesh
    Mesh lightMesh(lightVertices, lightIndices);
    lightMesh.addAttribute(0, 3); // Vertex Color
    lightMesh.buildVAO();

    //########################################//
    //            Object Shader               //
    //########################################//
    std::string vertShaderPath = shader_path  + "default.vert";
    std::string fragShaderPath = shader_path  + "default.frag";
    std::string texturePath    = texture_path + "brick.jpeg"; 

    // Instantiate Shader (from vertex & fragment files)
    Shader shader (vertShaderPath, fragShaderPath);

    glm::vec3 scale = glm::vec3(0.025f, 0.025f, 0.025f);
    // glm::vec3 scale = glm::vec3(1.0f);

    glm::vec3 pyramidPos = glm::vec3(0.0f,0.0f,0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);
    shader.setMatrix4f( "model", pyramidModel, scale);

    glm::vec4 baseColor = glm::vec4(.20f, 0.8f,1.0f,1.0f);
    shader.setVect4f("baseColor", baseColor);


    std::string path = "src/assets/meshes/teapot.obj";
    // std::string path = "src/assets/meshes/tree.obj";
    
    // OpenGlTutorial::ObjParser parser{path};
    // parser.parse();

    std::string mesh_t = "obj";
    std::unique_ptr<IMeshParser> parser = MeshParserFactory::create("obj");

    // std::vector<GLfloat> vertices = parser.getVertexBuffer();
    // std::vector<GLuint>  indices  = parser.getIndexBuffer();


    // Vertices coordinates
    std::vector<GLfloat> vertices =
    { //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
        -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, // Bottom side
        -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, 1.0f, 0.0f, // Bottom side
         0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, 1.0f, 0.0f, // Bottom side
         0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 1.0f, 0.0f, // Bottom side

        -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
        -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
         0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

        -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
         0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
         0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

         0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      -0.8f, -0.5f,  0.0f, // Right side
         0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      -0.8f, -0.5f,  0.0f, // Right side
         0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      -0.8f, -0.5f,  0.0f, // Right side

         0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -0.5f,  -0.8f, // Facing side
        -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -0.5f,  -0.8f, // Facing side
         0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, -0.5f,  -0.8f  // Facing side
    };

    // Indices for vertices order
    std::vector<GLuint> indices =
    {
        0, 1, 2, // Bottom side
        0, 2, 3, // Bottom side
        4, 6, 5, // Left side
        7, 9, 8, // Non-facing side
        10, 12, 11, // Right side
        13, 15, 14 // Facing side
    };

    // Pyramid Mesh
    Mesh mesh(vertices, indices);
    mesh.addAttribute(0, 3); // Vertex Position
    // mesh.addAttribute(1, 3); // Vertex Color
    // mesh.addAttribute(2, 2); // Texture Coords
    mesh.addAttribute(3, 3); // Normals 
    mesh.buildVAO();

    //########################################//
    //            Render Classes              //
    //########################################//
    Texture texture(texturePath,GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    texture.texUnit(shader, "tex0", 0);

    Renderer renderer;
    Camera camera(SRC_WIDTH, SRC_HEIGHT, glm::vec3(0.0f, 0.0f, 8.0f));

    glEnable(GL_DEPTH_TEST);

    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    // glFrontFace(GL_CCW);  // default, CCW = front-facing
    // -----------
    while (!glfwWindowShouldClose(window))
    {   
        // Clear the Renderer Scene
        renderer.Clear();

        // Handle Wind & Mouse inputs (translate to camera movement)
        processInput(window);
        camera.Inputs(window);

        // Update Camera Parameters (e.g. Create Camera Matrix --- proj*view matrix)
        camera.updateMatrixParams(45.0f, 0.1f, 100.0f);   // args: 1) FOV, 2) NearFieldClip, 3) FarFieldClip, 

        // Bind/Active this Shader
        camera.setMatrixUniform  (shader, "camMatrix");
        camera.setPositionUniform(shader, "camPos"   );
        shader.setBool("tex0", 0);

        // Render Pyramid
        renderer.Draw(mesh, shader, texture);       

        // Render Light Box
        camera.setMatrixUniform  (lightShader, "camMatrix");
        renderer.Draw(lightMesh, lightShader);
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Delete ALL Shaders in Scenes
    shader.Delete();
    lightShader.Delete();

    return 0;
}

/*
        Once you have a Mesh abstraction, your rendering code becomes cleaner, and your 
        renderer can receive the data it needs in a structured form.

        What the renderer should be passed:
            A reference to the Mesh (encapsulating VAO, VBO, EBO)
            The Shader (with uniforms already set, or renderer can help set them)
            The Texture(s) (already bound or managed by a material system)
            The Camera (or its matrix — typically viewProj)
            Possibly a Transform matrix (model matrix)
*/


/*
    NEXT STEPS AFTER CREATING A MESH CLASS... 
    
    Moving VBO/VAO/EBO setup logic out of main
    Creating a high-level object (Mesh) that the renderer can interact with
    Thinking about future scalability (collections of meshes, batching, material systems)
    Once you're comfortable with this layer, you’ll naturally move toward things like:
    A Material class that wraps shader + texture(s)
    A Renderable component that combines Mesh + Material + Transform
    Scene-level submission (e.g., scene.submit(renderer))
*/

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

}