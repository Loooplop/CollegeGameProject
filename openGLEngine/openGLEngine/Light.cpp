#include "Light.h"



Light::Light()
{
	lightPosition = vec3f();
	lightColor = vec3f(1, 1, 1);
	lightAttenuation = vec3f(1, 0, 0);
}

Light::Light(vec3f lightposition, vec3f lightcolor, vec3f lightattenuation)
{
	lightPosition = lightposition;
	lightColor = lightcolor;
	lightAttenuation = lightattenuation;
}


Light::~Light()
{
}

void Light::setLightPosition(vec3f lightposition)
{
	this->lightPosition = lightposition;
}

void Light::setLightColor(vec3f lightcolor)
{
	this->lightColor = lightcolor;
}

void Light::setLightAttenuation(vec3f attenuation)
{
	lightAttenuation = attenuation;
}

vec3f Light::getLightPosition()
{
	return lightPosition;
}

vec3f Light::getLightColor()
{
	return lightColor;
}

vec3f Light::getLightAttenuation()
{
	return lightAttenuation;
}
