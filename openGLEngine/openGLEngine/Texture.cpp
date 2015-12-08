#include "Texture.h"
#include "BMPLoader.h"

Texture::Texture()
{
	glGenTextures(1, &this->textureID);
}


Texture::~Texture()
{
	glDeleteTextures(1, &this->textureID);
}

void Texture::loadTexture(const char* filename)
{
	Image *image = loadBMP(filename);
	glBindTexture(GL_TEXTURE_2D,this->textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	delete(image);
};