#pragma once
#include <gl\glew.h>
#include <GLFW\glfw3.h>
class Texture
{
public:
	Texture();
	Texture(const char*filename, GLenum textureType)
	{
		glGenTextures(1, &this->textureID);
		loadTexture(filename, textureType);
	}
	Texture(GLuint textureID, GLenum textureType)
	{
		this->textureID = textureID;
		this->textureType = textureType;
	}
	~Texture();
	void loadTexture(const char* filename, GLenum textureType);
	void bindTexture()
	{
		glBindTexture(textureType, textureID);
	}
	void unbindTexture()
	{
		glBindTexture(textureType, 0);
	}
	GLuint getTextureId()
	{
		return textureID;
	}
	GLenum getTextureType()
	{
		return textureType;
	}
private:
	GLuint textureID;
	GLenum textureType;
};