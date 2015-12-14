#include "ModelRenderer.h"



ModelRenderer::ModelRenderer()
{
	this->rendererProgram = new Program();
	this->rendererProgram->AddShader("vertex.vs", GL_VERTEX_SHADER);
	this->rendererProgram->AddShader("fragment.fs", GL_FRAGMENT_SHADER);
	this->rendererProgram->CompileProgram();

	std::cout << "ModelRenderer Program ID: " << rendererProgram->getProgramID() << std::endl;
}


ModelRenderer::~ModelRenderer()
{
	delete rendererProgram;
}

void ModelRenderer::prepare()
{
	rendererProgram->start();
}

void ModelRenderer::process(void * renderableObject)
{
	models.push_back((Model*)renderableObject);
}

void ModelRenderer::render()
{
	for (int i = 0; i < models.size(); i++)
	{
		models[i]->Render();
	}
	models.clear();
}

void ModelRenderer::unprepare()
{
	rendererProgram->stop();
}
