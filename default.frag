#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 Normal;
in vec3 crntPos;

uniform sampler2D tex0; //for texture
uniform sampler2D tex1; //for texture
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

uniform bool blinnPhong_switch;
uniform bool specularMap_Switch;

void main()
{
	// ambient lighting
	float ambient = 0.2;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularStrength = 0.5f;
	float specular;
	if(blinnPhong_switch)
	{
		vec3 viewDir    = normalize(camPos - crntPos);
		vec3 halfwayDir = normalize(lightDirection + viewDir);
		float specAmount = pow(max(dot(normal, halfwayDir), 0.0f), 16);
		specular = specAmount * specularStrength;
	}
	else
	{
		vec3 viewDirection = normalize(camPos - crntPos);
		vec3 reflectionDirection = reflect(-lightDirection, normal);
		float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
		specular = specAmount * specularStrength;
	}

	// Assuming lightColor is vec3
	vec4 lightColorVec4 = vec4(lightColor, 1.0);  // Convert lightColor to vec4

	// Combine lighting components
	if (specularMap_Switch)  // M key
	{
		// If tex1 is used as a specular map
		FragColor = texture(tex0, texCoord) * ((diffuse + ambient) + vec4(texture(tex1, texCoord).r) * specular) * lightColorVec4 ;  // Ensure specular is multiplied correctly
	}
	else
	{
		FragColor = texture(tex0, texCoord) * ((ambient + diffuse + specular) * lightColorVec4);
	}
	
	//FragColor = texture(tex0, texCoord);
	//FragColor = vec4(ambient * objectColor * color, 1.0);
}

