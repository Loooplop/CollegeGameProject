#include "EntityRenderer.h"
#include "DisplayManager.h"


EntityRenderer::EntityRenderer()
{
	entityMap = std::map<std::string, std::vector<Entity*>>();
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
	rendererProgram->uploadUniform_mat4("mat4_perspectiveMatrix", DisplayManager::getPerspectiveMatrix(), false);
}

void EntityRenderer::process(void * renderableObject)
{
	Entity *e = (Entity*)renderableObject;
	std::string modelName=e->getModel()->getModelName();

	if (entityMap.find(modelName)==entityMap.end())
	{
		entityMap[modelName] = std::vector<Entity*>();
	}
	entityMap[modelName].push_back(e);
}

void EntityRenderer::render(Camera &camera,Light light)
{
	rendererProgram->uploadUniform_mat4("mat4_viewMatrix", camera.getViewMatrix(), false);
	rendererProgram->uploadUniform_vec3("vec3_cameraOrigin", camera.getOriginPosition());

	rendererProgram->uploadUniform_vec3("light_position", light.getLightPosition());
	rendererProgram->uploadUniform_vec3("light_color", light.getLightColor());
	rendererProgram->uploadUniform_vec3("light_attenuation", light.getLightAttenuation());
	for (auto it = entityMap.begin(); it != entityMap.end(); it++)
	{
		it->second[0]->getModel()->prepareModel();
		
		std::vector<Entity*> list = it->second;
		for (int i = 0; i < list.size(); i++)
		{
			rendererProgram->uploadUniform_mat4("mat4_modelMatrix",list[i]->getModelMatrix(),false);
			list[i]->getTexture()->bindTexture();
			list[i]->getModel()->renderModel();
			list[i]->getTexture()->unbindTexture();
		}
		
		it->second[0]->getModel()->unprepareModel();
	};
	entityMap.clear();
}

void EntityRenderer::renderScene(Camera & camera, Light light)
{
	rendererProgram->uploadUniform_mat4("mat4_viewMatrix", camera.getViewMatrix(), false);
	rendererProgram->uploadUniform_vec3("vec3_cameraOrigin", camera.getOriginPosition());

	rendererProgram->uploadUniform_vec3("light_position", light.getLightPosition());
	rendererProgram->uploadUniform_vec3("light_color", light.getLightColor());
	rendererProgram->uploadUniform_vec3("light_attenuation", light.getLightAttenuation());
	for (auto it = entityMap.begin(); it != entityMap.end(); it++)
	{
		it->second[0]->getModel()->prepareModel();
		it->second[0]->getTexture()->bindTexture();
		std::vector<Entity*> list = it->second;
		for (int i = 0; i < list.size(); i++)
		{
			rendererProgram->uploadUniform_mat4("mat4_modelMatrix", list[i]->getModelMatrix(), false);
			list[i]->getModel()->renderModel();
		}
		it->second[0]->getTexture()->unbindTexture();
		it->second[0]->getModel()->unprepareModel();
	};
}

void EntityRenderer::unprepare()
{
	rendererProgram->stop();
}
