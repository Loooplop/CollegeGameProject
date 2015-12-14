#include "Camera.h"
#define Radians(x) (float)x*(3.141592653589793238462643383279f/180.0f)
Camera::Camera()
{
	origin = vec3f(0, 0, 0);
	rotAngleZ = 90.0f;
	viewMatrix = mat4f(1,0,0,0,
		               0,1,0,0,
					   0,0,1,0,
					   0,0,0,1);
	updateNeeded = true;
}
Camera::Camera(vec3f origin)
{
	this->origin = origin;
	rotAngleZ = 90.0f;
	viewMatrix = mat4f(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	updateNeeded = true;
}
void Camera::MoveRight(float speed)
{
	vec3f dir = vec3f(0, 1, 0).CrossProduct(vec3f(cos(Radians(rotAngleZ))*speed, 0, -(Radians(rotAngleZ)))*speed);
	origin = origin - dir;
	updateNeeded = true;
};
void Camera::MoveLeft(float speed)
{
	vec3f dir = vec3f(0, 1, 0).CrossProduct(vec3f(cos(Radians(rotAngleZ))*speed, 0, -sin(Radians(rotAngleZ)))*speed);
	origin = origin + dir;
	updateNeeded = true;
};
Camera::~Camera()
{

}
void Camera::RotateRight(float rotSpeed)
{
	rotAngleZ -= rotSpeed;
	updateNeeded = true;
};
void Camera::RotateLeft(float rotSpeed)
{
	rotAngleZ += rotSpeed;
	updateNeeded = true;
};
void Camera::MoveForward(float speed)
{
	origin = origin + vec3f(cos(Radians(rotAngleZ))*speed, 0, -sin(Radians(rotAngleZ))*speed);
	updateNeeded = true;
};
void Camera::MoveBackward(float speed)
{
	MoveForward(-speed);
	updateNeeded = true;
};
mat4f Camera::getViewMatrix()
{
	if (updateNeeded)
	{
		viewMatrix = ::getViewMatrix<float>(origin, origin + vec3f(sin(Radians(rotAngleZ)), 0, cos(Radians(rotAngleZ))), vec3f(0, 1, 0));
		updateNeeded = false;
	}
	return viewMatrix;
};