#version 330 core

layout(location = 0) in vec3 i_vertex;
layout(location = 1) in vec3 i_normal;
layout(location = 2) in vec2 i_uv;

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;
uniform float u_time;

out vec2 uv;

void main()
{
    gl_Position =
            u_projectionMatrix *
            u_viewMatrix *
            u_modelMatrix *
            vec4(i_vertex, 1.0);

    uv = i_uv;
}
