#version 330 core
out vec4 FragColor;

uniform vec4 lightColor;

in vec3 Normal;

void main()
{
    FragColor = lightColor; 
    //vec3 normalizedNormal = normalize(Normal);
    //FragColor = vec4(normalizedNormal * 0.5 + 0.5, 1.0) * lightColor;
}