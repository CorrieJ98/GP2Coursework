#version 420 core

layout (location = 0) in vec3 inPosition;

const float PI = 3.14159265358979323846;
const float TWO_PI = 6.28318530717958647692;


void main()
{
	gl_Position = vec4(inPosition, 1.0);
}