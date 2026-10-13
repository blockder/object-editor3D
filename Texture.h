#pragma once
#include<glad/glad.h>
#include<stb/stb_image.h>
#include"Shader.h"
class Texture
{
public:
	GLuint id;
	GLuint slot;
	unsigned char* bytes;
	const char* location;

	Texture(const char* location, GLuint slot);
	Texture(int width, int height);
	Texture(int width, int height, bool depth);
	Texture(const Texture& other);
	Texture() = default;
	void sendToShader(Shader& shaderProgram);
	void bind();
	void unBind();
	void Delete();

	bool operator== (Texture other);
private:
	int width;
	int height;
	int numColch;
};