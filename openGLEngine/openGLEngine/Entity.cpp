#include "Entity.h"
#include "WE_TransMatrix.h"
Entity::Entity(std::string modelFilename, std::string textureFilename)
{
	model = new TexturedModel(modelFilename, true, textureFilename);
	position = rotation =vec3f();
	scaleAmount = vec3f(1, 1, 1);
	modelMatrix = getScaleMatrix<float>(1, 1, 1);
	updateNeeded = true;
}

Entity::Entity(std::string modelFilename, std::string textureFilename, vec3f initialPosition, vec3f initialRotation, vec3f initialScale)
{
	model = new TexturedModel(modelFilename, true, textureFilename);
	position = initialPosition;
	rotation = initialRotation;
	scaleAmount = initialScale;
	modelMatrix = getScaleMatrix<float>(1, 1, 1);
    updateNeeded = true;
}

Entity::Entity(Model * model, Texture * tex)
{
	this->model = new TexturedModel(model, tex);
	position = rotation = vec3f();
	scaleAmount = vec3f(1, 1, 1);
	modelMatrix = getScaleMatrix<float>(1, 1, 1);
	updateNeeded = true;
}

Entity::Entity(Model * model, Texture * tex, vec3f initialPosition, vec3f initialRotation, vec3f initialScale)
{
	this->model = new TexturedModel(model, tex);
	position = initialPosition;
	rotation = initialRotation;
	scaleAmount = initialScale;
	modelMatrix = getScaleMatrix<float>(1, 1, 1);
	updateNeeded = true;
}

Entity::~Entity()
{
	std::cout << "destroying Entity" << std::endl;
	if(model)
	delete model;
}

mat4f Entity::getModelMatrix()
{
	if (updateNeeded)
	{
		std::cout << "updated" << std::endl;
		modelMatrix= getRotationYMatrix<float>(rotation.getY(), false)*getTranslationMatrix<float>(position.getX(), position.getY(), position.getZ())*getScaleMatrix<float>(scaleAmount.getX(), scaleAmount.getY(), scaleAmount.getZ());
		updateNeeded = false;
	}
	return modelMatrix;
}

void Entity::prepareEntity()
{
	model->prepare();
}

void Entity::render()
{
	model->render();
}

void Entity::unprepareEntity()
{
	model->unprepare();
}

Model * Entity::getModel()
{
	return model->getModel();
}

Texture * Entity::getTexture()
{
	return model->getTexture();
}

TexturedModel * Entity::getTexturedModel()
{
	return model;
}

void Entity::move(vec3f dx)
{
	position = position + dx;
	updateNeeded = true;
}

void Entity::rotate(vec3f dx)
{
	rotation = rotation + dx;
	updateNeeded = true;
}

void Entity::scale(vec3f dx)
{
	scaleAmount = scaleAmount * dx;
	updateNeeded = true;
}
