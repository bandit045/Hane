#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Transform.h"
#include "GLErrorHandle.h"

std::string get_file_contents(const char* filename);

class Shader
{
	public:
		// Reference ID of the Shader Program
		GLuint ID;
		// Constructor that build the Shader Program from 2 different shaders
		Shader(const char* vertexFile, const char* fragmentFile);

		// Activates the Shader Program
		void Activate();
		// Deactivate the Shader Program
		void Deactivate();
		// Deletes the Shader Program
		void Delete();
		// Update uniforms to shader
		void sendBool(const std::string& varName,const bool& boolValue);
		void sendVec3f(const std::string& varName, const glm::vec3& vec3);
		void sendVec3f(const std::string& varName, const float& x, const float& y, const float& z);
		void sendVec2f(const std::string& varName, const glm::vec2& vec2);
		void sendVec2f(const std::string& varName, const float& x, const float& y);
		void sendFloat(const std::string& varName, const float& x);
		void sendMatrix4x4f(const std::string& varName, const glm::mat4& matrix);
		void sendMatrix3x3f(const std::string& varName, const glm::mat3& matrix);
	private:
		void constructShaderProgram(const char* vertexFile, const char* fragmentFile);
		void compileErrors(unsigned int shader, const char* type);
};
#endif // !SHADER_CLASS_H