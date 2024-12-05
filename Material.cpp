#include "Material.h"

Material::Material()
{

}

void Material::setObjectColor(glm::vec4 newObjectColor)
{
	material.objectColor = newObjectColor;
}
void Material::setAmbientStrenght(float newAmbientStrenght)
{
	material.ambientStrenght = newAmbientStrenght;
}
void Material::setDiffuseStrenght(float newDiffuseStrenght)
{
	material.diffuseStrenght = newDiffuseStrenght;
}
void Material::setSpecularStrenght(float newSpecularStrenght)
{
	material.specularStrength = newSpecularStrenght;
}
void Material::setShininessStrenght(float newShininessStrenght)
{
	material.shininessStrenght = newShininessStrenght;
}

glm::vec4& Material::getObjectColor()
{
	return material.objectColor;
}
float& Material::getAmbientStrenght()
{
	return material.ambientStrenght;
}
float& Material::getDiffuseStrenght()
{
	return material.diffuseStrenght;
}
float& Material::getSpecularStrenght()
{
	return material.specularStrength;
}
float& Material::getShininessStrenght()
{
	return material.shininessStrenght;
}