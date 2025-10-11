/**
 * @file MeshManager.hpp
 * @brief 
 * @author Jonathan Dorsey
 * @date Creation date: 2025-10-10
 *
 */

 // local 
#include "MeshManager.hpp"


namespace OpenGlTutorial
{

std::shared_ptr<MeshData> MeshManager::getMeshfromFile(const std::filesystem::path& path) 
{ 
    return m_importer.loadMesh(path); 
}


}