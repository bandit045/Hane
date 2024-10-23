#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0; //for texture
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	float ambientStrength = 0.5;
	vec3 ambient = ambientStrength * lightColor;

	//FragColor = texture(tex0, texCoord);
	FragColor = vec4(ambient * objectColor * color, 1.0) * texture(tex0, texCoord);
}