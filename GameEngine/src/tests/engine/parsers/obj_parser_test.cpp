/**
 * @file ObjParser_UT.cpp
 * @brief Implementation of the class/functions defined in obj_parser.hpp/cpp to test functionality
 * @author Jonathan Dorsey
 * @date Creation date: 2025-05-17
 * 
 * This file contains the implementation of Google GTest for testing the parsing of an <file>.obj
 * mesh file.
 */


// std
#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>

// gtest
#include <gtest/gtest.h>

// engine_parsers
#include "obj_parser.hpp"


TEST(TestObjectMeshParserVertexData, TestVertex1) {
    
    std::string path = "src/assets/meshes/teapot.OBJ";
    //
    OpenGlTutorial::ObjParser parser{path};

    parser.parse();

    // Evaluate Validity
    EXPECT_TRUE(true);
}

TEST(TestObjectMeshParserVertexNormals, TestVertexNorms1) {
    
    // Evaluate Validity
    EXPECT_TRUE(true);
}