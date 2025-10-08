#version 330 core

// Imports the color from the Vertex Shader
in vec3 color;
in vec2 TexCoord;
in vec3 Normal;
in vec3 curPos;

uniform sampler2D tex0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;
uniform vec4 baseColor;

out vec4 FragColor;


void main()
{
	// ambient lighting
	float ambient = 0.2f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - curPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos - curPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
	float specular = specAmount * specularLight;

	// outputs final color
	//FragColor =  baseColor * (diffuse + ambient + specular);
	//FragColor =  texture(tex0, TexCoord) * (diffuse + ambient + specular);
	FragColor =  vec4(normalize(Normal) * 0.5 + 0.5, 1.0);
	//FragColor = vec4(vec3(FragColor.z), 1.0);


}