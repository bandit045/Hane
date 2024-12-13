#pragma once

#include <glad/glad.h>
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLErrorHandle::GLClearError(); x; ASSERT(GLErrorHandle::GLLogCall(#x, __FILE__, __LINE__)) // This GLCall macro will clear the error buffer and then call the function, and then check if there is an error

class GLErrorHandle
{
public:
	static void GLClearError()
	{
        while (glGetError() != GL_NO_ERROR);
	}

	static bool GLLogCall(const char* function, const char* file, int line)
	{
		while (GLenum error = glGetError())
		{
			std::cout << "GL ERROR: " << decodeErrorCode(error) << "(" << error << ")" << " Line: " << line << " File: " << file << "\n";
			return false;
		}
		return true;
	}

	static const char* decodeErrorCode(GLenum error)
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
};