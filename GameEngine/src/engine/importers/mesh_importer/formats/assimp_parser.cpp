
#include "assimp_parser.hpp"

namespace OpenGlTutorial
{
    AssimpParser::AssimpParser()
    {
        // Preallocated Vectors for Efficiency
        vertices.reserve(RESERVE_SIZE);
        indices.reserve(RESERVE_SIZE);
    }
    
    std::shared_ptr<MeshData> AssimpParser::parse(const std::filesystem::path& mesh_path)
    {
        const aiScene* scene = importer.ReadFile(   mesh_path.string(),
                                                    aiProcess_Triangulate |
                                                    aiProcess_GenSmoothNormals |
                                                    aiProcess_JoinIdenticalVertices |
                                                    aiProcess_ImproveCacheLocality |
                                                    aiProcess_OptimizeMeshes |
                                                    aiProcess_CalcTangentSpace |
                                                    aiProcess_ValidateDataStructure);

        const aiMesh* mesh = scene->mMeshes[0];  // First mesh

        for (size_t i = 0; i < mesh->mNumVertices; ++i) {
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

        for (size_t i = 0; i < mesh->mNumFaces; ++i) 
        {
            const aiFace& face = mesh->mFaces[i];
            for (size_t j = 0; j < face.mNumIndices; ++j) 
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        // NOTE: std::move parser data into MeshData
        return std::make_shared<MeshData>(std::move(vertices), std::move(indices));
    }  
}