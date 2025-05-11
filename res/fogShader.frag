#version 400

out vec4 FragColor;

in vec4 v_pos;

vec3 fogColor = vec3(0.35f, 0.4f, 0.5f);

float maxDist = 10.0f;
float minDist = 1.0f;

void main(){

	float dist = abs(v_pos.z);
	float fogFactor = ((maxDist - dist) / (maxDist - minDist));
	fogFactor = clamp( fogFactor,0.0,1.0);
	vec3 lightColor = vec3(0.25f, 0.25f, 0.25f);
	vec3 color = mix(fogColor,lightColor,fogFactor);

	FragColor = vec4(color, 1.0);
}