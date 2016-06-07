#pragma once
#include <vector>
#include "Texture.h"
class FrameBuffer
{
public:
	FrameBuffer();
	FrameBuffer(float framebufferWidth, float framebufferHeight);
	FrameBuffer(float framebufferWidth, float framebufferHeight, bool hasDepthTexture);
	FrameBuffer(float framebufferWidth, float framebufferHeight, int amountOfColorAttachment);
	FrameBuffer(float framebufferWidth, float framebufferHeight, bool hasDepthTexture,int amountOfColorAttachment);
	~FrameBuffer();

	void bindFrameBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	};
	void unbindFrameBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	};
	void bindDepthTexture()
	{
		glBindTexture(depthAttachemnt.getTextureId(), depthAttachemnt.getTextureType());
	};
	void unbindDepthTexture()
	{
		glBindTexture(0, depthAttachemnt.getTextureType());
	};
	void bindColorTexture()
	{
		glBindTexture(colorAttachment.getTextureId(), colorAttachment.getTextureType());
	};
	void unbindColorTexture()
	{
		glBindTexture(0, colorAttachment.getTextureType());
	};
private:
	GLuint frameBufferID;
	Texture depthAttachemnt;
	Texture colorAttachment;
};