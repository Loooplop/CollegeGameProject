#pragma once
#include "WE_Vector.h"
#include "WE_Matrix.h"
#include "WE_TransMatrix.h"
class WE_FP_Camera
{
public:
	WE_FP_Camera();
	WE_FP_Camera(vec3f origin);
	~WE_FP_Camera();

	void RotateRight(float rotSpeed);
	void RotateLeft(float rotSpeed);

	void MoveRight(float speed);
	void MoveLeft(float speed);
	void MoveForward(float speed);
	void MoveBackward(float speed);

	mat4f getViewMatrix();

	vec3f getOriginPosition(){ return origin; };
private:
	mat4f viewMatrix;
	bool updateNeeded;
	vec3f origin;
	float rotAngleZ;
};

