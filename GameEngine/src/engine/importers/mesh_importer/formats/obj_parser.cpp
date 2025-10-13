/**
 * @file obj_parser.hpp
 * @brief File defines class the concept of a OBJ file parser for mesh creation.
 * @author Jonathan Dorsey 
 * @date Creation date: 2025-05-12
 * 
 * OBJ files are a very easy way to create mesh geometry. This is a class attempts
 * to implement a VERY basic version of a OBJ file parser (for s & g) to prove that 
 * I understand the concept of loading mesh elements in from a well known 3D model 
 * object exchange format.
 */


// local 
#include "obj_parser.hpp"

namespace OpenGlTutorial
{
    ObjParser::ObjParser()
    {
        // Pre-allocate Vectors for Effiency
        vertices.reserve(RESERVE_SIZE);
        indices.reserve(RESERVE_SIZE);
    }

    std::shared_ptr<MeshData> ObjParser::parse(const std::filesystem::path& mesh_path)
    {
        // Handle File IO
        std::ifstream in { mesh_path };
        std::string line;

        while(std::getline(in, line))
        {
            // Skip Comments && Empty Lines
            if(line[0] == '#' || line == "")
            {
                continue;
            }

            // Split Line by Whitespace
            std::stringstream ss { line };
            std::string word;
            std::vector<std::string> line_words;

            while( ss >> word )
            {
                line_words.push_back(word);

                // std::cout << word << std::endl;
            }

            if( line_words[0] == "v")
            {
                // Parse Vertices (e.g. v # # # )
                // std::cout << line << std::endl;
            }
            else if( line_words[0] == "vn")
            {
                // Parse Normals (e.g. vn # # # )
                // std::cout << line << std::endl;
            }
            else if( line_words[0] == "vt")
            {
                // Parsed Textures (e.g. vt # #) UV coordinates
                // std::cout << line << std::endl;
            }
            else if( line_words[0] == "f")
            {
                // Parsed Face Definitions
                // std::cout << line << std::endl;

                // if(line_words.size() > 4)
                // {
                //     // Non-Triangular Face (Must be triangularize)
                // }
                // else 
                // {
                    
                // }
                
            }
            else 
            {
                // Character NOT Identified 
                std::cout << "Unidentified Character: " << line << std::endl;
            }

            

            

            
        }

        // Triangularize ALL Faces 

        // Handle Vertex Normals (including for FLAT shading)



        

        /*  
            Rules:
            1) Lines starting with '#' are commented
            2) OBJ can use .mtl materials
            3) Character 'g' is a group selector
        */

        /*  
           Parse Faces: 

           1) Verts Only                 ( e.g. f v1 v2 v3 )
           2) Verts & Textures           ( e.g. f v1/vt1 v2/vt2 v3/vt3 )
           3) Verts, Textures, & Normals ( e.g. f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 )
           4) Verts & Normals            ( e.g. f v1//vn1 v2//vn2 v3//vn3 )

           Triangularize Non-Triangle Faces

           Computer "normal" depending on whether smooth shading is ON or OFF

        */
        return std::make_shared<MeshData>();
    }
}