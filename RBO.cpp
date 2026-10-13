#include"RBO.h"


RBO::RBO(int screenWidth, int screenHeight)
{
	glGenFramebuffers(1, &id);
	bind();
	texture = Texture(screenWidth, screenHeight, true);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture.id, 0);


	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "ERROR: Framebuffer not complete!" << std::endl;
	unBind();
}

void RBO::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void RBO::unBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}