#include "GLErrorHandle.h"

void GLErrorHandle::GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLErrorHandle::GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "GL_ERROR: " << decodeErrorCode(error) << "(" << error << ")" << " Line: " << line << " File: " << file << "\n";
		return false;
	}
	return true;
}

const char* GLErrorHandle::decodeErrorCode(GLenum error)
{
	switch (error)
	{
	case 1280: return "GL_INVALID_ENUM";
		break;
	case 1281: return "GL_INVALID_VALUE";
		break;
	case 1282: return "GL_INVALID_OPERATION";
		break;
	case 1283: return "GL_STACK_OVERFLOW";
		break;
	case 1284: return "GL_STACK_UNDERFLOW";
		break;
	case 1285: return "GL_OUT_OF_MEMORY";
		break;
	case 1286: return "GL_INVALID_FRAMEBUFFER_OPERATION";
		break;
	}
	return "Unknown Error, add error to switch inside GLErrorHandle.h";
	// How to add new enum uncoment this down and find it
	// GL_INVALID_VALUE
}