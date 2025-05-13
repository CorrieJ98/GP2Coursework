#version 400
 
out vec4 FragColor;
 
in vec4 v_pos;
in vec2 vC;
 
vec3 fogColor = vec3(0.1f,0.1f,0.1f);
 
float maxDist = 10.0f;
float minDist = 1.0f;
 
uniform sampler2D textureIn;
 
void main(){
 
	vec4 textColour = texture(textureIn, vC);
 
	float dist = abs(v_pos.z);
	float fogFactor = ((maxDist - dist) / (maxDist - minDist));
	fogFactor = clamp( fogFactor,0.0,1.0);
	vec3 lightColor = vec3(0.7f,0.7f,0.6f);
	vec3 color = mix(fogColor,lightColor,fogFactor);
 
	FragColor = mix(textColour, vec4(color, 1.0), 0.5);
}