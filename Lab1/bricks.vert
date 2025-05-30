#version 400

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 aTexCoord; 
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(VertexPosition, 1.0);
    TexCoord = aTexCoord;
}
