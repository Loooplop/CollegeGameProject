#pragma once
#include "WE_Vector.h"
class Light
{
public:
	Light();
	Light(vec3f lightposition, vec3f lightcolor,vec3f lightattenuation);
	~Light();
	void setLightPosition(vec3f lightposition);
	void setLightColor(vec3f lightcolor);
	void setLightAttenuation(vec3f attenuation);
	vec3f getLightPosition();
	vec3f getLightColor();
	vec3f getLightAttenuation();
private:
	vec3f lightPosition;
	vec3f lightColor;
	vec3f lightAttenuation;
};

