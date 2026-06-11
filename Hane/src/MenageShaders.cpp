#include "MenageShaders.h"

GLuint* MenageShaders::m_defaultShaderForObjectsID = 0;
GLuint* MenageShaders::m_defaultShaderForLightID = 0;

// This static function serve as seter at program start up to set default shaders for various type of objects
void MenageShaders::setDefaultShadersForAllID(GLuint& _defaultShaderForObjectsID, GLuint& _defaultShaderForLightsID)
{
	m_defaultShaderForObjectsID = &_defaultShaderForObjectsID;
	m_defaultShaderForLightID = &_defaultShaderForLightsID;
};

GLuint& MenageShaders::getDefaultShaderID(DefaultShader _defaultShader)
{
	if (DefaultShader::FOR_OBJECTS == _defaultShader)
	{
		return *m_defaultShaderForObjectsID;
	}
	else if (DefaultShader::FOR_LIGHT == _defaultShader)
	{
		return *m_defaultShaderForLightID;
	}
#ifdef _DEBUG
	throw std::runtime_error("Wrong parameter passed in static function getDefaultShaderID(DefaultShader defaultShader)");
#else
	std::cout << "Wrong parameter passed in static function getDefaultShaderID(DefaultShader defaultShader)" << "\n";
#endif // _DEBUG
}