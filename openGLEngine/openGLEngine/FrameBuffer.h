#pragma once
#include <vector>
#include "Texture.h"
class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();
	void bindFrameBuffer();
	void unbindFrameBuffer();
	void bindFrameBufferTexture(int textureType);
	void unbindFrameBufferTexture();
private:
	GLuint frameBufferID;
	std::vector<Texture> framebufferColorAttachments;
	Texture depthTexture;
};