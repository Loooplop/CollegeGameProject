#pragma once
#include "Renderer.h"
#include "Model.h"
class ModelRenderer :
	public Renderer
{
public:
	ModelRenderer();
	~ModelRenderer();

	void prepare();
	void process(void *renderableObject);
	void render();
	void unprepare();

private:
	std::vector<Model*> models;
};

