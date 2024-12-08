#include "Light.h"

Light::Light(TypeOfLight typeOfLight)
{
	if (typeOfLight == TypeOfLight::POINT_LIGHT)
	{
		activeLight = (int)TypeOfLight::POINT_LIGHT; // 0 - Point Light, 1 - Directional Light, 2 - Spot Light
		parameters = pointLightParameters;
	}
	else if(typeOfLight == TypeOfLight::DIRECTIONAL_LIGHT)
	{
		activeLight = (int)TypeOfLight::DIRECTIONAL_LIGHT; // 0 - Point Light, 1 - Directional Light, 2 - Spot Light
		parameters = directionalLightParameters;
	}
	else if (typeOfLight == TypeOfLight::SPOT_LIGHT)
	{
		activeLight = (int)TypeOfLight::SPOT_LIGHT;  // 0 - Point Light, 1 - Directional Light, 2 - Spot Light
		parameters = spotLightParameters;
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
	if (activeLight != 1)
	{
		std::cout << "You can`t edit Directional Light Params, at object light that are not Directional Light Type!";
		throw std::runtime_error("You can`t edit Directional Light Params, at object light that are not Directional Light Type");
	}
}
Light::PointLightParameters& Light::setPointLightParams() 
{
	if (activeLight == 0)
	{
		return pointLightParameters;
	}
	if (activeLight != 0)
	{
		std::cout << "You can`t edit Point Light Params, at object light that are not Point Light Type!";
		throw std::runtime_error("You can`t edit Point Light Params, at object light that are not Point Light Type!");
	}
}
Light::SpotLightParameters& Light::setSpotLightParams()
{
	if (activeLight == 2)
	{
		return spotLightParameters;
	}
	if (activeLight != 2)
	{
		std::cout << "You can`t edit Spot Light Params, at object light that are not Spot Light Type!";
		throw std::runtime_error("You can`t edit Spot Light Params, at object light that are not Spot Light Type!");
	}
}

const Light::PointLightParameters& Light::getPointLightParams() const
{
	if (activeLight == (int)TypeOfLight::POINT_LIGHT)
	{
		return pointLightParameters;
	}
	if (activeLight != (int)TypeOfLight::POINT_LIGHT) 
	{
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
	if (activeLight != (int)TypeOfLight::DIRECTIONAL_LIGHT)
	{
		std::cout << "You can`t get Directional Light Params, at object light that are not Directional Light Type!";
		throw std::runtime_error("You can`t get Directional Light Params, at object light that are not Directional Light Type!");
	}
};
const Light::SpotLightParameters& Light::getSpotLightParams() const
{
	if (activeLight == (int)TypeOfLight::SPOT_LIGHT)
	{
		return spotLightParameters;
	}
	if (activeLight != (int)TypeOfLight::SPOT_LIGHT)
	{
		std::cout << "You can`t get Spot Light Params, at object light that are not Spot Light Type!";
		throw std::runtime_error("You can`t get Spot Light Params, at object light that are not Spot Light Type!");
	}
}