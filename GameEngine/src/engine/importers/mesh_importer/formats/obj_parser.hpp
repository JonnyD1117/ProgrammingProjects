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

#pragma once 

// std
#include <algorithm>
#include <deque>
#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <iostream>
#include <optional>
#include <ranges>
#include <sstream>
#include <string>
#include <unordered_map> 
#include <vector>



// opengl
#include <glad/glad.h>
#include <glm/glm.hpp>

// engine
#include "engine_interfaces.hpp"
#include "MeshData.hpp"
#include "MeshTypes.hpp"

// local 
#include "obj_types.hpp"


namespace OpenGlTutorial
{
    class ObjParser : public virtual IMeshParser
    {
        public: 

        //******************************//
        //  Constructors & Destructors  //
        //******************************//
        ObjParser();
        virtual ~ObjParser()=default;

        //******************************//
        //  Public Methods              //
        //******************************//
        virtual std::shared_ptr<MeshData> parse(const std::filesystem::path& mesh_path) override; 

        private:

        std::vector<std::string> split(const std::string& str, char delimiter) {
            std::vector<std::string> tokens;
            std::stringstream ss(str);
            std::string item;

            while (std::getline(ss, item, delimiter)) {
                tokens.push_back(item);
            }
            return tokens;
        }

        void summarize_mesh()
        {
            std::cout << "Print Mesh File Stats:" << std::endl;
            std::cout << std::format("Num Vertex Lines: {}", m_vertexVec.size()) << std::endl;
            std::cout << std::format("Num Normal Lines: {}", m_normalVec.size()) << std::endl;
            std::cout << std::format("Num Texture Lines: {}", m_textureVec.size()) << std::endl;
            std::cout << std::format("Num Triangular Face Lines: {}", m_triangular_faces.size()) << std::endl;
            std::cout << std::format("Num Non-Triangular Face Lines: {}", m_polygonal_faces.size()) << std::endl;

            std::cout << "#############################" << std::endl;
            std::cout << std::format("FACE INDICES: {}", m_faceIdx ) << std::endl;
        }

        static inline float string_to_float ( const std::string& input  )
        {
            return std::stof( input );
        }

        void parse_geometry_vert( std::deque<std::string>& space_delim_line )
        {
            // Remove Token Identifier 
            space_delim_line.pop_front();

            // Parse Vertices (e.g. v # # # )
            if( space_delim_line.size() == 3 )
            {
                std::array<float,3> state;
                std::transform( space_delim_line.begin(), space_delim_line.end(), state.begin(), string_to_float );

                m_vertexVec.push_back(state);
                m_vertexIdx++;
            }
            else 
            {
                throw std::runtime_error( "" );
            }
        }

        void parse_texture_vert( std::deque<std::string>& space_delim_line )
        {   
            // Remove Token Identifier 
            space_delim_line.pop_front();

            // Parse Vertices (e.g. vt # # # )
            if( space_delim_line.size() == 2 )
            {
                std::array<float,2> state;
                std::transform( space_delim_line.begin(), space_delim_line.end(), state.begin(), string_to_float );

                m_textureVec.push_back(state);
                m_textureIdx++;
            }
            else 
            {
                throw std::runtime_error( "" );
            }
        }

        void parse_normal_vert( std::deque<std::string>& space_delim_line )
        {
            // Remove Token Identifier 
            space_delim_line.pop_front();

            // Parse Vertices (e.g. vn # # # )
            if( space_delim_line.size() == 3 )
            {
                std::array<float,3> state;
                std::transform( space_delim_line.begin(), space_delim_line.end(), state.begin(), string_to_float );

                m_normalVec.push_back(state);
                m_normalIdx++;
            }
            else 
            {
                throw std::runtime_error( "" );
            }
        }

        void parse_point_element( std::deque<std::string>& space_delim_line )
        {
            throw std::runtime_error("ObjParser::parse_point_element() - Not implemented");
        }

        void parse_line_element( std::deque<std::string>& space_delim_line )
        {
            throw std::runtime_error("ObjParser::parse_line_element() - Not implemented");
        }

        void parse_face_element( std::deque<std::string>& space_delim_line )
        {
            // Remove Token Identifier 
            space_delim_line.pop_front();

            const size_t num_face_verts = space_delim_line.size();

            if( num_face_verts < 3 )
            {
                throw std::runtime_error( "ObjParser::parse_face_element(): Cannot Parse face with <3 vertices!" );
            }

             // Create Face Object
            ObjMesh::ObjFace face;

            // Iterate Over Each Vertex Definition String
            for(std::string& ident  : space_delim_line)
            {  
                // Extract V, VT, VN data from string
                ObjMesh::FaceVertData face_vert_data = parse_face_string( ident );

                // face_vert_data.print_data();
                    
                face.insert_face_data( face_vert_data );
            }

             // Append Face to Triangular or Polygonal Faces Vectors
            if( num_face_verts == 3 )
            {    
                face.print();
                m_triangular_faces.push_back( face );
            }
            else 
            {
                m_polygonal_faces.push_back( face );
            }

            m_faceIdx++;
        }

        void parse_group_element( std::deque<std::string>& space_delim_line )
        {
            throw std::runtime_error("ObjParser::parse_group_element() - Not implemented");
        }

        void parse_object_element( std::deque<std::string>& space_delim_line )
        {
            throw std::runtime_error("ObjParser::parse_object_element() - Not implemented");
        }

        void data_sizing_pass( const std::filesystem::path& mesh_path );

        void data_extraction_pass( const std::filesystem::path& mesh_path );

        ObjMesh::FaceVertData parse_face_string( std::string& identifier )
        {
            // Parsing State Machine Initialization
            ObjMesh::FaceParsingState state = ObjMesh::FaceParsingState::VERT;

            // Temporary Storage Variables
            int geo = 0; 
            std::optional<int> text = std::nullopt;
            std::optional<int> norm = std::nullopt;

            // Temporary Parsing Variable
            std::string temp = "";

            std::vector<size_t> seperator_indices; 

            // Iterate char-by-char
            for( auto c : identifier ) 
            {
                if( c == '/' )
                {
                    seperator_indices.push_back( c );
                }
            }
            seperator_indices.shrink_to_fit();

            if( seperator_indices.empty() )
            {
                geo = std::stoi( identifier );
            }
            else 
            {
                // V/VT
                if( seperator_indices.size() == 1 )
                {
                    geo  = std::stoi( identifier.substr( 0, seperator_indices[0] ) );
                    text = std::stoi( identifier.substr( seperator_indices[0], identifier.size() ) );
                }
                // V/VT/VN
                else if ( seperator_indices.size() == 2 )
                {
                    geo  = std::stoi( identifier.substr( 0, seperator_indices[0] ) );
                    text = std::stoi( identifier.substr( seperator_indices[0], seperator_indices[1] ) );
                    norm = std::stoi( identifier.substr( seperator_indices[1], identifier.size() ) );
                }
            }

            return ObjMesh::FaceVertData( geo, text, norm );
        }

        void triangularize_faces();

        void construct_mesh_data();


        size_t m_faceIdx    {0};
        size_t m_vertexIdx  {0};
        size_t m_normalIdx  {0};
        size_t m_textureIdx {0};

        size_t m_nonTriFaceIdx {0};
        
        std::vector<std::array<float,3>> m_vertexVec            {};
        std::vector<std::array<float,2>> m_textureVec           {};
        std::vector<std::array<float,3>> m_normalVec            {};
        std::vector<ObjMesh::ObjFace>    m_triangular_faces     {};
        std::vector<ObjMesh::ObjFace>    m_polygonal_faces      {};

        std::vector<MeshVertex> vertices; 
        std::vector<size_t>     indices;

        bool isFlat { false };

        // Flags 
        bool triangulation_required {false};

        // OBJ Vertex Data Sizes
        size_t m_num_geo_vert                     {0u};
        size_t m_num_text_vert                    {0u};
        size_t m_num_norm_vert                    {0u};
        size_t m_num_param_vert                   {0u};

        // OBJ Element Data Sizes 
        size_t m_num_points                       {0u};
        size_t m_num_lines                        {0u};
        size_t m_num_faces                        {0u};

        // OBJ Group Data Sizes
        size_t m_num_groups                       {0u};
        size_t m_num_objects                      {0u};

        // Parsing Identifier Tokens
        const std::string COMMENT_TOKEN       {"#"};
        const std::string GEO_VERT_TOKEN      {"v"};
        const std::string NORM_VERT_TOKEN     {"vn"};
        const std::string TEXT_VERT_TOKEN     {"vt"};
        const std::string POINT_ELEMENT_TOKEN {"p"};
        const std::string LINE_ELEMENT_TOKEN  {"l"};
        const std::string FACE_ELEMENT_TOKEN  {"f"};
        const std::string GROUP_TOKEN         {"g"};   
        const std::string OBJECT_TOKEN        {"o"};    

    }; // End class ObjParser

} // End namespace OpenGlTutorial