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
 * 
 * Rules:
 *           1) Lines starting with '#' are commented
 *           2) OBJ can use .mtl materials
 *           3) Character 'g' is a group selector
 * 
 * 
 * Parse Faces: 
 *
 *           1) Verts Only                 ( e.g. f v1 v2 v3 )
 *           2) Verts & Textures           ( e.g. f v1/vt1 v2/vt2 v3/vt3 )
 *           3) Verts, Textures, & Normals ( e.g. f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 )
 *           4) Verts & Normals            ( e.g. f v1//vn1 v2//vn2 v3//vn3 )
 *
 *           Triangularize Non-Triangle Faces
 *
 *          Compute "normal" depending on whether smooth shading is ON or OFF
 * 
 * 
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
        m_triangular_faces           .reserve(RESERVE_SIZE);
        m_polygonal_faces .reserve(RESERVE_SIZE);
    }
   
    std::shared_ptr<MeshData> ObjParser::parse( const std::filesystem::path& mesh_path )
    {
        if ( !std::filesystem::exists( mesh_path ) )
        {
            throw std::runtime_error( "Mesh File DOES NOT exist" );
        }

        /*
            Allocation pass determines number of elements in file to allocate efficiently   
            NOTE: 'faces' may non-triangular
        */ 
        data_sizing_pass( mesh_path );

        /*
            Extraction pass extracts the element data into containers
        */ 
        data_extraction_pass( mesh_path );

        /*
            Face triangulation - if required convert all polygonal faces into triangles   
        */ 
        if ( triangulation_required )
        {
            triangularize_faces( );
        }

        /*
            Create Mesh Data
        */ 
        summarize_mesh();

        construct_mesh_data();

        //
        return std::make_shared<MeshData>();
    }

    /************************/
    //  Private Methods
    /************************/

    /*
        First parsing pass of OBJ file that extracts the 
        number of vertices, normals, texture verts...etc
        to optimize allocation efficiency in second 
        parsing pass.
    */
    void ObjParser::data_sizing_pass( const std::filesystem::path& mesh_path )
    {

        // Handle File IO
        std::ifstream mesh_stream { mesh_path };
        // Temp working variable
        std::string line;

        // Iterate over file (line-by-line)
        while( std::getline( mesh_stream, line ) )
        {
            // Split Line by Whitespace
            std::stringstream ss { line };
            std::string word;
            std::vector<std::string> line_words;

            while( ss >> word )
            {
                line_words.push_back(word);
            }

            try
            {
                if( line_words.size() == 0 )
                {
                    continue;
                } 
                std::string token = line_words[0];

            
                // Skip Comments && Empty Lines
                if( token == COMMENT_TOKEN || line == "" ) { continue; } // Do not parse commented or empty lines
                
                // Increment OBJ Identifier Counters
                else if ( token == GEO_VERT_TOKEN )     { ++m_num_geo_vert;  continue; }
                else if ( token == NORM_VERT_TOKEN )    { ++m_num_norm_vert; continue; }
                else if ( token == TEXT_VERT_TOKEN )    { ++m_num_text_vert; continue; }
                else if ( token == POINT_ELEMENT_TOKEN ){ ++m_num_points;    continue; }
                else if ( token == LINE_ELEMENT_TOKEN ) { ++m_num_lines;     continue; } 
                else if ( token == FACE_ELEMENT_TOKEN ) { ++m_num_faces;     continue; } // NOTE: Faces CAN be more than 3 vertices (e.g. quads are 4...etc)
                else if ( token == GROUP_TOKEN )        { ++m_num_groups;    continue; }
                else if ( token == OBJECT_TOKEN )       { ++m_num_objects;   continue; }
                else 
                {
                    throw std::runtime_error("ObjParser::parse() encounted an 'unknown' OBJ identifier.");
                }    
            }
            catch( std::exception& e)
            {
                throw std::runtime_error(e.what());
            }
               
        }

        // Resize Data Containers for allocation efficiency
        m_vertexVec            .reserve( m_num_geo_vert  );
        m_textureVec           .reserve( m_num_text_vert );
        m_normalVec            .reserve( m_num_norm_vert );
        m_triangular_faces           .reserve( m_num_faces );
        m_polygonal_faces .reserve( m_num_faces );
    }
    
    /*
        Second parsing pass that extracts the data from
        from the raw OBJ file, after the first pass has
        provided enough information to efficiently 
        allocate storage.
    */
    void ObjParser::data_extraction_pass( const std::filesystem::path& mesh_path )
    {

        // Handle File IO
        std::ifstream mesh_stream { mesh_path };
        // Temp working variable
        std::string line;

        // Iterate Over File (line-by-line)
        while( std::getline( mesh_stream, line ))
        {
            // Skip Comments && Empty Lines
            if(line[0] == '#' || line == "")
            {
                continue;
            }

            // Split Line by Whitespace
            std::stringstream ss { line };
            std::string word;
            std::deque<std::string> line_words;

            while( ss >> word )
            {
                line_words.push_back(word);
            }

            // Extract First token from line (should be identifier)
            std::string token = line_words.front();
            
            // Increment OBJ Identifier Counters
            if ( token == GEO_VERT_TOKEN )
            {
                parse_geometry_vert( line_words );
                continue;
            }
            else if ( token == NORM_VERT_TOKEN )
            {
                parse_normal_vert( line_words );
                continue;
            }
            else if ( token == TEXT_VERT_TOKEN )
            {
                parse_texture_vert( line_words );
                continue;
            }
            else if ( token == POINT_ELEMENT_TOKEN )
            {

                // parse_point_element( line_words );
                continue;
            }
            else if ( token == LINE_ELEMENT_TOKEN )
            {
                // parse_line_element( line_words );
                continue;
            }
            else if ( token == FACE_ELEMENT_TOKEN )
            {
                parse_face_element( line_words );
                continue;
            }
            else if ( token == GROUP_TOKEN )
            {
                // parse_group_element( line_words );
                continue;
            }
            else if ( token == OBJECT_TOKEN )       
            {
                // parse_object_element( line_words );
                continue;
            }
            else 
            {
                throw std::runtime_error("ObjParser::parse() encounted an 'unknown' OBJ identifier.");
            }         
        }

        // Shrink Containers to Fit
        m_vertexVec.shrink_to_fit();
        m_normalVec.shrink_to_fit();
        m_textureVec.shrink_to_fit();
        m_triangular_faces.shrink_to_fit();
    }

    /*
        Triangularization of non-triangle faces.
        This is required for rendering in OpenGL
        & Vulkan
    */
    void ObjParser::triangularize_faces()
    {
        for (auto& face : m_polygonal_faces)
        {
            // Triangularize Faces
        }
    }

    void ObjParser::construct_mesh_data()
    {
        // From "face" data construct MeshVertex 
        // Create MeshData from vector of all MeshVertices


        // std::vector<MeshVertex> m_meshVertexVec {}; // Vector of structs that store raw mesh vertex data
        // m_meshVertexVec.reserve(m_triangular_faces.size());
        // for ( auto face : m_triangular_faces )
        // {
        //     size_t vertIdx = 0;
        //     size_t textIdx = 0; 
        //     size_t normIdx = 0; 

        //     m_meshVertexVec.emplace_back(m_vertexVec[vertIdx], m_textureVec[textIdx], m_normalVec[normIdx]);
        // }
    }

} // End namespace OpenGlTutorial