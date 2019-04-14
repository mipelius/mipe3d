#version 330 core

out vec3 color;

in float colorFactor;

uniform float u_time;

void main()
{
    // color is based on the math madness
    color.r = (sin(colorFactor + u_time) + 1.0) / 2.0;
    color.g = 0.0;
    color.b = pow(sin(colorFactor + u_time), 2.0f);
    
    color /= 2.0;
}
