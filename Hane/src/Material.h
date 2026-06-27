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
	inline void setObjectColor(glm::vec4 newObjectColor) { material.objectColor = newObjectColor; }
	inline void setAmbientStrenght(float newAmbientStrenght) { material.ambientStrenght = newAmbientStrenght; }
	inline void setDiffuseStrenght(float newDiffuseStrenght) { material.diffuseStrenght = newDiffuseStrenght; }
	inline void setSpecularStrenght(float newSpecularStrenght) { material.specularStrength = newSpecularStrenght; }
	inline void setShininessStrenght(float newShininessStrenght) { material.shininessStrenght = newShininessStrenght; }

	inline glm::vec4& getObjectColor() { return material.objectColor; }
	inline float& getAmbientStrenght() { return material.ambientStrenght; }
	inline float& getDiffuseStrenght() { return material.diffuseStrenght; }
	inline float& getSpecularStrenght() { return material.specularStrength; }
	inline float& getShininessStrenght() { return material.shininessStrenght; }
private:
	DefaultParametersForMaterial material;
};

#endif // !MATERIAL_H