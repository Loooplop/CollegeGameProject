#pragma once
#include <vector>
#include "WE_Vector.h"
#include "Model.h";
#include "Texture.h"
class Terrain
{
public:
	Terrain(int dimensions, int cellnum, int maxHeight,vec3f origin, int flag);
	~Terrain()
	{
		heightmap.clear();
		for (int i = 0; i < terrainTextures.size(); i++)
		{
			GLuint address = terrainTextures[i].getTexture();
			glDeleteTextures(1, &address);
		}
		terrainTextures.clear();
	};

	void Render();
private:
	std::vector<float> heightmap;
	Model terrainModel;
	std::vector<Texture> terrainTextures;
};

