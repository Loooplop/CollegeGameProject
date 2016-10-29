#pragma once
#include "EntityRenderer.h"
#include "ImageRenderer.h"
#include "TextRenderer.h"
#include "DisplayManager.h"
#include "Renderer.h"
class MasterRenderer :
	public Renderer
{
public:
	MasterRenderer();
	~MasterRenderer();

	void prepare();
	void process(void *renderableObject);
	void process(Text *text);
	void render();
	void render(Camera &camera, Light &light);
	void unprepare();

	void cleanUp();
private:
	EntityRenderer *entRen;
	ImageRenderer *imgRen;
	TextRenderer *texRen;
	FrameBuffer *initialFramebuffer;
	std::vector<Text*> texts;
};

