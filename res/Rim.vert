#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 VertexUV;
layout (location = 2) in vec3 VertexNormal;

uniform mat4 transform;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform vec3 camPos;

out vec3 normal;
out vec3 viewDirection;
out vec2 texCoords;  // Pass texture coordinates to the fragment shader

void main()
{
    vec4 worldPosition = (viewMatrix * modelMatrix) * vec4(VertexPosition, 1.0);
    vec4 viewPosition = vec4(worldPosition.xyz - camPos, 1.0);
    gl_Position = transform * vec4(VertexPosition, 1.0);

    normal = mat3(transpose(inverse(modelMatrix))) * VertexNormal;
    viewDirection = -vec3(viewPosition);

    texCoords = VertexUV; // Pass texture coordinates to fragment shader
}

