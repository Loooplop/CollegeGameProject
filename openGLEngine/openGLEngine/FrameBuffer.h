#pragma once
#include <vector>
#include <iostream>
#include "Texture.h"
class FrameBuffer
{
public:
	FrameBuffer(float framebufferWidth, float framebufferHeight);
	~FrameBuffer();

	void bindFrameBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
		std::cout << frameBufferID << std::endl;
	};
	void unbindFrameBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	};
	void bindDepthTexture()
	{
		glBindTexture(depthAttachment->getTextureId(), depthAttachment->getTextureType());
	};
	void unbindDepthTexture()
	{
		glBindTexture(0, depthAttachment->getTextureType());
	};
	void bindColorTexture(int index)
	{
		glBindTexture(colorAttachment->getTextureId(), colorAttachment->getTextureType());
	};
	void unbindColorTexture()
	{
		glBindTexture(0, colorAttachment->getTextureType());
	};
	Texture *getColorTexture()
	{
		return colorAttachment;
	};
	Texture *getDepthTexture()
	{
		return depthAttachment;
	};
private:
	FrameBuffer();
	GLuint frameBufferID;
	Texture *depthAttachment;
	Texture *colorAttachment;
};