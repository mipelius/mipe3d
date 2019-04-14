#version 330 core

layout(location = 0) in vec3 i_vertex;

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;
uniform float u_time;

const float PI = 3.14159;
const float waveAmplitude = 0.1;

out float colorFactor;

void main()
{
    vec3 position = i_vertex;
    position.y = 
        cos(position.x * 2 * PI + u_time) * 
        sin(position.z * 2 * PI + u_time);
    colorFactor = position.y;    
    position.y *= waveAmplitude;

    gl_Position =
            u_projectionMatrix *
            u_viewMatrix *
            u_modelMatrix *
            vec4(position, 1.0);
}
