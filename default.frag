#version 330 core

struct Material{
	vec4 objectColor;
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
	vec4 lightColor;
	vec3 lightPos;
	vec3 direction;
	
	bool  isPointLightReducingOnDistance;
	int exponentForPointLight;
	float linearTerm_Kl; // For reducing light strenght becouse of distande of impact for point light
	float quadraticTerm_Kq; // For reducing light strenght becouse of distande of impact for point light
	float constantTerm_Kc; // For reducing light strenght becouse of distande of impact for point light
};
struct ControlsOfState{
	bool phong_switch;
	bool blinnPhong_switch;

	bool specularMap_Switch;

	bool isDirectionalLight;
	bool isPointLight;
};

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 Normal;
in vec3 crntPos;
in vec3 vertNormal;

uniform vec3 camPos;

uniform Material material;
uniform Light light;
uniform ControlsOfState control;
uniform Texture textures;

float lightProportinalToDistance(bool isPointLightReducingOnDistance);
vec3 directionLightOrPointLight(bool pointLight, bool directionalLight);

void main()
{	
	// Strenght of lighting components
	float ambientStrenght  = material.ambientStrenght;
	float diffuseStrenght  = material.diffuseStrenght;
	float specularStrength = material.specularStrength;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	//vec3 lightDirection = normalize(light.lightPos - crntPos);
	vec3 lightDirection = directionLightOrPointLight(control.isPointLight, control.isDirectionalLight);
	float diff = max(dot(normal, lightDirection), 0.0f);
	float diffuse = diff * diffuseStrenght;

	// specular lighting
	float specAmount;
	vec3 viewDirection = normalize(camPos - crntPos);
	if(control.blinnPhong_switch && !control.phong_switch){ // can be switched on P - O key
		vec3 halfwayDir  = normalize(lightDirection + viewDirection);
		specAmount       = pow(max(dot(normal, halfwayDir), 0.0f), material.shininessBlinnPhong);
	}
	else if(!control.blinnPhong_switch && control.phong_switch){
		vec3 reflectionDirection = reflect(-lightDirection, normal);
		specAmount               = pow(max(dot(viewDirection, reflectionDirection), 0.0f), material.shininessPhong);
	}
	float specular = specAmount * specularStrength;

	// specural map control on/off
	if (control.specularMap_Switch){ // can be switched on M - N key
		FragColor = texture(textures.tex0, texCoord) * ((diffuse + ambientStrenght) + vec4(texture(textures.tex1, texCoord).r) * specular) * light.lightColor * lightProportinalToDistance(light.isPointLightReducingOnDistance);
	}
	else{
		FragColor = texture(textures.tex0, texCoord) * ((ambientStrenght + diffuse + specular) * light.lightColor) * lightProportinalToDistance(light.isPointLightReducingOnDistance);
	}
}

float lightProportinalToDistance(bool isPointLightReducingOnDistance)
{
	if(!isPointLightReducingOnDistance){return 1.0f;};
	float constantTerm_Kc = light.constantTerm_Kc;
	float linearTerm_Kl = light.linearTerm_Kl;
	float quadraticTerm_Kq = light.quadraticTerm_Kq;

	float distanceLightSourceToFragment = length(light.lightPos - crntPos);
	return 1.0f / (constantTerm_Kc + linearTerm_Kl * distanceLightSourceToFragment + quadraticTerm_Kq * pow(distanceLightSourceToFragment, light.exponentForPointLight));
};

vec3 directionLightOrPointLight(bool ispointLight, bool isdirectionalLight){
	if(isdirectionalLight && !ispointLight){
		return normalize(-light.direction);
	}
	else if(ispointLight && !isdirectionalLight){
		return normalize(light.lightPos - crntPos);
	};
};