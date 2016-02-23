#include "TexturedModel.h"
#include "ResourceLoader.h"
TexturedModel::TexturedModel()
{

}

TexturedModel::TexturedModel(std::string modelFilename, bool hasNormals, std::string textureFilename)
{
	model = new Model(modelFilename, hasNormals == true ? Position_Texture_Normal : Position_Texture, false);
	texture = new Texture(textureFilename.c_str(),GL_TEXTURE_2D);
}

TexturedModel::TexturedModel(Model * model, Texture * modelTexture)
{
	this->model = model;
	this->texture = modelTexture;
}


TexturedModel::~TexturedModel()
{
	
}

void TexturedModel::prepare()
{
	model->prepareModel();
	texture->bindTexture();
}

void TexturedModel::render()
{
	model->renderModel();
}

void TexturedModel::unprepare()
{
	model->unprepareModel();
	texture->unbindTexture();
}
Model* TexturedModel::getModel()
{
	return model;
}
Texture* TexturedModel::getTexture()
{
	return texture;
}
