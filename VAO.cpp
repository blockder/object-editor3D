#include"VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &id);
}


void VAO::setLayer(VBO& VBO, EBO& EBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	bind();
	VBO.bind();
	EBO.bind();

	glEnableVertexAttribArray(layout);
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);

	unBind();
	VBO.unBind();
	EBO.unBind();
}

// Binds the VAO
void VAO::bind()
{
	glBindVertexArray(id);
}

// Unbinds the VAO
void VAO::unBind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &id);
}
