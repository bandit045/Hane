#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>
#include <glm/glm.hpp>
#include <variant>

class Light {
private:
	struct PointLightParameters{
		float exponentForPointLight = 2.0f;
		float linearTerm_Kl = 0.7f;
		float quadraticTerm_Kq = 1.8f;
		float constantTerm_Kc = 1.0f;
	};
	PointLightParameters pointLightParameters;
	struct DirectionalLightParameters{
		glm::vec3 lightDirection = glm::vec3(-0.2f, 0.5f, 0.4f);
	};
	DirectionalLightParameters directionalLightParameters;

	std::variant<PointLightParameters, DirectionalLightParameters> parameters;
public:
	enum class TypeOfLight {

		POINT_LIGHT = 0,
		DIRECTIONAL_LIGHT = 1
	};
	int activeLight = -1;
	Light(TypeOfLight typeOfLight);

	PointLightParameters& pointLightParams();
	DirectionalLightParameters& directionLightParams();
};

#endif // !LIGHT_H