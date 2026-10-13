#include"FBO.h"

FBO::FBO()
{
	id = 0;
}
FBO::FBO(int screenWidth, int screenHeight)
{
	glGenFramebuffers(1, &id);
	bind();
	texture = Texture(screenWidth, screenHeight);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id, 0);
	
	GLuint rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenWidth, screenHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "ERROR: Framebuffer not complete!" << std::endl;
	unBind();
}

void FBO::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void FBO::unBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}