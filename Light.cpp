#include "Light.h"

Light::Light(Light::TypeOfLight typeOfLight)
{
	if (typeOfLight == TypeOfLight::POINT_LIGHT)
	{
		activatePointLight();
	}
	else if(typeOfLight == TypeOfLight::DIRECTIONAL_LIGHT)
	{
		activateDirectionalLight();
	}

	// nesluzi nicemu ali da vidim kako se koristi ovo dole
/*	std::get<PointLightParams>(parameters).constantTerm_Kc;
	std::holds_alternative<PointLightParams>(parameters);
	std::cout << parameters.index();*/
}

void Light::setLightDirection(float x, float y, float z){
	directionalLightParams.lightDirection.x = x;
	directionalLightParams.lightDirection.y = y;
	directionalLightParams.lightDirection.z = z;
}

void Light::setLightDirection(glm::vec3 newDirection) {
	directionalLightParams.lightDirection = newDirection;
}

float& Light::getFirstElementOfLightDirection()
{
	return directionalLightParams.lightDirection.x;
}

Light::DirectionalLightParams Light::getDirectionalLightParams()
{
	return directionalLightParams;
};
Light::PointLightParams Light::getPointLightParams()
{
	return pointLightParams;
};
int Light::getIndexOfCurcurentActiveLight()
{
	return parameters.index();
};
void Light::activateDirectionalLight()
{
	parameters = directionalLightParams;
}
void Light::activatePointLight()
{
	parameters = pointLightParams;
}