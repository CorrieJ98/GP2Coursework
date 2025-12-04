/*
This shader is adapted and based on a fragment shader found on ShaderToy
Created by vegardno in 2019-11-15

I have converted it for use with 3D GameObjects in OpenGL.

https://www.shadertoy.com/view/wdVXWR
*/


#version 430 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTex;
layout(location = 2) in vec3 aNormal;


out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTex;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}