#pragma once
#include "Model.h"
#include "WE_Vector.h"
#include "WE_TransMatrix.h"
#include "WE_FP_Camera.h"
#include "Program.h"
#include "DisplayManager.h"
class Entity
{
public:
	Entity(Model *temp, vec3f InitialPosition, vec3f InitialRotation)
	{
		model = temp;
		rot = InitialRotation;
		pos - InitialPosition;
		updateNeeded = true;
		modelMatrix = mat4f(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		modelNormalMatrix = mat3f(1, 0, 0, 0, 1, 0, 0, 0, 1);
	};
	void Render(WE_FP_Camera &camera, Program &shader)
	{
		if (updateNeeded)
		{
			modelMatrix = getRotationYMatrix<float>(rot.getY())*getTranslationMatrix<float>(pos.getX(), pos.getY(), pos.getZ());
			mat3f newNormalMatrix(modelMatrix.getElement(0, 0), modelMatrix.getElement(1, 0), modelMatrix.getElement(2, 0),
				modelMatrix.getElement(0, 1), modelMatrix.getElement(1, 1), modelMatrix.getElement(2, 1),
				modelMatrix.getElement(0, 2), modelMatrix.getElement(1, 2), modelMatrix.getElement(2, 2));
			modelNormalMatrix = newNormalMatrix.getInverse();
			updateNeeded = false;
		}
		shader.uploadUniform_mat4("Model", modelMatrix,false);
		shader.uploadUniform_mat4("View", camera.getViewMatrix(), false);
		shader.uploadUniform_vec3("eyePosition", camera.getOriginPosition());
		shader.uploadUniform_mat4("Perp", DisplayManager::getPerspectiveMatrix(), false);
		shader.uploadUniform_mat3("Normal", modelNormalMatrix, true);
		model->Render();
	}
	void moveEntity(float x, float y, float z)
	{
		pos = pos + vec3f(x, y, z);
		updateNeeded = true;
	}
	void setEntityPosition(float x, float y, float z)
	{
		pos = vec3f(x, y, z);
		updateNeeded = true;
	}
	vec3f getEntityPosition() const
	{
		return pos;
	}
	void rotateEntity(float x, float y, float z)
	{ 
		rot = rot+vec3f(-x, -y, -z);
		updateNeeded = true;
	}
	void setEntityRotation(float x, float y, float z)
	{
		rot = vec3f(x, y, z);
		updateNeeded = true;
	}
	Entity();
	~Entity();
private:
	vec3f rot;
	vec3f pos;
	Model *model;
	mat4f modelMatrix;
	mat3f modelNormalMatrix;
	bool updateNeeded;
};

