#pragma once
#include "TexturedModel.h"
class Entity
{
public:
	Entity(std::string modelFilename, std::string textureFilename);
	Entity(std::string modelFilename, std::string textureFilename, vec3f initialPosition, vec3f initialRotation, vec3f initialScale);
	Entity(Model* model, Texture *tex);
	Entity(Model* model, Texture *tex, vec3f initialPosition, vec3f initialRotation, vec3f initialScale);
	~Entity();

	mat4f getModelMatrix();
	void prepareEntity();
	void render();
	void unprepareEntity();
	Model *getModel();
	Texture *getTexture();
	TexturedModel *getTexturedModel();
	void move(vec3f dx);
	void setPosition(vec3f position)
	{
		this->position = position;
		updateNeeded = true;
	}
	vec3f getPosition()
	{
		return position;
	}
	void rotate(vec3f dx);
	void scale(vec3f dx);
private:
	TexturedModel *model;
	vec3f position;
	vec3f rotation;
	vec3f scaleAmount;
	mat4f modelMatrix;
	bool updateNeeded;
};

