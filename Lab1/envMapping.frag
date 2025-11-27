#version 420 core

out vec4 fragColor;

in Vertex_DATA{
	vec2 tC;
    vec3 Normal;
    vec3 Position;
} vs_In;

uniform vec3 cameraPos;
uniform samplerCube skybox;
layout (binding = 1) uniform sampler2D diffuse;

void main(){
    vec3 I = normalize(vs_In.Position - cameraPos); // incident vector direction
    vec3 R = reflect(I, normalize(vs_In.Normal)); // reflection direction

    vec4 colour = vec4(texture(skybox, R).rgb, 1.0);

    fragColor = (texture(diffuse, vs_In.tC) * colour);
}