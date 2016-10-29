#pragma once
#include "WE_Matrix.h"
#include <math.h>
#include <cmath>
template<typename type>
mat4<type> getTranslationMatrix(double x, double y, double z)
{
	return mat4<type>(1, 0, 0, 0,
		              0, 1, 0, 0,
					  0, 0, 1, 0,
		              (type)x, (type)y, (type)z, 1);
}

template<typename type>
mat4<type> getScaleMatrix(double x, double y, double z)
{
	return mat4<type>((type)x, 0, 0, 0,
		              0,(type)y, 0, 0,
					  0, 0,(type)z, 0,
		              0, 0, 0, 1);
}
template<typename type>
mat4<type> getRotationXMatrix(double angle, bool isRadians = true)
{
	double conversion = 3.14159265359/180.0;
	if (isRadians)
	{
		return mat4<type>(1, 0, 0, 0,
			0, cos(angle), -sin(angle), 0,
			0, sin(angle), cos(angle), 0,
			0, 0, 0, 1);
	}
	return mat4<type>(1, 0, 0, 0,
		0, cos(angle*conversion), -sin(angle*conversion), 0,
		0, sin(angle*conversion), cos(angle*conversion), 0,
		0, 0, 0, 1);
}
template<typename type>
mat4<type> getRotationYMatrix(double angle, bool isRadians = true)
{
	double conversion = 3.14159265359 / 180.0;
	if (isRadians)
	{
		return mat4<type>(cos(angle), 0, sin(angle), 0,
			              0, 1, 0, 0,
			              -sin(angle), 0, cos(angle), 0,
			              0, 0, 0, 1);
	}
	return mat4<type>(cos(angle*conversion), 0, sin(angle*conversion), 0,
			              0, 1, 0, 0,
						  -sin(angle*conversion), 0, cos(angle*conversion), 0,
			              0, 0, 0, 1);
}
template<typename type>
mat4<type> getRotationZMatrix(double angle, bool isRadians = true)
{
	double conversion = 3.14159265359 / 180.0;
	if (isRadians)
	{
		return mat4<type>(cos(angle), -sin(angle), 0, 0,
			              sin(angle), cos(angle), 0, 0,
			              0, 0, 1, 0,
			              0, 0, 0, 1);
	}
	return mat4<type>(cos(angle*conversion), -sin(angle*conversion), 0, 0,
		sin(angle*conversion), cos(angle*conversion), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}
template<typename type>
mat4<type> getViewMatrix(vec3<type> eye, vec3<type> target, vec3<type> up)
{
	vec3<type> zaxis = eye - target;
	zaxis /= zaxis.getLength();
	vec3<type> xaxis = up.CrossProduct(zaxis);
	xaxis /= xaxis.getLength();
	vec3<type> yaxis = zaxis.CrossProduct(xaxis);

	return mat4<type>(xaxis.getX(), yaxis.getX(), zaxis.getX(), 0,
		              xaxis.getY(), yaxis.getY(), zaxis.getY(), 0,
		              xaxis.getZ(), yaxis.getZ(), zaxis.getZ(), 0,
		-xaxis.DotProduct(eye), -yaxis.DotProduct(eye), -zaxis.DotProduct(eye), 1
		);
}

template<typename type>
mat4<type> getPerspectiveMatrix(double FOV, double aspectRatio, double znear, double zfar)
{
	double coty = 1.0 / tan(FOV * (3.14159265359 / 180.0));
	return mat4<type>(coty / aspectRatio, 0, 0, 0,
					  0, coty, 0, 0,
			          0, 0, (znear + zfar) / (znear - zfar), -1,
			          0, 0, (2 * znear * zfar) / (znear - zfar), 0);
	/*double top = znear*tan((3.14f / 180)*(FOV / 2.0f));
	double bottom = -top;
	double right = top*aspectRatio;
	double left = -right;
	return mat4<type>((2 * znear) / right - left, 0, ((right + left) / (right - left)), 0,
		0, (2 * znear) / (top - bottom), (top + bottom) / (top - bottom), 0,
		0, 0, -((zfar + znear) / (zfar - znear)), -((2 * zfar*znear) / (zfar - znear)),
		0, 0, -1, 0);*/
}

template<typename type>
mat4<type> getOrthographicMatrix(double top, double bottom, double left, double right, double near, double far)
{
	return mat4<type>(2 / (right - left), 0, 0, -((right + left) / (right - left)),
					  0, 2 / (top - bottom), 0, -((top + bottom) / (top - bottom)),
					  0, 0, -2 / (far - near), -((far + near) / (far - near)),
					  0, 0, 0, 1);
}