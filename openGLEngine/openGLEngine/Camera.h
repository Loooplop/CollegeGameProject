#pragma once
#include "WE_Vector.h"
#include "WE_Matrix.h"
#include "WE_TransMatrix.h"
class Camera
{
public:
	Camera();
	Camera(vec3f origin);
	~Camera();

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

