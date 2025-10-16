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

        m_vertexVec            .reserve(RESERVE_SIZE);
        m_textureVec           .reserve(RESERVE_SIZE);
        m_normalVec            .reserve(RESERVE_SIZE);
        m_triFaceVec           .reserve(RESERVE_SIZE);
        m_non_triangular_faces .reserve(RESERVE_SIZE);
    }

    std::shared_ptr<MeshData> ObjParser::parse(const std::filesystem::path& mesh_path)
    {
        // Handle File IO
        std::ifstream in { mesh_path };
        std::string line;

        size_t numVerts = 0; 

        /*
            File pass #1:
            - Determine # of Vertices 
            - Determine # of Faces (in file NOTE maybe non-triangular)
            - Use Information to preallocate Data in #2nd pass
        */  

        /*
            File pass #2:
            - 
        */

        MeshData data;

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
            }

            // Parse Obj Text
            if( line_words[0] == "v")
            {
                // Parse Vertices (e.g. v # # # )
                if(line_words.size() == 4)
                {
                    std::array<float,3> state;
                    for(size_t idx=0; idx < 3; idx++ )
                    {
                        size_t wordIdx = idx + 1;                         
                        state[idx] = std::stod(line_words[wordIdx]);
                    }

                    m_vertexVec.push_back(state);

                    m_vertexIdx++;
                }

                continue;
            }
            else if( line_words[0] == "vn")
            {
                // Parse Normals (e.g. vn # # # )
                if(line_words.size() == 4)
                {
                    std::array<float,3> state;
                    for(size_t idx=0; idx < 3; idx++ )
                    {
                        size_t wordIdx = idx + 1; 
                        state[idx] = std::stod(line_words[wordIdx]);
                    }

                    m_normalVec.push_back(state);
                    m_normalIdx++;
                }
                continue;
            }
            else if( line_words[0] == "vt")
            {
                // Parsed Textures (e.g. vt # #) UV coordinates
                if(line_words.size() == 3)
                {
                    std::array<float,2> state;
                    for(size_t idx=0; idx < 2; idx++ )
                    {
                        size_t wordIdx = idx + 1; 
                        state[idx] = std::stod(line_words[wordIdx]);
                    }

                    m_textureVec.push_back(state);
                    m_textureIdx++;
                }

                continue;
            }
            else if( line_words[0] == "f")
            {
                auto to_optional_index = [](const std::string& s) -> std::optional<size_t> {
                        if (s.empty()) return std::nullopt;
                        try {
                            return std::stoul(s);
                        } catch (...) {
                            return std::nullopt;
                        }
                    };

                if( line_words.size() == 4 )
                {
                    for( std::string element : line_words)
                    {
                        std::vector<std::string> tokens = split(element, '/');
                        std::array<std::optional<size_t>,3> face;

                        size_t j = 0; 
                        for(auto token : tokens)
                        {
                            face[j] = to_optional_index(token);
                            j++;
                        }

                        m_triFaceVec.push_back(face);
                    }
                    m_faceIdx++;
                }
                else if ( line_words.size() < 4 )
                {
                    // Malformed Face - Must be a triangle at minimum.
                }
                else
                {
                    // Handle Triangularization
                }                
            }
            else 
            {
                // Character NOT Identified 
                std::cout << "Unidentified Character: " << line << std::endl;
            }            
        }

        m_vertexVec.shrink_to_fit();
        m_normalVec.shrink_to_fit();
        m_textureVec.shrink_to_fit();
        m_triFaceVec.shrink_to_fit();

        std::cout << "Print Mesh File Stats:" << std::endl;

        std::cout << std::format("Num Vertex Lines: {}", m_vertexVec.size()) << std::endl;
        std::cout << std::format("Num Normal Lines: {}", m_normalVec.size()) << std::endl;
        std::cout << std::format("Num Texture Lines: {}", m_textureVec.size()) << std::endl;
        std::cout << std::format("Num Triangular Face Lines: {}", m_triFaceVec.size()) << std::endl;
        std::cout << std::format("Num Non-Triangular Face Lines: {}", m_non_triangular_faces.size()) << std::endl;

        // Process the Face Vector to construct "MeshVertex"
        std::vector<MeshVertex> m_meshVertexVec {};
        
        m_meshVertexVec.reserve(m_triFaceVec.size());

        for ( auto face : m_triFaceVec )
        {
            size_t vertIdx = 0;
            size_t textIdx = 0; 
            size_t normIdx = 0; 

            m_meshVertexVec.emplace_back(m_vertexVec[vertIdx], m_textureVec[textIdx], m_normalVec[normIdx]);
        }

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