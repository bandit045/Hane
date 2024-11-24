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
	struct PointLightParameters{
		float exponentForPointLight = 2.0f;
		float linearTerm_Kl = 0.7f;
		float quadraticTerm_Kq = 1.8f;
		float constantTerm_Kc = 1.0f;

		float overallLightBrightness = 1.0f; //  Lower the constant parameter towards 0.0 to increase overall brightness, but don’t make it negative since that would break the formula.
	};
	PointLightParameters pointLightParameters;
	struct DirectionalLightParameters{
		glm::vec3 lightDirection = glm::vec3(-0.2f, 0.5f, 0.4f);
	};
	DirectionalLightParameters directionalLightParameters;

	std::variant<PointLightParameters, DirectionalLightParameters> parameters;
public:
	int activeLight = -1;
	Light(TypeOfLight typeOfLight);

	PointLightParameters& setPointLightParams();
	DirectionalLightParameters& setDirectionLightParams();

	const PointLightParameters& getPointLightParams() const; 
	const DirectionalLightParameters& getDirectionLightParams() const;
};

#endif // !LIGHT_H