#include "ImageRenderer.h"
#include "DisplayManager.h"

ImageRenderer::ImageRenderer()
{
	model = ResourceLoader::getModel("ImgScreen.obj");
	prog = new Program("ImageRenderer.vs", "ImageRenderer.fs");
};

ImageRenderer::ImageRenderer(std::string vertexShader, std::string fragmentShader)
{
	model = ResourceLoader::getModel("ImgScreen.obj");
	prog = new Program(vertexShader, fragmentShader);
};

ImageRenderer::~ImageRenderer()
{
	delete prog;
}

void ImageRenderer::render(Texture * texture)
{
	glDisable(GL_DEPTH_TEST);
	prog->start();
	prog->uploadUniform_vec2("imageCenterPoint", vec2f(0, 0));
	prog->uploadUniform_vec2("imageScale", vec2f(1,1));
	model->prepareModel();
	texture->bindTexture();
	model->renderModel();
	texture->unbindTexture();
	model->unprepareModel();
	prog->stop();
	glEnable(GL_DEPTH_TEST);
}
void ImageRenderer::render(Texture * texture,vec2f position,vec2f size)
{
	glDisable(GL_DEPTH_TEST);
	prog->start();
	prog->uploadUniform_vec2("imageCenterPoint", ((position / DisplayManager::getScreenSize())-vec2f(0.5,0.5))*vec2f(2.0f,2.0f));
	prog->uploadUniform_vec2("imageScale", size / DisplayManager::getScreenSize());
	model->prepareModel();
	texture->bindTexture();
	model->renderModel();
	texture->unbindTexture();
	model->unprepareModel();
	prog->stop();
	glEnable(GL_DEPTH_TEST);
}
