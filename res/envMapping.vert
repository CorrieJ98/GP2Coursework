#version 430 core

layout(location = 0) in vec3 aPos;       // vertex position
layout(location = 1) in vec2 aTexCoords; // texture coordinates
layout(location = 2) in vec3 aNormal;    // vertex normal

out vec3 Normal;
out vec3 Position;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // Transform vertex position into world space
    Position = vec3(model * vec4(aPos, 1.0));
    
    // Transform normal into world space
    Normal = mat3(transpose(inverse(model))) * aNormal;
    
    TexCoords = aTexCoords;

    // Final clip-space position
    gl_Position = projection * view * vec4(Position, 1.0);
}