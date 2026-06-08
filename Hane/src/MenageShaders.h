#ifndef MENAGE_SHADERS_H
#define MENAGE_SHADERS_H

#include "Shader.h"

enum class DefaultShader
{
	FOR_OBJECTS,
	FOR_LIGHT
};

class MenageShaders
{
public:
	static void setDefaultShadersForAllID(GLuint& defaultShaderForObjectsID, GLuint& defaultShaderForLightsID);
	// This static function is used as geter to get default shader for diferent objects, it request ENUM "DefaultShader" argument
	static GLuint& getDefaultShaderID(DefaultShader defaultShader);
private:
	static GLuint* m_defaultShaderForObjectsID;
	static GLuint* m_defaultShaderForLightID;
};

#endif // !MENAGE_SHADERS_H*/