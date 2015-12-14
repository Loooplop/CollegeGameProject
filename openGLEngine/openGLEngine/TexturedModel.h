#pragma once
#include "Model.h"
#include "Texture.h"
class TexturedModel
{
public:
	TexturedModel();
	TexturedModel(std::string modelFilename, bool hasNormals, std::string textureFilename);
	TexturedModel(Model *model, Texture *modelTexture);
	~TexturedModel();

	void prepare();
	void render();
	void unprepare();
	Model* getModel();
	Texture* getTexture();
private:
	Model *model;
	Texture *texture;
};

