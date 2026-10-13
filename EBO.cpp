#include"EBO.h"
#include<iostream>

EBO::EBO(GLuint* indices, int size)
{
	EBO::size = size/4;
	glGenBuffers(1, &id);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, EBO::size * sizeof(GLuint), indices, GL_STATIC_DRAW);
	unBind();
}



// Binds the EBO
void EBO::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

// Unbinds the EBO
void EBO::unBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the EBO
void EBO::Delete()
{
	glDeleteBuffers(1, &id);
}

