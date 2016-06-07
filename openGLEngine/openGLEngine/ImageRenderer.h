#pragma once
#include "Program.h"
#include "Model.h"
#include "Texture.h"
#include "ResourceLoader.h"
class ImageRenderer
{
public:
	ImageRenderer();
	~ImageRenderer();
	void render(Texture* texture);

private:
	Model *model;
	Program *prog;
};

