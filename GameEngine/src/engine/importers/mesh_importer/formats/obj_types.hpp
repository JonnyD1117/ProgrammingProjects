/**
 * @file MeshTypes.hpp
 * @brief File defines types which the mesh parser will use.
 * @author Jonathan Dorsey
 * @date Creation date: 2025-05-27
 *
 */

#pragma once

// std
#include <iostream>
#include <map>
#include <optional>
#include <vector>

namespace OpenGlTutorial
{

namespace ObjMesh
{

    enum class FaceParsingState
    {
        VERT = 0, 
        TEXT, 
        NORM
    };

    struct FaceVertData
    {
        FaceVertData(
            int geo,
            std::optional<int> tex = std::nullopt,
            std::optional<int> norm = std::nullopt)
            :
            m_geo_vert_idx(geo),
            m_text_vert_idx(tex),
            m_norm_vert_idx(norm)
        {}

        int                m_geo_vert_idx  {};
        std::optional<int> m_text_vert_idx {};
        std::optional<int> m_norm_vert_idx {};

        void print_data()
        {
            std::cout << "######################" << std::endl;
            std::cout << "Face Vertex Data:"<< std::endl;
            std::cout << "\t- Vert. Idx = " << m_geo_vert_idx << std::endl;
            std::cout << "\t- Text. Idx = " << m_text_vert_idx.value_or(9999) << std::endl;
            std::cout << "\t- Norm. Idx = " << m_norm_vert_idx.value_or(9999) << std::endl;
            std::cout << "######################" << std::endl;
        }
    };

    struct ObjFace
    {
        
        std::vector<FaceVertData>  data;

        size_t get_num_verts() const { return data.size(); }

        void insert_vertex_data( int geo,       
                                std::optional<int> text=std::nullopt, 
                                std::optional<int> norm=std::nullopt )
        {
            data.emplace_back( geo, text, norm );
        }

        void insert_face_data( FaceVertData& face_data )
        {
            data.push_back( face_data );
        }

        void print()
        {
            const int n = 2; 
            std::stringstream ss; 
            ss << "f" << std::setw(n) << ""; 
            for(auto d : data)
            {
                ss << d.m_geo_vert_idx;

                if( d.m_text_vert_idx.has_value() )
                {
                    ss << "/" << d.m_text_vert_idx.value();
                }
                if ( d.m_norm_vert_idx.has_value() )
                {
                    ss << "/" << d.m_norm_vert_idx.value();
                }

                ss << std::setw(n) << "";
            }

            std::cout << ss.str() << std::endl;
        }
    };

} // end namespace ObjMesh

} // namespace OpenGlTutorial