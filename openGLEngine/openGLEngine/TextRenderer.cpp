#include "TextRenderer.h"



TextRenderer::TextRenderer()
{
	model = ResourceLoader::getModel("textModel.obj");
	prog = new Program("TextRenderer.vs", "TextRenderer.fs");
	prog->start();
	prog->uploadUniform_vec2("screenSize", DisplayManager::getScreenSize());
	prog->stop();
}


TextRenderer::~TextRenderer()
{
	delete prog;
}

void TextRenderer::render(Text *text)
{
	Font *f = text->getFont();
	glDisable(GL_DEPTH_TEST);
	prog->start();
	prog->uploadUniform_vec3("textColor", text->getTextColor());
	prog->uploadUniform_vec2("fontUVSize", f->getGlyphSize() / vec2f(f->getTextureSize(), f->getTextureSize()));
	prog->uploadUniform_vec2("glyphSize", f->getGlyphSize());
	model->prepareModel();
	f->getTexture()->bindTexture();
	std::vector<int>& codes = text->getTextGlyphCodes();
	for (int i = 0; i < codes.size(); i++)
	{
		if (codes[i]>0)
		{
			prog->uploadUniform_vec2("textBottomLeftLocation", vec2f(text->getTextLocation().getX() + f->getGlyphSize().getX()*i, text->getTextLocation().getY()));
			prog->uploadUniform_vec2("UVGlyphBottomLocation", f->getLocation(codes[i] + 32));
			model->renderModel();
		};
	}
	f->getTexture()->unbindTexture();
	model->unprepareModel();
	prog->stop();
	glEnable(GL_DEPTH_TEST);
}
