#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

std::string get_file_contents(const char* filename);

class Shader
{
	public:
		// Reference ID of the Shader Program
		GLuint ID;
		// Constructor that build the Shader Program from 2 different shaders
		Shader(const char* vertexFile, const char* fragmentFile);
		Shader();

		// Activates the Shader Program
		void Activate();
		// Deactivate the Shader Program
		void Deactivate();
		// Deletes the Shader Program
		void Delete();
		// Update vec3 matrix to shader
		void sendVec3fToShader(const char* varName, glm::vec3 vec3);
		void sendVec3fToShader(const char* varName, float x, float y, float z);
		void sendMat4x4ToShader(const char* varName, glm::mat4 matrix);
		void sendMatrix3x3fToShader(const char* varName, glm::mat3 matrix);
	private:
		void constructShader(const char* vertexFile, const char* fragmentFile);
		void compileErrors(unsigned int shader, const char* type);
};
#endif // !SHADER_CLASS_H