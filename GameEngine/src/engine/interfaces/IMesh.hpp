/**
 * @file IMesh.hpp
 * @brief Interace of type IMesh.
 * @author Jonathan Dorsey 
 * @date Creation date: 2025-05-27
 * 
 */

#pragma once 

// stl
#include <type_traits>

namespace OpenGlTutorial
{
    class IMesh
    {
        public:
        IMesh()=default;
        virtual ~IMesh()=default;

        virtual const size_t getNumIndices() const = 0; 

        virtual void Bind() const = 0; 

        virtual void buildVAO() = 0; 
    
        virtual void addAttribute(size_t layout_num, size_t num_components) = 0; 
    };
}