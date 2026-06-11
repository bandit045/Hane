#include "Light.h"

Light::Light(TypeOfLight typeOfLight)
{
	if (typeOfLight == TypeOfLight::POINT_LIGHT)
	{
		activeLight = (int)TypeOfLight::POINT_LIGHT;       // 0 - Point Light, 1 - Directional Light, 2 - Spot Light
		m_parameters = m_pointLightParameters;
	}
	else if(typeOfLight == TypeOfLight::DIRECTIONAL_LIGHT)
	{
		activeLight = (int)TypeOfLight::DIRECTIONAL_LIGHT; // 0 - Point Light, 1 - Directional Light, 2 - Spot Light
		m_parameters = m_directionalLightParameters;
	}
	else if (typeOfLight == TypeOfLight::SPOT_LIGHT)
	{
		activeLight = (int)TypeOfLight::SPOT_LIGHT;        // 0 - Point Light, 1 - Directional Light, 2 - Spot Light
		m_parameters = m_spotLightParameters;
	}
	else
	{
		std::cout << "Invalid argument passed while creating light source object, to Light constructor!";
		throw std::runtime_error("Invalid argument passed while creating light source object, to Light constructor!");
	}
}

// TODO return std::expected, std::unexpected ReWork, dabi koristio std::expected on je u C++23 a VS19 maksimalno ima verziju C++20, tako da prvo PREMAKE

Light::DirectionalLightParameters& Light::setDirectionLightParams()
{
	if (activeLight == (int)TypeOfLight::DIRECTIONAL_LIGHT)
		return m_directionalLightParameters;

	std::cout << "You can`t edit Directional Light Params, at object light that are not Directional Light Type!";
	throw std::runtime_error("You can`t edit Directional Light Params, at object light that are not Directional Light Type");
}
Light::PointLightParameters& Light::setPointLightParams() 
{
	if (activeLight == (int)TypeOfLight::POINT_LIGHT)
		return m_pointLightParameters;

	std::cout << "You can`t edit Point Light Params, at object light that are not Point Light Type!";
	throw std::runtime_error("You can`t edit Point Light Params, at object light that are not Point Light Type!");
}
Light::SpotLightParameters& Light::setSpotLightParams()
{
	if (activeLight == (int)TypeOfLight::SPOT_LIGHT)
		return m_spotLightParameters;

	std::cout << "You can`t edit Spot Light Params, at object light that are not Spot Light Type!";
	throw std::runtime_error("You can`t edit Spot Light Params, at object light that are not Spot Light Type!");
}
Light::SpotLightParameters& Light::setSpotLightParams(bool _limitInnerCuttOffToBeSmaller)
{
	if (m_spotLightParameters.innerCutOff >= m_spotLightParameters.outerCutOff)
	{
		m_spotLightParameters.innerCutOff = m_spotLightParameters.outerCutOff;
	}
	return m_spotLightParameters;
}


// -------------------------GETERS-----------------------------------------------
const Light::PointLightParameters& Light::getPointLightParams() const
{
	if (activeLight == (int)TypeOfLight::POINT_LIGHT)
		return m_pointLightParameters;

	std::cout << "You can`t get Point Light Params, at object light that are not Point Light Type!";
	throw std::runtime_error("You can`t get Point Light Params, at object light that are not Point Light Type!");
};
const Light::DirectionalLightParameters& Light::getDirectionLightParams() const
{
	if (activeLight == (int)TypeOfLight::DIRECTIONAL_LIGHT)
		return m_directionalLightParameters;

	std::cout << "You can`t get Directional Light Params, at object light that are not Directional Light Type!";
	throw std::runtime_error("You can`t get Directional Light Params, at object light that are not Directional Light Type!");
};
const Light::SpotLightParameters& Light::getSpotLightParams() const
{
	if (activeLight == (int)TypeOfLight::SPOT_LIGHT)
		return m_spotLightParameters;

	std::cout << "You can`t get Spot Light Params, at object light that are not Spot Light Type!";
	throw std::runtime_error("You can`t get Spot Light Params, at object light that are not Spot Light Type!");
}