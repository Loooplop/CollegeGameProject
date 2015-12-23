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
	void RotateUp(float speed);

	void MoveRight(float speed);
	void MoveLeft(float speed);
	void MoveForward(float speed);
	void MoveBackward(float speed);

	mat4f getViewMatrix();

	vec3f getOriginPosition(){ return origin; };
	vec3f getDirectionVector() { return direction; };
private:
	mat4f viewMatrix;
	bool updateNeeded;
	vec3f origin;
	vec3f direction;
	float rotAngleZ;
	float rotAngleY;
};

