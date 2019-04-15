#version 330 core

in vec2 uv;
in vec3 positionWorldspace;
in vec3 normalViewspace;
in vec3 eyeDirectionViewspace;
in vec3 lightDirectionViewspace;

out vec3 color;

uniform sampler2D u_texture;
uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;

const vec3 lightPositionWorldspace = vec3(2.0f, 10.0f, 5.0f);

const vec3 ambientColor = vec3(0.4, 0.4, 0.4);
const vec3 specularColor = vec3(0.2, 0.2, 0.2);

const vec3 lightColor = vec3(1.0, 1.0, 1.0);
const float lightPower = 100.0f;

void main()
{
    float distance = length(lightPositionWorldspace - positionWorldspace);
    float distancePow2 = distance * distance;

    vec3 n = normalize(normalViewspace);
    vec3 l = normalize(lightDirectionViewspace);
    float cosTheta = clamp(dot(n, l), 0.0, 1.0);

    vec3 e = normalize(eyeDirectionViewspace);
    vec3 r = reflect(-l, n);
    float cosAlpha = clamp(dot(e, r), 0.0, 1.0);

    vec3 textureColor = texture(u_texture, uv).rgb;

    vec3 ambient = ambientColor * textureColor;
    vec3 diffuse = 
        textureColor * lightColor * lightPower * cosTheta / 
        distancePow2;
    vec3 specular =
        specularColor * lightColor * lightPower * pow(cosAlpha, 5.0) / 
        distancePow2;
        
    color = ambient + diffuse + specular;
}
