#version 430 core

layout(location = 0) in vec3 aPos;       // Vertex position
layout(location = 1) in vec3 aNormal;    // Vertex normal
layout(location = 2) in vec2 aTexCoord;

out vec3 FragPos;    // Position in world space
out vec3 Normal;     // Normal in world space
out vec2 TexCoord;   // Texture coordinates

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;


void main()
{
    FragPos = vec3(uModel * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(uModel))) * aNormal;
    TexCoord = aTexCoord;

    gl_Position = uProjection * uView * vec4(FragPos, 1.0);
}