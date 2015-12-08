#pragma once
#include <gl\glew.h>
#include <GLFW\glfw3.h>
class Texture
{
public:
	Texture();
	~Texture();

	void loadTexture(const char* filename);
	GLuint getTexture()
	{
		return textureID;
	};
private:
	GLuint textureID;
};