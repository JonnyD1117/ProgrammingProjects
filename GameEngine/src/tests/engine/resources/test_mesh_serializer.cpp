// std 
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <iterator>
#include <string>

// Gtest
#include <gtest/gtest.h>

// Engine
#include "MeshData.hpp"
#include "MeshManager.hpp"
#include "MeshSerializer.hpp"

// I'm lazy usually I don't do like using namespace like this.
using namespace OpenGlTutorial; 

TEST(TestEngineResources, TestMeshSerializer) 
{
    // Define Paths to P
    std::filesystem::path objectPath = "/home/indy/repos/ProgrammingProjects/GameEngine/src/assets/meshes/teapot.obj";
    std::filesystem::path serializedPath = "/home/indy/repos/ProgrammingProjects/GameEngine/src/assets/data/teapot.dat";

    // Create Mesh Manager
    MeshManager m_meshManager;

    // Force Use of Assimp Parser
    m_meshManager.setAssimp(true);

    // Get MeshData (to be serialized)
    std::shared_ptr<MeshData>mesh_data = m_meshManager.getMeshfromFile(objectPath);   

    // Serialize the MeshData
    MeshSerializer::serialize(*mesh_data, serializedPath);

    // Deserialize the MeshData
    MeshData deserialize = MeshSerializer::deserialize(serializedPath);

    // Iterate Over each field of vertex vector
    for(size_t ctr = 0 ; ctr<deserialize.vertices.size(); ctr++)
    {
        EXPECT_EQ(mesh_data->vertices[ctr].position, deserialize.vertices[ctr].position);
        EXPECT_EQ(mesh_data->vertices[ctr].texture , deserialize.vertices[ctr].texture);
        EXPECT_EQ(mesh_data->vertices[ctr].normal  , deserialize.vertices[ctr].normal);
    }

    // Iterate Over each field of indices vector
    for(size_t ctr = 0 ; ctr<deserialize.indices.size(); ctr++)
    {
        EXPECT_EQ(mesh_data->indices[ctr], deserialize.indices[ctr]);
    }
}

