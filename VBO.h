#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

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