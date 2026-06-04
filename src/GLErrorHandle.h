#ifndef GL_ERROR_HANDLE
#define GL_ERROR_HANDLE

#include <glad/glad.h>
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak();
// This GLCall macro will clear the error buffer and then call the function, and then check if there is an error
#define GLCall(x) GLErrorHandle::GLClearError(); x; ASSERT(GLErrorHandle::GLLogCall(#x, __FILE__, __LINE__)) 

class GLErrorHandle
{
public:
	static void GLClearError();
	static bool GLLogCall(const char* function, const char* file, int line);
	static const char* decodeErrorCode(GLenum error);
};

#endif // !GL_ERROR_HANDLE