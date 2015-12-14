#pragma once
#include "Program.h"
class Renderer
{
public:
	Renderer();
	~Renderer();

	virtual void prepare() = 0;
	virtual void process(void *renderableObject)=0;
	virtual void render() = 0;
	virtual void unprepare() = 0;
protected:
	Program *rendererProgram;
};

