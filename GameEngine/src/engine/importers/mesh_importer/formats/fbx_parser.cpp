#include "fbx_parser.hpp"

namespace OpenGlTutorial
{
    FbxParser::FbxParser()
    {
        // Pre-allocate Vectors for Effiency
        vertices.reserve(RESERVE_SIZE);
        indices.reserve(RESERVE_SIZE);
    }

    std::shared_ptr<MeshData> FbxParser::parse(const std::filesystem::path& mesh_path)
    {
        return nullptr;
    }
}