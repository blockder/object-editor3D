#include"Texture.h"


Texture::Texture(int width, int height)
{
	this->slot = 3;
	glGenTextures(1, &id);
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Prevents edge bleeding

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	unBind();
}
Texture::Texture(int width, int height, bool depth)
{
	this->slot = 4;
	glGenTextures(1, &id);
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Prevents edge bleeding

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL); 
	unBind();
}
Texture::Texture(const char* location, GLuint slot)
{
	Texture::slot = slot;
	Texture::location = location;

	stbi_set_flip_vertically_on_load(true);
	Texture::bytes = stbi_load(location, &width, &height, &numColch, 0);

	glGenTextures(1, &id);

	glActiveTexture(GL_TEXTURE0 + slot);

	bind();
	//set parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	//put image into texture object
	if (numColch == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	}
	else if (numColch == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	}
	else if (numColch == 1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
	}
	else throw std::invalid_argument("automatic texture type recognition falied");

	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(bytes);
	unBind();
}
Texture::Texture(const Texture& other)
{
	Texture::slot = other.slot;
	Texture::location = other.location;

	stbi_set_flip_vertically_on_load(true);
	Texture::bytes = stbi_load(location, &width, &height, &numColch, 0);

	glGenTextures(1, &id);

	glActiveTexture(GL_TEXTURE0 + slot);

	bind();
	//set parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	//put image into texture object
	if (numColch == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	}
	else if (numColch == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	}
	else if (numColch == 1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
	}
	else throw std::invalid_argument("automatic texture type recognition falied");

	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(bytes);
	unBind();
}
void Texture::sendToShader(Shader& shaderProgram)
{
	shaderProgram.Active();
	glUniform1i(glGetUniformLocation(shaderProgram.id, "texUnit"), slot);
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::Delete()
{
	glDeleteVertexArrays(1, &id);
}

bool Texture::operator==(Texture other)
{
	return this->location == other.location;
}