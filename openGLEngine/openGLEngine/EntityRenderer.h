#pragma once
#include "Renderer.h"
#include "entity.h"
#include "Camera.h"
#include "Light.h"
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
	void unprepare();
private:
	std::vector<Entity*> entities;
};

