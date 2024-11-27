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
	//static void setDefaultShadersForAllProgram(Shader& defaultShaderForObjectsProgram, Shader& defaultShaderForLightsProgram);
	static GLuint& getDefaultShaderID(DefaultShader defaultShader);
	//static Shader& getDefaultShaderProgram(DefaultShader defaultShader);
private:
	static GLuint* m_defaultShaderForObjectsID;
	static GLuint* m_defaultShaderForLightID;

	//static Shader* m_defaultShaderForObjectsProgram;
	//static Shader* m_defaultShaderForLightProgram;
};

#endif // !MENAGE_SHADERS_H*/