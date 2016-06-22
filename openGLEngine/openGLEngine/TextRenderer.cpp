#include "TextRenderer.h"



TextRenderer::TextRenderer()
{
	model = ResourceLoader::getModel("ImgScreen.obj");
	prog = new Program("TextRenderer.vs", "TextRenderer.fs");
	prog->start();
	prog->uploadUniform_vec2("screenSize", DisplayManager::getScreenSize());
	prog->stop();
}


TextRenderer::~TextRenderer()
{
	delete prog;
}

void TextRenderer::render(Text & text)
{
	Font *f = text.getFont();
	std::vector<int> codes = text.getTextGlyphCodes();
	
	glDisable(GL_DEPTH_TEST);
	prog->start();
	prog->uploadUniform_vec2("cellSize", f->getGlyphSize());
	prog->uploadFloat("atlasTextureSize", f->getTextureSize());
	model->prepareModel();
	f->getTexture()->bindTexture();
	for (int i = 0; i < codes.size(); i++)
	{
		prog->uploadUniform_vec2("textBottomLeftLocation", vec2f(text.getTextLocation().getX() + f->getGlyphSize().getX()*i, text.getTextLocation().getY()));
		prog->uploadFloat("glyphCode", codes[i]);
		model->renderModel();
	}

	f->getTexture()->unbindTexture();
	model->unprepareModel();
	prog->stop();
	glEnable(GL_DEPTH_TEST);
}
