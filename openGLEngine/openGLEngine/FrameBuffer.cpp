#include "FrameBuffer.h"


FrameBuffer::FrameBuffer()
{
	
}

FrameBuffer::FrameBuffer(float framebufferWidth, float framebufferHeight)
{
	glGenFramebuffers(1, &frameBufferID);
	bindFrameBuffer();

	GLuint depthID;
	glGenTextures(1, &depthID);
	glBindTexture(GL_TEXTURE_2D, depthID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, framebufferWidth, framebufferHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthID, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	depthAttachment = new Texture(depthID, GL_TEXTURE_2D);
	std::cout << "depthTextureID: " << depthAttachment->getTextureId() << std::endl;

	GLuint colorID;
	glGenTextures(1, &colorID);
	glBindTexture(GL_TEXTURE_2D, colorID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, framebufferWidth, framebufferHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorID, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	colorAttachment = new Texture(colorID, GL_TEXTURE_2D);

	std::cout << "colorTextureID: " << colorAttachment->getTextureId() << std::endl;
	
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Framebuffer of Size: " << framebufferWidth << ", " << framebufferHeight << std::endl;
	}
	unbindFrameBuffer();
};

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &frameBufferID);
	delete depthAttachment;
	delete colorAttachment;
}