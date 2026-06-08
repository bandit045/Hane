#include "VAO.h"

// Constructor that generates a VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Links a VBO to the VAO using a certain layout
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	GLCall(glVertexAttribPointer(layout, numComponents, type, GL_FALSE, static_cast<GLsizei>(stride), offset));
	GLCall(glEnableVertexAttribArray(layout));
	VBO.Unbind();
}

void VAO::Bind()
{
	GLCall(glBindVertexArray(ID));
}

void VAO::Unbind()
{
	GLCall(glBindVertexArray(0));
}

void VAO::Delete()
{
	GLCall(glDeleteVertexArrays(1, &ID));
}