#pragma once
#include<glad/glad.h>
#include<vector>
#include"Vertex.h"

class VBO
{
public:
	GLuint id;

	VBO(std::vector<Vertex>& vertexArray);

	VBO() = default;
	

	void bind();

	void unBind();

	void Delete();
};
