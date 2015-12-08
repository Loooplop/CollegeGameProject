#include "WE_FP_Camera.h"
#define Radians(x) (float)x*(3.141592653589793238462643383279f/180.0f)
WE_FP_Camera::WE_FP_Camera()
{
	origin = vec3f(0, 0, 0);
	rotAngleZ = 90.0f;
	viewMatrix = mat4f(1,0,0,0,
		               0,1,0,0,
					   0,0,1,0,
					   0,0,0,1);
	updateNeeded = true;
}
WE_FP_Camera::WE_FP_Camera(vec3f origin)
{
	this->origin = origin;
	rotAngleZ = 90.0f;
}
void WE_FP_Camera::MoveRight(float speed)
{
	vec3f dir = vec3f(0, 1, 0).CrossProduct(vec3f(cos(Radians(rotAngleZ))*speed, 0, -(Radians(rotAngleZ)))*speed);
	origin = origin - dir;
	updateNeeded = true;
};
void WE_FP_Camera::MoveLeft(float speed)
{
	vec3f dir = vec3f(0, 1, 0).CrossProduct(vec3f(cos(Radians(rotAngleZ))*speed, 0, -sin(Radians(rotAngleZ)))*speed);
	origin = origin + dir;
	updateNeeded = true;
};
WE_FP_Camera::~WE_FP_Camera()
{

}
void WE_FP_Camera::RotateRight(float rotSpeed)
{
	rotAngleZ -= rotSpeed;
	updateNeeded = true;
};
void WE_FP_Camera::RotateLeft(float rotSpeed)
{
	rotAngleZ += rotSpeed;
	updateNeeded = true;
};
void WE_FP_Camera::MoveForward(float speed)
{
	origin = origin + vec3f(cos(Radians(rotAngleZ))*speed, 0, -sin(Radians(rotAngleZ))*speed);
	updateNeeded = true;
};
void WE_FP_Camera::MoveBackward(float speed)
{
	MoveForward(-speed);
	updateNeeded = true;
};
mat4f WE_FP_Camera::getViewMatrix()
{
	if (updateNeeded)
	{
		viewMatrix = ::getViewMatrix<float>(origin, origin + vec3f(cos(Radians(rotAngleZ)), 0, -sin(Radians(rotAngleZ))), vec3f(0, 1, 0));
		updateNeeded = false;
	}
	return viewMatrix;
};