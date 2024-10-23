#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D tex0; //for texture
uniform sampler2D tex1; //for texture
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	//vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);  

	float diff = max(dot(Normal, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0) * texture(tex0, texCoord);;

	//FragColor = texture(tex0, texCoord);
	//FragColor = vec4(ambient * objectColor * color, 1.0);
}