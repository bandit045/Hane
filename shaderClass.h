#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include <glm/glm.hpp>

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
		// Deletes the Shader Program
		void Delete();
		// Update vec3 matrix to shader
		void sendVec3ToShader(const char* varName, glm::vec3 vec3);
		void sendVec3ToShader(const char* varName, float x, float y, float z);
	private:
		void compileErrors(unsigned int shader, const char* type);
};
#endif // !SHADER_CLASS_H