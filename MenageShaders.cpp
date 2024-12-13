#include "MenageShaders.h"

GLuint* MenageShaders::m_defaultShaderForObjectsID = 0;
GLuint* MenageShaders::m_defaultShaderForLightID = 0;

// This static function serve as seter at program start up to set default shaders for various type of objects
void MenageShaders::setDefaultShadersForAllID(GLuint& _defaultShaderForObjectsID, GLuint& _defaultShaderForLightsID)
{
	m_defaultShaderForObjectsID = &_defaultShaderForObjectsID;
	m_defaultShaderForLightID = &_defaultShaderForLightsID;
};

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
#ifdef _DEBUG
		throw std::runtime_error("Wrong parameter passed in static function getDefaultShaderID(DefaultShader defaultShader)");
#else
		std::cout << "Wrong parameter passed in static function getDefaultShaderID(DefaultShader defaultShader)" << "\n";
#endif // _DEBUG
	}
}