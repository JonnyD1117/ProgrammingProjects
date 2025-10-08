/**
 * @file ObjParser.cpp
 * @brief Implementation of the class/functions defined in obj_parser.hpp
 * @author Jonathan Dorsey
 * @date Creation date: 2025-05-12
 * 
 */

#include "obj_parser.hpp"


namespace OpenGlTutorial
{
    ObjParser::ObjParser(std::string mesh_path) : m_path {mesh_path}
    {
        // Detemine Maximum Size of File to Preallocate Parsing Arrays
        preallocateResources();
    }

    void ObjParser::parse()
    {
        try
        {
            // Check if file Exists
            if (!std::filesystem::exists(m_path)) { throw std::runtime_error("OBJ Mesh Parser Failed to Load File - File Does NOT exist!"); }
            
            // Create FileStream 
            std::ifstream file (m_path);

            // Read File Line-by-Line
            std::string line; 

            std::vector<std::string> attribs { "v", "vt", "vn", "f" };

            // Loop over every line in the file
            while(std::getline(file, line))
            {
                // convert line string into stringstream
                std::stringstream ss{line};
                char delimiter = ' ';
                std::string tmp;

                std::vector<std::string> line_words;

                // Parse Line and delimite by space
                while(std::getline(ss, tmp, delimiter))
                {
                    if(!tmp.empty())
                    {
                        line_words.push_back(tmp);
                    }
                }

                if(line_words.size() ==0) { continue;}
                // Extract First Token from Vectors
                std::string firstToken = line_words.at(0);

                // Make Sure First Word is a TOKEN
                if(!line_words.empty() && std::find(attribs.begin(), attribs.end(), firstToken) != line_words.end())
                {
                    // check first token for type                     
                    if (firstToken == "v")
                    {
                        parseVertices(line_words);
                    }
                    else if (firstToken == "vt")
                    {
                        parseTextures(line_words);
                    }
                    else if (firstToken == "vn")
                    {
                        parseNormals(line_words);
                    }
                    else if (firstToken == "f") 
                    {
                        parseFaces(line_words);
                    }
                    else 
                    {
                        // Do Nothing
                    }
                }
            }

            // Close File Stream
            file.close();

            // Shrink to Fit Before Parsing into Vertex Data
            m_vertexCoords .shrink_to_fit();
            m_textureCoords.shrink_to_fit();
            m_normals      .shrink_to_fit();
            m_faces        .shrink_to_fit();

            // Using face Definitions populate OpenGL Buffers
            populateBufferFromFace(m_vertexBufferData, m_indexBufferData);   
            
            // Parse into Vertex structure
            //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS        //
            // -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, // Bottom side

            if (DEBUG_PARSER)
            {
                std::cout << "Number of Vertex Coordinates = " << m_vertexCoords.size()  << std::endl;
                std::cout << "Number of Texture Coordinates = "<< m_textureCoords.size() << std::endl;
                std::cout << "Number of Normals = "            << m_normals.size()       << std::endl;
                std::cout << "Number of Faces = "              << m_faces.size()         << std::endl;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
}