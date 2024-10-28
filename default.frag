#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 Normal;
in vec3 crntPos;

uniform sampler2D tex0; //for texture
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;
uniform bool blinnPhong_switch;

void main()
{
	// ambient lighting
	float ambientStrenght = 0.2;
	vec3 ambient = ambientStrenght * lightColor * objectColor;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);
	vec3 diffuseComponent = diffuse * lightColor;

	// specular lighting
	float specularStrength = 0.5f;
	vec3 specular;
	if(blinnPhong_switch)
	{
		vec3 viewDir    = normalize(camPos - crntPos);
		vec3 halfwayDir = normalize(lightDirection + viewDir);
		float specAmount = pow(max(dot(normal, halfwayDir), 0.0f), 16);
		specular = specAmount * lightColor * specularStrength * vec3(1.0);
	}
	else
	{
		vec3 viewDirection = normalize(camPos - crntPos);
		vec3 reflectionDirection = reflect(-lightDirection, normal);
		float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
		specular = specAmount * specularStrength * lightColor * vec3(1.0);
	}

    // Combine lighting components
    vec3 lightEffect = ambient + diffuseComponent + specular;
    FragColor = vec4(lightEffect , 1.0) * texture(tex0, texCoord);	

	//FragColor = texture(tex0, texCoord);
	//FragColor = vec4(ambient * objectColor * color, 1.0);
}

