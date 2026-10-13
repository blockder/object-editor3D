#pragma once
#include<glad/glad.h>

class EBO
{
public:
	GLuint id;
	int size;

	EBO(GLuint* indices, int size);
	EBO() = default;


	void bind();

	void unBind();

	void Delete();

	
};