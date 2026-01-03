#version 330 core

// Vertex Positions
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

// Output Variables
out vec3 color; 
out vec2 TexCoord;
out vec3 Normal;
out vec3 curPos;


// Matrices
uniform mat4 camMatrix;
uniform mat4 model;


void main()
{
   curPos = vec3( model * vec4(aPos, 1.0f));
   gl_Position = camMatrix * vec4(curPos, 1.0);

   color = aColor;
   TexCoord = aTexCoord;
   //Normal   = aNormal;
   Normal = -1.0*mat3(transpose(inverse(model))) * aNormal;
}