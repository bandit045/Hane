#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0; //for texture
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	//FragColor = texture(tex0, texCoord);
	FragColor = vec4(lightColor * objectColor, 1.0) * texture(tex0, texCoord);
}