#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

struct DefaultParametersForMaterial
{
	glm::vec4 objectColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	float ambientStrenght = 0.6f;
	float diffuseStrenght = 1.9f;
	float specularStrength = 0.5f;
	float shininessStrenght = 16.0f;
};

class Material
{
public:
	Material();
	void setObjectColor(glm::vec4 newMaterialColor);
	void setAmbientStrenght(float newAmbientStrenght);
	void setDiffuseStrenght(float newDiffuseStrenght);
	void setSpecularStrenght(float newSpecularStrenght);
	void setShininessStrenght(float newShininessStrenght);

	glm::vec4& getObjectColor();
	float& getAmbientStrenght();
	float& getDiffuseStrenght();
	float& getSpecularStrenght();
	float& getShininessStrenght();
private:
	DefaultParametersForMaterial material;
};

#endif // !MATERIAL_H