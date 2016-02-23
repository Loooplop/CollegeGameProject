#pragma once
#include <vector>
#include "WE_Vector.h"
#include "TexturedModel.h"
#define TerrainSize 200.0f
#define AmountOfVerticesPerLine 100
#define MaxHeight 10.0f
class Terrain
{
public:
	Terrain(std::string terrainTextureFilename);
	~Terrain();
	void renderTerrain()
	{
		terrain->prepare();
		terrain->render();
		terrain->unprepare();
	};
	Model* getModel()
	{
		return terrain->getModel();
	}
	Texture* getTexture()
	{
		return terrain->getTexture();
	}
private:
	float **heights;
	TexturedModel *terrain;


	class NoiseGenerator
	{
	public:
		NoiseGenerator(int seed)
		{
			this->seed = seed;
		};
		~NoiseGenerator()
		{

		};
		float getSmoothRandomNoise(float x, float y)
		{
			float corners = (getRandomNoise(x - 1, y - 1) + getRandomNoise(x - 1, y + 1) + getRandomNoise(x + 1, y - 1) + getRandomNoise(x + 1, y + 1)) / 16.0f;
			float sides = (getRandomNoise(x - 1, y) + getRandomNoise(x, y + 1) + getRandomNoise(x + 1, y) + getRandomNoise(x + 1,y)) / 8.0f;
			float center = getRandomNoise(x, y) / 4;
			return corners + sides + center;
		}
		float getRandomNoise(float x,float y)
		{
			srand(seed*x+y*x);
			return float(rand() % 1001) / 500.0f - 1.0f;
		}
		float getInterpolatedNoise(float x, float y)
		{
			int integerX = int(x);
			float fractionalX = x - integerX;

			int integerY = int(y);
			float fractionalY = y - integerY;

			float tl, tr, bl, br;
			tl = getSmoothRandomNoise(integerX, integerY);
			tr = getSmoothRandomNoise(integerX+1, integerY);
			bl = getSmoothRandomNoise(integerX, integerY+1);
			br = getSmoothRandomNoise(integerX+1, integerY+1);

			float interx = cosineInterpolate(tl, tr, fractionalX);
			float interxb = cosineInterpolate(bl, br, fractionalX);

			return cosineInterpolate(interx, interxb, fractionalY);
		}
		float cosineInterpolate(float a, float b, float x)
		{
			float p = x*3.1415927;
			float f = (1 - cos(p))*0.5;
			return a*(1 - f) + b*f;
		};
	private:
		int seed;

	};
};

