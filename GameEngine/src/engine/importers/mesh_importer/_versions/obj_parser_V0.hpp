/**
 * @file obj_parser.hpp
 * @brief File defines class the concept of a OBJ file parser for mesh creation.
 * @author Jonathan Dorsey 
 * @date Creation date: 2025-05-12
 * 
 * OBJ files are a very easy way to create mesh geometry. This is a class attempts
 * to implement a VERY basic version of a OBJ file parser (for s & g) to prove that 
 * I understand the concept of loading mesh elements in from a well known 3D model 
 * object exchange format.
 */

#pragma once 

// std
#include <algorithm>
#include <array>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// opengl
#include <glad/glad.h>
#include <glm/glm.hpp>

// engine


namespace OpenGlTutorial
{
    class ObjParser
    {
        public:
        ObjParser(std::string mesh_path);
        ~ObjParser()=default;

        void parse();

        std::vector<float> getVertexBuffer() { return m_vertexBufferData; }
        std::vector<unsigned int> getIndexBuffer() { return m_indexBufferData; }

        private:

        void preallocateResources()
        {        
            // Check if file Exists
            if (!std::filesystem::exists(m_path)) { throw std::runtime_error("OBJ Mesh Parser Failed to Load File - File Does NOT exist!"); }
            
            // Create FileStream 
            std::ifstream file (m_path);

            // Read File Line-by-Line
            std::string line; 
            size_t lineCtr = 0; 

            // Loop over every line in the file
            while(std::getline(file, line))
            {
                lineCtr++;
            }

            // Set Max Number of Lines in the File
            m_maxLines = lineCtr;

            // Resize all resource vectors to Pre-Allocate
            m_vertexCoords .reserve(m_maxLines);
            m_textureCoords.reserve(m_maxLines);
            m_normals      .reserve(m_maxLines);
            m_faces        .reserve(m_maxLines);
        }

        void parseVertices(std::vector<std::string> curLine)
        {
            VertexCoords vert; 

            // check Vertex 
            for (size_t idx=1; idx < curLine.size(); idx++)
            {
                vert.data[idx-1] = std::stod(trim(curLine[idx]));
            }

            m_vertexCoords.push_back(vert);            
        }

        void parseTextures(std::vector<std::string> curLine)
        {
            TextureCoords text;
            // check Textures
            for (size_t idx=1; idx < curLine.size(); idx++)
            {
                text.data[idx] = std::stod(trim(curLine[idx]));
            }
            m_textureCoords.push_back(text);
        }

        void parseNormals(std::vector<std::string> curLine)
        {
            Normal norm; 

            // check Normals 
            for (size_t idx=1; idx < curLine.size(); idx++)
            {
                // norm.data[idx-1] = std::stod(trim(curLine[idx]));

                std::string tmp = "1.0";
                norm.data[idx-1] = std::stod(trim(tmp));
            }

            m_normals.push_back(norm);
        }

        void parseFaces(std::vector<std::string> curLine)
        {
            // Compute Number of Arguments
            size_t numArgs = curLine.size() - 1; // could be any number of polygon faces

            // Null Argument Guard
            if (numArgs <= 0 ) { return; }

            // Container to hold triangular faces
            std::vector<std::vector<std::string>> triangularized_faces ;

            // Face Describes a Polygon (not a triangle)
            // Triangularize before handling with parser
            // if (numArgs > 3)
            // {
            //     // Triangularize Polygonal Face
            //     for( size_t i=1; i < curLine.size(); i++)
            //     {
            //         std::vector<std::string> triaFaceToken;
            //         emitTriangle(faceVertices[0], faceVertices[i], faceVertices[i + 1]);
            //     }
            // }
            // else
            // {
                // For uniform handling of faces append existing triangular faces to list
                triangularized_faces.push_back(curLine);
            // }

            // Parse ALL triangular faces
            for(auto line : triangularized_faces)
            {
                handleFaceFormatVariations(line);
            }
        }

        std::string trim(std::string& s) 
        {
            s.erase(std::remove_if(s.begin(), s.end(), [](unsigned char c) {return std::isspace(c);}), s.end());
            return s;
        }

        void handleVertexOnlyLayout(std::vector<std::string> currentLine)
        {
            Face face;
            for (size_t arg_pos=1; arg_pos < 4; arg_pos++)
            {
                // Vertex Data (Indices in OBJ are 1 based)
                size_t vertInd = static_cast<unsigned int>(std::stoul(trim(currentLine[arg_pos]))) - 1;

                face.m_vertexInds[arg_pos -1] = vertInd;

                // Compute Normals: 1) Face 2) Vertex
            }

            m_faces.push_back(face);
        }

        void handleVertexTextureLayout(std::vector<std::string> currentLine)
        {

        }

        void handleVertexTextureNormalLayout(std::vector<std::string> currentLine)
        {

        }

        void handleVertexNormalLayout(std::vector<std::string> currentLine)
        {
            // NOTE: Assumption is that ALL polygons have been triangularized (tesselated)

            Face face;
            for (size_t arg_pos=1; arg_pos < 4; arg_pos++)
            {
                size_t totLen = currentLine[arg_pos].size();
                size_t delimPos = currentLine[arg_pos].find("//");
                size_t delimSize =2 ;
                bool delimInvalid = (delimPos!=std::string::npos);

                if(delimInvalid) { return; }

                std::string vertStr = currentLine[arg_pos].substr(0,delimPos);

                size_t normStart = (delimPos + delimSize);
                size_t normLen   = (totLen - normStart); 

                std::string normStr = currentLine[arg_pos].substr(normStart, normLen); 

                std::cout << "Vert String = " << vertStr<< "  Ind Str = " << normStr<< std::endl;
                // Vertex Data (Indices in OBJ are 1 based)
                size_t vertInd = static_cast<unsigned int>(std::stoul(trim(vertStr))) - 1;

                // Normal Data (Indices in OBJ are 1 based)
                size_t normInd = static_cast<unsigned int>(std::stoul(trim(normStr))) - 1;

                face.m_vertexInds[arg_pos -1] = vertInd;
                face.m_normalInds[arg_pos -1] = normInd;

                std::cout << "RECONSTRUCT = f" << vertInd<<"//"<< normInd<< std::endl;
            }

            // // std::cout << std::endl;

            m_faces.push_back(face);
        }

        void handleFaceFormatVariations(std::vector<std::string> currentLine)
        {

            // Set Default face format type
            FaceTypes faceFormat = FaceTypes::INVALID;

            std::string testStr = currentLine[1];
            size_t delimCounter = std::count(testStr.begin(), testStr.end(), '/');

            if (delimCounter == 0)
            {
                faceFormat = FaceTypes::VertexOnly;
            }
            else if (delimCounter == 1)
            {
                // v + t
                faceFormat = FaceTypes::VertexAndTextures;
            }
            else if (delimCounter == 2)
            {
                // v + _ + n || v + t + n
                
                // Double Delimited Condition
                bool doubleDelimited  = ((currentLine[1].find("//"))!=std::string::npos);
                // Set Face Format
                faceFormat = (doubleDelimited) ? FaceTypes::VertexAndNormals : FaceTypes::VertexAndTexturesAndNormals;
            }
            else
            {
                std::cerr << "Obj Parser: ERROR - FaceFormat Delimiter is INVALID" << std::endl;
            }

            switch( faceFormat )
            {
                case FaceTypes::VertexOnly:
                {
                    handleVertexOnlyLayout(currentLine);
                    break;
                }
                case FaceTypes::VertexAndTextures:
                {
                    handleVertexTextureLayout(currentLine);
                    break;
                }
                case FaceTypes::VertexAndTexturesAndNormals:
                {
                    handleVertexTextureNormalLayout(currentLine);
                    break;
                }
                case FaceTypes::VertexAndNormals:
                {
                    handleVertexNormalLayout(currentLine);
                    break;
                }
                default:
                    break;
            }
        }
       
        void populateBufferFromFace(std::vector<GLfloat>& vertBuffer, std::vector<GLuint>& indBuffer)
        {
            size_t ctr = 0; 
            std::map<size_t, size_t> vertInd2IndBuffer;
            for ( auto face : m_faces )
            {  
                //********************************//
                // *** Populate Vertex Buffer *** //
                //********************************//
                for(size_t idx=0; idx<3; idx++)
                {
                    // Vertex Coords
                    size_t vertInd = face.m_vertexInds[idx];
                    VertexCoords vert = m_vertexCoords[vertInd];

                    // if (auto search = example.find(2); search != example.end())
                    // if(vertInd2IndBuffer.find(vertInd)==vertInd2IndBuffer.end())
                    // {
                    //     vertInd2IndBuffer[vertInd] = ctr;
                    //                             ctr++;

                    // }

                    for(size_t i=0; i< 3; i++)
                    {
                        vertBuffer.push_back(vert.data[i]);

                    }
                    
                    indBuffer.push_back(ctr); 
                    ctr++;
                    // indBuffer.push_back(vertInd2IndBuffer[vertInd]); 
            
                    // Normals
                    size_t normInd = face.m_normalInds[idx];

                    Normal norm = m_normals[normInd];

                    for(size_t i=0; i< 3; i++)
                    {
                        vertBuffer.push_back(norm.data[i]);
                        // indBuffer.push_back(ctr); 
                        // ctr++;
                    }
                }

                //*******************************//
                // *** Populate Index Buffer *** //
                //*******************************//
                // indBuffer.push_back(m_faces[idx].data[i]-1);

            }
        }

        std::string m_path;
        std::vector<VertexCoords>  m_vertexCoords;
        std::vector<TextureCoords> m_textureCoords;
        std::vector<Normal>        m_normals;
        std::vector<Face>         m_faces;

        std::vector<GLfloat> m_vertexBufferData;
        std::vector<GLuint> m_indexBufferData;

        size_t m_maxLines;

        const bool DEBUG_PARSER = false;
    };
}