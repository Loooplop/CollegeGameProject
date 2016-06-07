#pragma once
#include "WE_Vector.h"
class AnimationFrame
{
public:
	AnimationFrame();
	AnimationFrame(vec3f frameTranslation, vec3f frameRotation)
	{
		this->frameRotation = frameRotation;
		this->frameTranslation = frameTranslation;
	};
	~AnimationFrame();
	
	void print()
	{
		std::cout << frameTranslation << "," << frameRotation << std::endl;
	}
private:
	vec3f frameTranslation;
	vec3f frameRotation;
};

