#include "Light.h"

Light::Light(TypeOfLight typeOfLight)
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
		std::cout << "Invalid argument passed while creating light source object, to Light constructor!";
		throw std::runtime_error("Invalid argument passed while creating light source object, to Light constructor!");
	}
}

Light::DirectionalLightParameters& Light::setDirectionLightParams()
{
	if (activeLight == 1)
	{
		return directionalLightParameters;
	}
	if (activeLight != 1) {
		std::cout << "You can`t edit Directional Light Params, at object light that are not Directional Light Type!";
		throw std::runtime_error("You can`t edit Directional Light Params, at object light that are not Directional Light Type");
	}
} // Both getter and setter
Light::PointLightParameters& Light::setPointLightParams() 
{
	if (activeLight == 0)
	{
		return pointLightParameters;
	}
	if (activeLight != 0) {
		std::cout << "You can`t edit Point Light Params, at object light that are not Point Light Type!";
		throw std::runtime_error("You can`t edit Point Light Params, at object light that are not Point Light Type!");
	}
} // Both getter and setter

const Light::PointLightParameters& Light::getPointLightParams() const
{
	if (activeLight == (int)TypeOfLight::POINT_LIGHT)
	{
		return pointLightParameters;
	}
	if (activeLight != (int)TypeOfLight::POINT_LIGHT) {
		std::cout << "You can`t get Point Light Params, at object light that are not Point Light Type!";
		throw std::runtime_error("You can`t get Point Light Params, at object light that are not Point Light Type!");
	}
};
const Light::DirectionalLightParameters& Light::getDirectionLightParams() const
{
	if (activeLight == (int)TypeOfLight::DIRECTIONAL_LIGHT)
	{
		return directionalLightParameters;
	}
	if (activeLight != (int)TypeOfLight::DIRECTIONAL_LIGHT) {
		std::cout << "You can`t get Directional Light Params, at object light that are not Directional Light Type!";
		throw std::runtime_error("You can`t get Directional Light Params, at object light that are not Directional Light Type!");
	}
};