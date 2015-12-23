#include "EntityRenderer.h"
#include "DisplayManager.h"


EntityRenderer::EntityRenderer()
{
	entities = std::vector<Entity*>();
	rendererProgram = new Program("entityVertex.vs", "entityFragment.fs");
	rendererProgram->start();
	rendererProgram->uploadUniform_mat4("mat4_perspectiveMatrix", DisplayManager::getPerspectiveMatrix(), false);
	rendererProgram->uploadUniform_mat4("mat4_viewMatrix", getViewMatrix<float>(vec3f(0, 0, 2), vec3f(0, 0, 0), vec3f(0, 1, 0)), false);
	rendererProgram->uploadUniform_mat4("mat4_modelMatrix", getTranslationMatrix<float>(0,0,0), false);
	rendererProgram->stop();
}


EntityRenderer::~EntityRenderer()
{
	delete rendererProgram;
}

void EntityRenderer::prepare()
{
	rendererProgram->start();
}

void EntityRenderer::process(void * renderableObject)
{
	entities.push_back((Entity*)renderableObject);
}

void EntityRenderer::render(Camera &camera,Light light)
{
	rendererProgram->uploadUniform_mat4("mat4_perspectiveMatrix", DisplayManager::getPerspectiveMatrix(), false);

	rendererProgram->uploadUniform_mat4("mat4_viewMatrix", camera.getViewMatrix(), false);
	rendererProgram->uploadUniform_vec3("vec3_cameraOrigin", camera.getOriginPosition());

	rendererProgram->uploadUniform_vec3("light_position", light.getLightPosition());
	rendererProgram->uploadUniform_vec3("light_color", light.getLightColor());
	rendererProgram->uploadUniform_vec3("light_attenuation", light.getLightAttenuation());
	
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->prepareEntity();
		
		rendererProgram->uploadUniform_mat4("mat4_modelMatrix", entities[i]->getModelMatrix(), false);
		entities[i]->render();
		
		entities[i]->unprepareEntity();
	}
	



	entities.clear();
}

void EntityRenderer::unprepare()
{
	rendererProgram->stop();
}
