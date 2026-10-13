#pragma once
#include<glm/glm.hpp>
#include<glad/glad.h>
#include"VBO.h"
#include"EBO.h"

class VAO
{
public:
	GLuint id;

	VAO();
	void setLayer(VBO& VBO,EBO& EBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

	void bind();

	void unBind();

	void Delete();
};
