#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>
#include <glm/glm.hpp>
#include <variant>

enum class TypeOfLight {

	POINT_LIGHT = 0,
	DIRECTIONAL_LIGHT = 1,
	SPOT_LIGHT = 2
};

class Light {
private:
	// Default parametars for point light
	struct PointLightParameters{
		float exponentForPointLight = 2.0f;
		float linearTerm_Kl = 0.7f;
		float quadraticTerm_Kq = 1.8f;
		float constantTerm_Kc = 1.0f;

		float overallLightBrightness = 1.0f; //  Lower the constant parameter towards 0.0 to increase overall brightness, but don’t make it negative since that would break the formula.
	};
	PointLightParameters m_pointLightParameters;

	// Default parametars for directional light
	struct DirectionalLightParameters{
		glm::vec3 lightDirection = glm::vec3(-0.2f, 0.5f, 0.4f);
	};
	DirectionalLightParameters m_directionalLightParameters;

	// Default parametars for spot light
	struct SpotLightParameters {
		float cutOff = 12.5f;
		glm::vec3 spotLightDirection = glm::vec3(0.0f, -1.0f, 0.0f);
		float innerCutOff = 40.0f;
		float outerCutOff = 46.00f;
		float intensityMultiplayer = 1.0f;
		float thetaMultiplayer = 1.0f;
	};
	SpotLightParameters m_spotLightParameters;

	std::variant<PointLightParameters, DirectionalLightParameters, SpotLightParameters> m_parameters;
public:
	int activeLight = -1;
	Light(TypeOfLight typeOfLight);

	PointLightParameters& setPointLightParams();
	DirectionalLightParameters& setDirectionLightParams();
	SpotLightParameters& setSpotLightParams();
	SpotLightParameters& setSpotLightParams(bool _limitInnerCuttOffToBeSmaller);

	const PointLightParameters& getPointLightParams() const; 
	const DirectionalLightParameters& getDirectionLightParams() const;
	const SpotLightParameters& getSpotLightParams() const;
};

#endif // !LIGHT_H