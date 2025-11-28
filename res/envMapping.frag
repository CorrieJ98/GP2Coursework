//#version 330 core
//
//out vec4 FragColor;
//
//in vec3 Normal;
//in vec3 Position;
//
//uniform vec3 cameraPos;
//uniform samplerCube skybox;
//
//void main()
//{             
//    vec3 I = normalize(Position - cameraPos);
//    vec3 R = reflect(I, normalize(Normal));
//    FragColor = vec4(texture(skybox, R).rgb, 1.0);
//}
//

#version 430 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;
in vec2 TexCoords;

uniform vec3 cameraPos;

// Explicit binding locations for samplers
layout(binding = 0) uniform samplerCube skybox;
layout(binding = 1) uniform sampler2D diffuse;

void main()
{             
    vec3 I = normalize(Position - cameraPos);
    vec3 R = reflect(I, normalize(Normal));
    
    // Modern texture function
    vec4 color = texture(diffuse, TexCoords);
    vec4 mapping = vec4(texture(skybox, R).rgb, 1.0);
   
    FragColor = vec4(mix(color.rgb, mapping.rgb, 0.95), 1.0);
}