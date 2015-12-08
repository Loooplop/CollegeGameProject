#pragma once
#include "Entity.h"
class Renderer
{
public:
	Renderer();
	~Renderer();

	virtual void prepare() = 0;
	virtual void Render(void *entity) = 0;
	virtual void unprepare() = 0;
	virtual void Init() = 0;
	virtual void DestroyResource() = 0;
protected:
	GLuint programID;
};

