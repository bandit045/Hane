#include "MenageShaders.h"

GLuint* MenageShaders::m_defaultShaderForObjects = 0;
GLuint* MenageShaders::m_defaultShaderForLight = 0;

MenageShaders::MenageShaders()
{

}

void MenageShaders::setDefaultShadersForAll(GLuint& defaultShaderForObjects, GLuint& defaultShaderForLights)
{
	m_defaultShaderForObjects = &defaultShaderForObjects;
	m_defaultShaderForLight = &defaultShaderForLights;
};

GLuint& MenageShaders::getDefaultShaderID(DefaultShader defaultShader)
{
	if (DefaultShader::FOR_OBJECTS == defaultShader)
	{
		return *m_defaultShaderForObjects;
	}
	else if (DefaultShader::FOR_LIGHT == defaultShader)
	{
		return *m_defaultShaderForLight;
	}
	else
	{
		std::cout << "Wrong parameter";
		throw std::runtime_error("Wrong parameter!");
	}
}