#version 330 core

#define control.isDirectionalLight killme[]

struct Material{
	vec4 objectColor;
	float ambientStrenght;
	float diffuseStrenght;
	float specularStrength;
	float shininessStrenght;
};
struct Texture{
	sampler2D baseTexture; //For base texture
	sampler2D specularMap; //For specular efect
};
struct Light{
	vec4 lightColor;
	vec3 lightPos;
	vec3 lightDirection;
	
	float exponentForPointLight;
	float linearTerm_Kl; // For reducing light strenght becouse of distande of impact for point light
	float quadraticTerm_Kq; // For reducing light strenght becouse of distande of impact for point light
	float constantTerm_Kc; // For reducing light strenght becouse of distande of impact for point light

	float overallLightBrightness; //  Lower the constant parameter towards 0.0 to increase overall brightness, but don’t make it negative since that would break the formula.
};
layout (std140) uniform ControlsOfState{
	bool isPointLightReducingOnDistance;
	bool isPhong;
	bool isBlinnPhong;
	bool isSpecularMap;
	bool isDirectionalLight;
	bool isPointLight;
	bool isAutomaticLuminosity;
	bool isManuelLuminosity;
} control;

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 Normal;
in vec3 crntPos;
in vec3 vertNormal;

uniform vec3 camPos;

uniform Material material;
uniform Light light;
//uniform ControlsOfState control;
uniform Texture textures;

float specAmount(vec3 viewDirection, vec3 lightDirection, vec3 normal);
float luminosityCalculation(bool isPointLightReducingOnDistance, bool isAutomaticLuminosity, bool isManuelLuminosity, float overallLightBrightness);
vec3 directionLightOrPointLight();
vec4 finalFragColor(float diffuse, float ambientStrenght, float specular);

void main()
{	
	// Strenght of lighting components
	float ambientStrenght  = material.ambientStrenght;
	float diffuseStrenght  = material.diffuseStrenght;
	float specularStrength = material.specularStrength;

	// Diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = directionLightOrPointLight();
	float diff = max(dot(normal, lightDirection), 0.0f);
	float diffuse = diff * diffuseStrenght;

	// Specular lighting
	vec3 viewDirection = normalize(camPos - crntPos);
	float specAmount = specAmount(viewDirection, lightDirection, normal);
	float specular = specAmount * specularStrength;

	// Calculating final result
	FragColor = finalFragColor(diffuse, ambientStrenght, specular);
}

float luminosityCalculation(bool isPointLightReducingOnDistance, bool isAutomaticLuminosity, bool isManuelLuminosity, float overallLightBrightness){
	if(!isPointLightReducingOnDistance){return 1.0f;};
	float distanceLightSourceToFragment = length(light.lightPos - crntPos);

	float constantTerm_Kc;
	float linearTerm_Kl;
	float quadraticTerm_Kq;
	if(isAutomaticLuminosity)
	{
		constantTerm_Kc = 1.0;   
		linearTerm_Kl = 4.5/distanceLightSourceToFragment; 
		quadraticTerm_Kq = 75.0 / sqrt(distanceLightSourceToFragment);
		return 1.0f / ((constantTerm_Kc * max(0, overallLightBrightness)) + linearTerm_Kl * distanceLightSourceToFragment + quadraticTerm_Kq * pow(distanceLightSourceToFragment, 2));
	}
	else if(isManuelLuminosity)
	{
		constantTerm_Kc = light.constantTerm_Kc;
		linearTerm_Kl = light.linearTerm_Kl;
		quadraticTerm_Kq = light.quadraticTerm_Kq;
		return 1.0f / (constantTerm_Kc + linearTerm_Kl * distanceLightSourceToFragment + quadraticTerm_Kq * pow(distanceLightSourceToFragment, light.exponentForPointLight));
	}
};

vec3 directionLightOrPointLight(){
	if(control.isDirectionalLight && !control.isPointLight){
		return normalize(light.lightDirection);
	}
	else if(control.isPointLight && !control.isDirectionalLight){
		return normalize(light.lightPos - crntPos);
	};
};
vec4 finalFragColor(float diffuse, float ambientStrenght, float specular){
	if (control.isSpecularMap){ // Can be switched on M - N key
		return texture(textures.baseTexture, texCoord) * (ambientStrenght + diffuse + texture(textures.specularMap, texCoord).r * specular) * light.lightColor * luminosityCalculation(control.isPointLightReducingOnDistance, control.isAutomaticLuminosity, control.isManuelLuminosity, light.overallLightBrightness);
	}
	else{
		return texture(textures.baseTexture, texCoord) * (ambientStrenght + diffuse + specular) * light.lightColor * luminosityCalculation(control.isPointLightReducingOnDistance, control.isAutomaticLuminosity, control.isManuelLuminosity, light.overallLightBrightness);
	}
}
float specAmount(vec3 viewDirection, vec3 lightDirection, vec3 normal){
	
	if(control.isBlinnPhong && !control.isPhong){ // can be switched on P - O key
		vec3 halfwayDir  = normalize(lightDirection + viewDirection);
		return pow(max(dot(normal, halfwayDir), 0.0f), material.shininessStrenght);
	}
	else if(!control.isBlinnPhong && control.isPhong){
		vec3 reflectionDirection = reflect(-lightDirection, normal);
		return pow(max(dot(viewDirection, reflectionDirection), 0.0f), material.shininessStrenght);
	}
};