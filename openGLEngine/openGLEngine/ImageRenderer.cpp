#include "ImageRenderer.h"


ImageRenderer::ImageRenderer()
{
	model = ResourceLoader::getModel("ImgScreen.obj");
	prog = new Program("ImageRenderer.vs", "ImageRenderer.fs");
}


ImageRenderer::~ImageRenderer()
{
	delete prog;
}

void ImageRenderer::render(Texture * texture)
{
	glDisable(GL_DEPTH_TEST);
	prog->start();
	model->prepareModel();
	texture->bindTexture();
	model->renderModel();
	texture->unbindTexture();
	model->unprepareModel();
	prog->stop();
	glEnable(GL_DEPTH_TEST);
}
