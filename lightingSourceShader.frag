#version 330 core
out vec4 FragColor;

uniform vec4 lightColor;

in vec3 FragNormal;

void main()
{
    FragColor = lightColor * vec4(FragNormal, 1.0f); 
}