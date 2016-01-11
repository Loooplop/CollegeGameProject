#include "Camera.h"
#define Radians(x) (float)x*(3.141592653589793238462643383279f/180.0f)
Camera::Camera()
{
	origin = vec3f(0, 0, 0);
	rotAngleZ = 90.0f;
	rotAngleY = 0.0f;
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
	rotAngleY = 0.0f;
	viewMatrix = mat4f(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	direction = vec3f(0, 0, 1);
	updateNeeded = true;
}
void Camera::MoveRight(float speed)
{
	origin = origin + (direction).CrossProduct(vec3f(0,1,0)).getNormal()*speed;
	updateNeeded = true;
};
void Camera::MoveLeft(float speed)
{
	origin = origin + (direction).CrossProduct(vec3f(0, 1, 0)).getNormal()*-speed;
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
}
void Camera::RotateUp(float speed)
{
	rotAngleY += speed;
	if (rotAngleY <= -360.0f)
	{
		rotAngleY = -360.0f;
	}
	else if (rotAngleY>=360.0f)
	{
		rotAngleY = 360.0f;
	}
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
		float r = 3 * cosf(Radians(rotAngleY));
		this->direction= vec3f(r*sinf(Radians(rotAngleZ)), 3*sinf(Radians(rotAngleY)), r*cosf(Radians(rotAngleZ)));
		viewMatrix = ::getViewMatrix<float>(origin, origin + direction, vec3f(0, 1, 0));
		updateNeeded = false;
	}
	return viewMatrix;
};