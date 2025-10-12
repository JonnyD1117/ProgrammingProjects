

#include "MeshSerializer.hpp"

namespace OpenGlTutorial
{

    void MeshSerializer::serialize( const MeshData& mesh, std::ofstream& of )
    {
        // Serialize Mesh Vertex Vector to File
        size_t vertCount = mesh.vertices.size();
        of.write(reinterpret_cast<const char*>(&vertCount), sizeof(vertCount));
        of.write(reinterpret_cast<const char*>(mesh.vertices.data()), sizeof(MeshVertex)*vertCount);

        // Serialize Mesh Index Vector to File
        size_t indCount = mesh.indices.size();
        of.write(reinterpret_cast<const char*>(&indCount), sizeof(indCount));
        of.write(reinterpret_cast<const char*>(mesh.indices.data()), sizeof(size_t)*indCount);

    }

    MeshData MeshSerializer::deserialize( std::ifstream& in )
    {
        // Create MeshData as deserialization container
        MeshData data; 

        // Deserialize Mesh Vertex Vector from File
        size_t vertCount;
        in.read(reinterpret_cast<char*>(&vertCount), sizeof(vertCount));

        data.vertices.resize(vertCount);
        in.read(reinterpret_cast<char*>(data.vertices.data()), sizeof(MeshVertex)*vertCount);

        // Deserialize Mesh Index Vector from File
        size_t indCount;
        in.read(reinterpret_cast<char*>(&indCount), sizeof(indCount));

        data.indices.resize(indCount);
        in.read(reinterpret_cast<char*>(data.indices.data()), sizeof(size_t)*indCount);

        return data;
    }

    void MeshSerializer::serialize( const MeshData& mesh, const std::filesystem::path& output_path )
    {
        // Create/Open Output File for Serialization
        std::ofstream outFile {output_path.string(), std::ios::binary};

        // Error Checking
        if(!outFile)
        {
            throw std::runtime_error(std::format("MeshSerializer::serialize() failed to open ofstream '{}'", output_path.string()));
        }

        // Serialize File via its ofstream
        serialize( mesh, outFile);
    }

    MeshData MeshSerializer::deserialize( const std::filesystem::path& input_path )
    {
        // Create/Open Output File for Serialization
        std::ifstream inFile {input_path.string(), std::ios::binary};

        // Error Checking
        if(!inFile)
        {
            throw std::runtime_error(std::format("MeshSerializer::serialize() failed to open ifstream '{}'", input_path.string()));
        }

        // Serialize File via its ofstream
        return deserialize( inFile);
    }

} // namespace OpenGlTutorial