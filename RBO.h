#pragma once
#include<glad/glad.h>
#include"Texture.h"

class RBO
{
public:
	GLuint id;

	Texture texture;

	RBO(int screenWidth, int screenHeight);
	RBO() = default;
	

	void bind();

	void unBind();

};
