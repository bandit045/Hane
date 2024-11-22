#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>
#include <glm/glm.hpp>
#include <variant>

class Light {
private:

	struct PointLightParams{
		float exponentForPointLight = 2.0f;
		float linearTerm_Kl = 0.7f;
		float quadraticTerm_Kq = 1.8f;
		float constantTerm_Kc = 1.0f;
	};
	PointLightParams pointLightParams;
	struct DirectionalLightParams{
		glm::vec3 lightDirection = glm::normalize(glm::vec3(-0.2f, 0.5f, 0.4f));
	};
	DirectionalLightParams directionalLightParams;

	std::variant<PointLightParams, DirectionalLightParams> parameters;

	void activatePointLight();
	void activateDirectionalLight();
public:
	enum class TypeOfLight {

		POINT_LIGHT = 0,
		DIRECTIONAL_LIGHT = 1
	};
	Light(TypeOfLight typeOfLight);

	DirectionalLightParams getDirectionalLightParams();
	PointLightParams getPointLightParams();
	void setLightDirection(glm::vec3 newDirection);
	void setLightDirection(float x, float y, float z);

	float& getFirstElementOfLightDirection();

	int getIndexOfCurcurentActiveLight();
};

#endif // !LIGHT_H