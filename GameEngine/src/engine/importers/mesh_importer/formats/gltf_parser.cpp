
#include "gltf_parser.hpp"

namespace OpenGlTutorial
{
    GltfParser::GltfParser()
    {
        // Pre-allocate Vectors for Effiency
        vertices.reserve(RESERVE_SIZE);
        indices.reserve(RESERVE_SIZE);
    }

    std::shared_ptr<MeshData> GltfParser::parse(const std::filesystem::path& mesh_path)
    {
        return nullptr;
    }
}