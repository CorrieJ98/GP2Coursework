#version 400

in vec2 TexCoord;
out vec4 FragColor;

// Parameters for the brick pattern
uniform vec3 brickColor = vec3(0.8, 0.3, 0.2);
uniform vec3 mortarColor = vec3(0.9, 0.9, 0.9);
uniform vec2 brickSize = vec2(0.3, 0.15);
uniform vec2 brickPct = vec2(0.8, 0.9); // Percentage of brick occupied (rest is mortar)

void main()
{
    // Scale texture coordinates to brick space
    vec2 position = TexCoord / brickSize;

    // Offset every other row to create the brick pattern
    if (mod(floor(position.y), 2.0) == 1.0)
        position.x += 0.5;

    // Find the fractional part (0-1) of the brick space position
    vec2 f = fract(position);

    // Determine whether we are inside a brick or in the mortar
    if (f.x > brickPct.x || f.y > brickPct.y)
        FragColor = vec4(mortarColor, 1.0); // Mortar
    else
        FragColor = vec4(brickColor, 1.0);   // Brick
}
