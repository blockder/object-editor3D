#pragma once
#include<glad/glad.h>
#include"Texture.h"

class FBO
{
public:
	GLuint id;

	Texture texture;

	FBO(int screenWidth, int screenHeight);
	FBO();


	void bind();

	void unBind();

};
