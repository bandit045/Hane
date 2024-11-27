#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>
#include <vector>

class EBO
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO(GLuint* indices, GLsizeiptr size);
	EBO(std::vector<int> indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};
#endif // !EBO_CLASS_H