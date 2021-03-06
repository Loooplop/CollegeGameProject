#pragma once
#include "Renderer.h"
#include "entity.h"
#include "Camera.h"
#include "Light.h"
#include "FrameBuffer.h"
#include <map>
class EntityRenderer :
	public Renderer
{
public:
	EntityRenderer();
	~EntityRenderer();
	void prepare();
	void process(void *renderableObject);
	void render()
	{

	};
	void render(Camera &camera,Light light);
	void renderScene(Camera &camera, Light light);
	void renderSceneToFrameBuffer(Camera &camera, Light light, FrameBuffer &frameBuffer, bool needClear=true);
	void renderToFrameBuffer(Camera &camera, Light light, FrameBuffer &frameBuffer, bool needClear = true);
	void unprepare();
	float getAmountOfObjectsProccessed()
	{
		return amountOfObjectsProcessed;
	}
private:
	std::map<std::string, std::vector<Entity*>> entityMap;
	float amountOfObjectsProcessed;
};

