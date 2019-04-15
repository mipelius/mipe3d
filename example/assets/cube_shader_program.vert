#version 330 core

layout(location = 0) in vec3 i_vertex;
layout(location = 1) in vec3 i_normal;
layout(location = 2) in vec2 i_uv;

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;
uniform float u_time;

const vec3 lightPositionWorldspace = vec3(2.0f, 10.0f, 5.0f);

out vec2 uv;
out vec3 positionWorldspace;
out vec3 normalViewspace;
out vec3 eyeDirectionViewspace;
out vec3 lightDirectionViewspace;

void main()
{

    gl_Position =
            u_projectionMatrix *
            u_viewMatrix *
            u_modelMatrix *
            vec4(i_vertex, 1.0);

    uv = i_uv;
    
    positionWorldspace = (u_modelMatrix * vec4(i_vertex, 1.0)).xyz;

    vec3 positionViewspace = 
        (u_viewMatrix * u_modelMatrix * vec4(i_vertex, 1.0)).xyz;
    eyeDirectionViewspace = vec3(0.0, 0.0, 0.0) - positionViewspace;

    vec3 lightPositionViewspace = 
        (u_viewMatrix * vec4(lightPositionWorldspace, 1.0)).xyz;
    lightDirectionViewspace = lightPositionViewspace + eyeDirectionViewspace;

    normalViewspace = 
        (u_viewMatrix * u_modelMatrix * vec4(i_normal, 0.0f)).xyz;
}
