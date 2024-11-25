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
	MenageShaders();
	static void setDefaultShadersForAll(GLuint& defaultShaderForObjects, GLuint& defaultShaderForLights);
	static GLuint& getDefaultShaderID(DefaultShader defaultShader);
private:
	static GLuint* m_defaultShaderForObjects;
	static GLuint* m_defaultShaderForLight;
};

#endif // !MENAGE_SHADERS_H*/