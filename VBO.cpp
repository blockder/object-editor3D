#include"VBO.h"

VBO::VBO(std::vector<Vertex>& vertexArray)
{
	glGenBuffers(1, &id);
	bind();
	glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(Vertex), vertexArray.data(), GL_STATIC_DRAW);
	unBind();
}


void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

// Unbinds the VBO
void VBO::unBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void VBO::Delete()
{
	glDeleteBuffers(1, &id);
}