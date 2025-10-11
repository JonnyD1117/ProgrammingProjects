#pragma once 

// std 
#include <iostream>
#include <vector>
#include <string> 

// local 
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>



class AssimpParser
{
    public:
    AssimpParser(std::string path)
    {
        const aiScene* scene = importer.ReadFile(   path,
                                                    aiProcess_Triangulate |
                                                    aiProcess_GenSmoothNormals |
                                                    aiProcess_JoinIdenticalVertices |
                                                    aiProcess_ImproveCacheLocality |
                                                    aiProcess_OptimizeMeshes |
                                                    aiProcess_CalcTangentSpace |
                                                    aiProcess_ValidateDataStructure);

        const aiMesh* mesh = scene->mMeshes[0];  // First mesh

        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            aiVector3D pos = mesh->mVertices[i];
            aiVector3D norm = mesh->HasNormals() ? mesh->mNormals[i] : aiVector3D(0, 0, 0);
            aiVector3D uv = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][i] : aiVector3D(0, 0, 0);

            // Push to vertex buffer: position (3), normal (3), uv (2)
            vertices.push_back(pos.x);
            vertices.push_back(pos.y);
            vertices.push_back(pos.z);
            // vertices.push_back(uv.x);
            // vertices.push_back(uv.y);
            vertices.push_back(norm.x);
            vertices.push_back(norm.y);
            vertices.push_back(norm.z);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; ++i) 
        {
            const aiFace& face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; ++j) 
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        std::cout << "vertex Buffer Size = " << vertices.size() << std::endl;
        std::cout << "index Buffer Size = " << indices.size() << std::endl;
    
    }
    ~AssimpParser()=default;

    std::vector<float> getVertexBuffer() { return vertices; }
    std::vector<unsigned int> getIndexBuffer() { return indices;} 

    private:

    std::vector<float> vertices; 
    std::vector<unsigned int> indices;

    Assimp::Importer importer;

};