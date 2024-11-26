#include "MenageShaders.h"

GLuint* MenageShaders::m_defaultShaderForObjectsID = 0;
GLuint* MenageShaders::m_defaultShaderForLightID = 0;

/*/Shader* MenageShaders::m_defaultShaderForObjectsProgram = new Shader();
Shader* MenageShaders::m_defaultShaderForLightProgram = new Shader();*/

MenageShaders::MenageShaders()
{

}

void MenageShaders::setDefaultShadersForAllID(GLuint& defaultShaderForObjectsID, GLuint& defaultShaderForLightsID)
{
	m_defaultShaderForObjectsID = &defaultShaderForObjectsID;
	m_defaultShaderForLightID = &defaultShaderForLightsID;
};

/*void MenageShaders::setDefaultShadersForAllProgram(Shader& defaultShaderForObjectsProgram, Shader& defaultShaderForLightsProgram)
{
	m_defaultShaderForObjectsProgram = &defaultShaderForObjectsProgram;
	m_defaultShaderForLightProgram = &defaultShaderForLightsProgram;
};*/

GLuint& MenageShaders::getDefaultShaderID(DefaultShader defaultShader)
{
	if (DefaultShader::FOR_OBJECTS == defaultShader)
	{
		return *m_defaultShaderForObjectsID;
	}
	else if (DefaultShader::FOR_LIGHT == defaultShader)
	{
		return *m_defaultShaderForLightID;
	}
	else
	{
		std::cout << "Wrong parameter";
		throw std::runtime_error("Wrong parameter!");
	}
}

/*Shader& MenageShaders::getDefaultShaderProgram(DefaultShader defaultShader)
{
	if (DefaultShader::FOR_OBJECTS == defaultShader)
	{
		return *m_defaultShaderForObjectsProgram;
	}
	else if (DefaultShader::FOR_LIGHT == defaultShader)
	{
		return *m_defaultShaderForLightProgram;
	}
	else
	{
		std::cout << "Wrong parameter";
		throw std::runtime_error("Wrong parameter!");
	}
}*/