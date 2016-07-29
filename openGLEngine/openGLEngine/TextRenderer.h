#pragma once
#include "Program.h"
#include "Model.h"
#include "Texture.h"
#include "ResourceLoader.h"
#include "Text.h"
#include "DisplayManager.h"
class TextRenderer
{
public:
	TextRenderer();
	~TextRenderer();
	void render(Text *text);
private:
	Model *model;
	Program *prog;
	Font* currentFont;
};

