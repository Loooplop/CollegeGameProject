#pragma once
class InterpolatingFunction
{
	InterpolatingFunction()
	{

	};
	~InterpolatingFunction()
	{

	};
	float lerp(float v0, float v1, float t)
	{
		return (1 - t)*v0 + v1;
	}



};