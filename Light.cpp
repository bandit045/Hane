#include "Light.h"

Light::Light(Light::TypeOfLight typeOfLight)
{
	if (typeOfLight == TypeOfLight::POINT_LIGHT)
	{
		activeLight = (int)TypeOfLight::POINT_LIGHT; // 0 - Point Light, 1 - Directional Light
		parameters = pointLightParameters;
	}
	else if(typeOfLight == TypeOfLight::DIRECTIONAL_LIGHT)
	{
		activeLight = (int)TypeOfLight::DIRECTIONAL_LIGHT; // 0 - Point Light, 1 - Directional Light
		parameters = directionalLightParameters;
	}
	else
	{
		std::cout << "Invalid argument!";
		throw std::runtime_error("Invalid argument!");
	}
}

Light::DirectionalLightParameters& Light::directionLightParams()
{
	if (activeLight == 1)
	{
		return directionalLightParameters;
	}
	if (activeLight != 1) {
		std::cout << "You can`t edit Directional Light Params, at object light that are not Directional Light Type!";
		throw std::runtime_error("Invalid light type for directional parameters!");
	}
}
Light::PointLightParameters& Light::pointLightParams()
{
	if (activeLight == 0)
	{
		return pointLightParameters;
	}
	if (activeLight != 0) {
		std::cout << "You can`t edit Point Light Params, at object light that are not Point Light Type!";
		throw std::runtime_error("Invalid light type for point parameters!");
	}
}