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
	direction = vec3f(0, 0, 1);
	updateNeeded = true;
}
void Camera::MoveRight(float speed)
{
	origin = origin + (direction*speed).CrossProduct(vec3f(0,1,0));
	updateNeeded = true;
};
void Camera::MoveLeft(float speed)
{
	origin = origin + (direction*-speed).CrossProduct(vec3f(0, 1, 0));
	updateNeeded = true;
};
Camera::~Camera()
{

}
void Camera::RotateRight(float rotSpeed)
{
	rotAngleZ -= rotSpeed;
	direction = vec3f(cos(Radians(rotAngleZ)), 0, -sin(Radians(rotAngleZ)));
	updateNeeded = true;
};
void Camera::RotateLeft(float rotSpeed)
{
	rotAngleZ += rotSpeed;
	direction = vec3f(cos(Radians(rotAngleZ)), 0, -sin(Radians(rotAngleZ)));
	updateNeeded = true;
};
void Camera::MoveForward(float speed)
{
	origin = origin + direction*speed;
	updateNeeded = true;
};
void Camera::MoveBackward(float speed)
{
	
	origin = origin + direction*-speed;
	updateNeeded = true;
};
mat4f Camera::getViewMatrix()
{
	if (updateNeeded)
	{
		direction= vec3f(cos(Radians(rotAngleZ)), 0.0f, sin(Radians(-rotAngleZ)));
		viewMatrix = ::getViewMatrix<float>(origin, origin + direction, vec3f(0, 1, 0));
		updateNeeded = false;
	}
	return viewMatrix;
};