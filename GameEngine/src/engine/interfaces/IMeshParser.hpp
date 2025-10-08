/**
 * @file IMeshParser.hpp
 * @brief Interace to define a Mesh Parser.
 * @author Jonathan Dorsey 
 * @date Creation date: 2025-05-27
 * 
 */

#pragma once 


// std 
#include <iostream>
#include <vector>
#include <string> 

// opengl
#include <glad/glad.h>
#include <glm/glm.hpp>


namespace OpenGlTutorial
{
    class IMeshParser
    {
        public:
        IMeshParser()=default;
        virtual ~IMeshParser()=default;

        // Parse Mesh file into Mesh Object 
        void virtual parse( const std::string& meshPath) = 0;      
        
        /* NOTE: Passing mesh into parser method enables
        same parser to be used multiple times without 
        reconstruction of parser object.
        */
    };
}