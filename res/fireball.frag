#version 430 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform float uTime;

layout(binding = 0) uniform sampler2D uNoiseTexture;

// Fire color function
vec3 fire_color(float x)
{
    return vec3(1., 0., 0.) * x
         + vec3(1., 1., 0.) * clamp(x - .5, 0., 1.)
         + vec3(1., 1., 1.) * clamp(x - .7, 0., 1.);
}

void main()
{
    // animate fire
    float noise = texture(uNoiseTexture, TexCoords + vec2(uTime * 0.1f, uTime * 0.1f)).r;

    // Intensity based on height (y) and noise
    float intensity = clamp(FragPos.y * 0.5 + noise, 0.0, 1.0);

    vec3 color = fire_color(intensity);

    FragColor = vec4(color, 1.0);
}

mat4 rotate(float a, vec3 v)
{
    float c = cos(a);
    vec3 ci = (1. - c) * v;
    vec3 s = sin(a) * v;

    return mat4(
        ci.x * v.x + c, ci.x * v.y + s.z, ci.x * v.z - s.y, 0,
        ci.y * v.x - s.z, ci.y * v.y + c, ci.y * v.z + s.x, 0,
        ci.z * v.x + s.y, ci.z * v.y - s.x, ci.z * v.z + c, 0,
        0, 0, 0, 1
	);
}

mat4 translate(vec3 v)
{
    return mat4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        v.x, v.y, v.z, 1
    );
}

// http://jamie-wong.com/2016/07/15/ray-marching-signed-distance-functions/
vec3 rayDirection(float fieldOfView, vec2 size, vec2 fragCoord) {
    vec2 xy = fragCoord - size / 2.0;
    float z = size.y / tan(radians(fieldOfView) / 2.0);
    return normalize(vec3(xy, -z));
}

// intersect ray with sphere to find
//  - the distance to the sphere
//  - and the point of intersection on the sphere
// http://viclw17.github.io/2018/07/16/raytracing-ray-sphere-intersection/
float intersect_ray_sphere(vec3 origin, vec3 direction, vec3 center, float radius)
{
    vec3 oc = origin - center;
    float a = dot(direction, direction);
    float b = 2. * dot(oc, direction);
    float c = dot(oc, oc) - radius * radius;
    float disc = b * b - 4. * a * c;
    if (disc < 0.) {
        // no intersection?
        return -1.;
    } else {
        return (-b - sqrt(disc)) / (2. * a);
    }
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{


    mat4 mvp = rotate(radians(0. * uTime), vec3(0, 1, 0));
    
	vec3 dir = (mvp * vec4(rayDirection(45., vec2(800., 600.), fragCoord), 0)).xyz;
    vec3 eye = (mvp * vec4(0., 0., 1.9, 1.)).xyz;

    vec3 sphere_pos = vec3(0., 0., 0.);

    float intensity = 0.;
    
    mat4 tex_mat = mat4(1.);
    mat4 wind_mat = mat4(1.);
    for (int i = 0; i < 10; ++i) {
        float dist = intersect_ray_sphere(eye, dir, sphere_pos, 1. - float(i) / 40.);

        if (dist > 0.) {
            vec3 hit_pos = eye + dir * dist;
            vec3 t_hit_pos = (tex_mat * wind_mat * vec4(hit_pos, 1.)).xyz;
            vec3 normal = normalize(t_hit_pos - sphere_pos);

            float alpha = texture(uNoiseTexture, 1. / float(i) * vec2(atan(normal.z, normal.x) / radians(90.), normal.y)).r;
			intensity += step(1. - float(i) / 6., alpha) * .8 * alpha * max(0., dot(vec3(0, 0, 1.), hit_pos));

            tex_mat = rotate(radians(11.) * uTime, normalize(vec3(.3, -.7, .1))) * tex_mat;
            wind_mat = rotate(radians(25.) * uTime, normalize(vec3(1., 0., 0.))) * wind_mat;
        }
    }

	fragColor = vec4(fire_color(intensity), 1.);
}