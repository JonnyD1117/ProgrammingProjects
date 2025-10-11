/**
 * @file mesh_serializer.hpp
 * @brief 
 * @author Jonathan Dorsey
 * @date Creation date: 2025-10-10
 *
 */

#pragma once 

// std
#include <iostream>
#include <filesystem>
#include <string>
#include <cmath>
#include <vector>

// Mesh Importer
#include "mesh_importer.hpp"
#include "mesh_data.hpp"


namespace OpenGlTutorial
{

class MeshManager
{
    public: 
    MeshManager()=default;
    ~MeshManager()=default;

    std::shared_ptr<MeshData> getMeshfromFile(const std::filesystem::path& path);

    void setAssimp(bool flag) { m_importer.setAssimp(flag); }

    private:
    MeshImporter m_importer;

};

}