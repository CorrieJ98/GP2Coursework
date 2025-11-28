#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 tc;
layout (location = 2) in vec3 aNormal;

out vec3 Normal;
out vec3 Position;

uniform mat4 transform;
uniform mat4 model;
out vec2 texCoords;

void main()
{
    Normal = mat3(transpose(inverse(model))) * aNormal;
    Position = vec3(model * vec4(aPos, 1.0));
    texCoords = tc;
    gl_Position = transform * vec4(aPos, 1.0);
}  