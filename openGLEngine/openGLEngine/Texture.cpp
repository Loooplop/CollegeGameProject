#include "Texture.h"
#include "BMPLoader.h"
#include <string>
#include <iostream>
Texture::Texture()
{
	glGenTextures(1, &this->textureID);
	textureType = 0;
}


Texture::~Texture()
{
	glDeleteTextures(1, &this->textureID);
}

void Texture::loadTexture(const char* filename, GLenum textureType)
{
	this->textureType = textureType;
	glBindTexture(textureType, this->textureID);
	glActiveTexture(GL_TEXTURE0);
	Image *image = 0x00;
	switch (textureType)
	{
	case GL_TEXTURE_2D:
		image = loadBMP(filename);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
		delete(image);
		break;
	case GL_TEXTURE_CUBE_MAP:
		for (int i = 0; i < 6; i++)
		{
			image = loadBMP((std::string(filename)+std::to_string(i)).c_str());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
			delete(image);
		}
		
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		break;
	default:
		break;
	}
	glBindTexture(textureType, 0);
};