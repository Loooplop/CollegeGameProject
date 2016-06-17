#pragma once
#include "Program.h"
#include "Model.h"
#include "Texture.h"
#include "ResourceLoader.h"
class ImageRenderer
{
public:
	ImageRenderer();
	ImageRenderer(std::string vertexShader, std::string fragmentShader);
	~ImageRenderer();
	void render(Texture* texture);
	void render(Texture * texture, vec2f position, vec2f size);
private:
	Model *model;
	Program *prog;
};

