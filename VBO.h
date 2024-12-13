#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "GLErrorHandle.h"

struct Vertex {
	glm::vec3 position;
	glm::vec2 texCoords;
	glm::vec3 normal;
};

class VBO
{
	public:
		// Reference ID of the Vertex Buffer Object
		GLuint ID;
		// Constructor that generates a Vertex Buffer Object and links it to vertices
		VBO(GLfloat* vertices, GLsizeiptr size);
		VBO(std::vector<glm::vec3> vertices, GLsizeiptr size);
		VBO(std::vector<glm::vec2> vertices, GLsizeiptr size);

		void Bind();
		void Unbind();
		void Delete();
};

#endif // !VBO_CLASS_H