#version 330 core

struct Material{
	vec3 objectColor;
	float ambientStrenght;
	float diffuseStrenght;
	float specularStrength;
	float shininessBlinnPhong;
	float shininessPhong;
};
struct Texture{
	sampler2D tex0; //For base texture
	sampler2D tex1; //For specular efect
};
struct Light{
	vec3 lightColor;
	vec3 lightPos;
};
struct ControlsOfState{
	bool blinnPhong_switch;
	bool specularMap_Switch;
};

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 Normal;
in vec3 crntPos;

uniform vec3 camPos;

uniform Material material;
uniform Light light;
uniform ControlsOfState control;
uniform Texture textures;

void main()
{
	// ambient lighting
	float ambientStrenght = material.ambientStrenght;

	// diffuse lighting
	float diffuseStrenght =  material.diffuseStrenght;
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(light.lightPos - crntPos);
	float diff = max(dot(normal, lightDirection), 0.0f);
	float diffuse = diff * diffuseStrenght;

	// specular lighting
	float specularStrength = material.specularStrength;
	float specular;
	if(control.blinnPhong_switch) // P-O
	{
		vec3 viewDir    = normalize(camPos - crntPos);
		vec3 halfwayDir = normalize(lightDirection + viewDir);
		float specAmount = pow(max(dot(normal, halfwayDir), 0.0f), material.shininessBlinnPhong);
		specular = specAmount * specularStrength;
	}
	else
	{
		vec3 viewDirection = normalize(camPos - crntPos);
		vec3 reflectionDirection = reflect(-lightDirection, normal);
		float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), material.shininessPhong);
		specular = specAmount * specularStrength;
	}

	// Assuming lightColor is vec3
	vec4 lightColorVec4 = vec4(light.lightColor, 1.0);  // Convert lightColor to vec4

	// Combine lighting components
	if (control.specularMap_Switch)  // M-N key
	{
		// If tex1 is used as a specular map
		FragColor = texture(textures.tex0, texCoord) * ((diffuse + ambientStrenght) + vec4(texture(textures.tex1, texCoord).r) * specular) * lightColorVec4 ;  // Ensure specular is multiplied correctly
	}
	else
	{
		FragColor = texture(textures.tex0, texCoord) * ((ambientStrenght + diffuse + specular) * lightColorVec4);
	}
	
	//FragColor = texture(tex0, texCoord);
	//FragColor = vec4(ambient * objectColor * color, 1.0);
}