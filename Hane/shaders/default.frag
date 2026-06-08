#version 330 core

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
	// Basic Light parameters transform color etc
	vec4 lightColor;
	vec3 lightPos;

	// Parameters for Directional(Sun) Light
	vec3 lightDirection;
	
	// Parametes for Point Light
	float exponentForPointLight; // For reducing light strenght becouse of distande of impact for point light
	float linearTerm_Kl;         // For reducing light strenght becouse of distande of impact for point light
	float quadraticTerm_Kq;      // For reducing light strenght becouse of distande of impact for point light
	float constantTerm_Kc;       // For reducing light strenght becouse of distande of impact for point light

	// Parameters for Spot Light
	vec3 spotLightDirection;
	float intensityMultiplayer;
	float thetaMultiplayer;
	float innerCutOff;
	float outerCutOff;
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
	bool isLightTurnOff;
	bool isSpotLight;
	bool isVisualiseNormal;
	bool isVisualiseUVCordinate;
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
uniform Texture textures;

float specAmountFunction(vec3 viewDirection, vec3 lightDirection, vec3 normal);
float luminosityCalculation(bool isPointLightReducingOnDistance);
//vec3 directionLightOrPointLight();
//vec4 finalFragColor(float diffuse, float ambientStrenght, float specular);
void spotLightCalculation(float _ambientStrenght, float _diffuseStrenght, float _specularStrength, float _intensityMultiplayer, float _thetaMultiplayer);

void main()
{	
	// Strenght of lighting components
	float ambientStrenght  = material.ambientStrenght;
	float diffuseStrenght  = material.diffuseStrenght;
	float specularStrength = material.specularStrength;

	// Diffuse lighting
	vec3 normal = normalize(Normal);
	/*vec3 lightDirection = directionLightOrPointLight();
	float diff = max(dot(normal, lightDirection), 0.0f);
	float diffuse = diff * diffuseStrenght;*/

	// Specular lighting
	vec3 viewDirection = normalize(camPos - crntPos);
	/*float specAmount = specAmountFunction(viewDirection, lightDirection, normal);
	float specular = specAmount * specularStrength;*/

	// Calculating final result
	if(control.isSpotLight){

		spotLightCalculation(ambientStrenght, diffuseStrenght, specularStrength, light.intensityMultiplayer, light.thetaMultiplayer);
	}
	else if(control.isDirectionalLight){ // If directional light is used
	
		vec3 lightDirection = normalize(light.lightDirection);
		float diff = max(dot(normal, lightDirection), 0.0f);
		float diffuse = diff * diffuseStrenght;

		float specAmount = specAmountFunction(viewDirection, lightDirection, normal);
		float specular = specAmount * specularStrength;

		if (control.isSpecularMap) // If specular map is used while it is directional light
		{
			FragColor = texture(textures.baseTexture, texCoord) * (ambientStrenght + diffuse + texture(textures.specularMap, texCoord).r * specular) * light.lightColor;
		}
		else if(!control.isSpecularMap) // If specular map is not used in directional light
		{
			FragColor = texture(textures.baseTexture, texCoord) * (ambientStrenght + diffuse +/*texture(textures.specularMap, texCoord).r */specular) * light.lightColor;
		}
	}
	else if(control.isPointLight){ // If point light is used

	    vec3 lightDirection = normalize(light.lightPos - crntPos);
		float diff = max(dot(normal, lightDirection), 0.0f);
		float diffuse = diff * diffuseStrenght;

		float specAmount = specAmountFunction(viewDirection, lightDirection, normal);
		float specular = specAmount * specularStrength;

		if (control.isSpecularMap){ // If specular map is used while it is point light
			
			FragColor = texture(textures.baseTexture, texCoord) * (ambientStrenght + diffuse + texture(textures.specularMap, texCoord).r * specular) * light.lightColor * luminosityCalculation(control.isPointLightReducingOnDistance);
		}
		else if(!control.isSpecularMap){ // If specular map is not used in point light
		
			FragColor = texture(textures.baseTexture, texCoord) * (ambientStrenght + diffuse +/*texture(textures.specularMap, texCoord).r */specular) * light.lightColor * luminosityCalculation(control.isPointLightReducingOnDistance);
		}
	}
	else if(control.isVisualiseNormal){ // Debug purpose to visualise normals
		
		vec3 normalizedNormal = normalize(Normal);
		FragColor = vec4(normalizedNormal * 0.5 + 0.5, 1.0);
	}
	else if(control.isVisualiseUVCordinate){  // Debug purpose to visalise UV coordinates
		
		FragColor = vec4(texCoord, 0.0, 1.0);
	}
	else{ // If light is turned off or some weird things to not get only black
		
		FragColor = texture(textures.baseTexture, texCoord) * ambientStrenght;
	}
	}

float luminosityCalculation(bool isPointLightReducingOnDistance){
	if(!isPointLightReducingOnDistance){return 1.0f;};
	float distanceLightSourceToFragment = length(light.lightPos - crntPos);

	float constantTerm_Kc;
	float linearTerm_Kl;
	float quadraticTerm_Kq;

	constantTerm_Kc = light.constantTerm_Kc;
	linearTerm_Kl = light.linearTerm_Kl;
	quadraticTerm_Kq = light.quadraticTerm_Kq;
	return 1.0f / (constantTerm_Kc + linearTerm_Kl * distanceLightSourceToFragment + quadraticTerm_Kq * pow(distanceLightSourceToFragment, light.exponentForPointLight));
};
/*vec3 directionLightOrPointLight(){
	if(control.isDirectionalLight && !control.isPointLight){
		return normalize(light.lightDirection);
	}
	else if(control.isPointLight && !control.isDirectionalLight){
		return normalize(light.lightPos - crntPos);
	};
};*/
/*vec4 finalFragColor(float diffuse, float ambientStrenght, float specular){
	if (control.isSpecularMap){
		return texture(textures.baseTexture, texCoord) * (ambientStrenght + diffuse + texture(textures.specularMap, texCoord).r * specular) * light.lightColor * luminosityCalculation(control.isPointLightReducingOnDistance);
	}
	else{
		return texture(textures.baseTexture, texCoord) * (ambientStrenght + diffuse + specular) * light.lightColor * luminosityCalculation(control.isPointLightReducingOnDistance);
	}
}*/
float specAmountFunction(vec3 viewDirection, vec3 lightDirection, vec3 normal){
	
	if(control.isBlinnPhong && !control.isPhong){
		vec3 halfwayDir  = normalize(lightDirection + viewDirection);
		return pow(max(dot(normal, halfwayDir), 0.0f), material.shininessStrenght);
	}
	else if(!control.isBlinnPhong && control.isPhong){
		vec3 reflectionDirection = reflect(-lightDirection, normal);
		return pow(max(dot(viewDirection, reflectionDirection), 0.0f), material.shininessStrenght);
	}
};
void spotLightCalculation(float _ambientStrenght, float _diffuseStrenght, float _specularStrength, float _intensityMultiplayer, float _thetaMultiplayer){

	vec3 lightDir = normalize(light.lightPos - crntPos);

	float theta = dot(normalize(-light.spotLightDirection), lightDir);
	if(theta > light.outerCutOff)// Ako dobijemo da se pixeli nalaze u cone onda ide ovo
	{       
		float intensity = smoothstep(theta * _thetaMultiplayer, light.outerCutOff, light.innerCutOff) * _intensityMultiplayer;
		FragColor = texture(textures.baseTexture, texCoord) * (_ambientStrenght + intensity * (_diffuseStrenght + _specularStrength )) * light.lightColor;
				 
	}
	else // For the outside of cone 
	{
		FragColor = texture(textures.baseTexture, texCoord) * _ambientStrenght;
	}
}