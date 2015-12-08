#include "Terrain.h"

std::vector<float> getHeights(int dimensions, int maxHeight)
{
	std::vector<float> temp;
	for (int z = 0; z < dimensions + 1; z++)
	{
		for (int x = 0; x < dimensions + 1; x++)
		{
			temp.push_back(((rand() % 32768) / 32768.0)*(rand() % maxHeight));
		}
	}
	return temp;
} 
void addPoint(std::vector<float> &vec, vec3f point)
{
	vec.push_back(point.getX()); vec.push_back(point.getY()); vec.push_back(point.getZ());
}
void addQuad(std::vector<float> &vec, vec3f tl, vec3f tr, vec3f bl, vec3f br)
{
	addPoint(vec, tr);
	addPoint(vec, tl);
	addPoint(vec, bl);

	addPoint(vec, tr);
	addPoint(vec, bl);
	addPoint(vec, br);
}
#define TwoD2OneD(x,y,s) (y*s)+x 
Terrain::Terrain(int dimensions, int cellnum, int maxHeight, vec3f origin, int flag)
{
	std::vector<float> position;
	std::vector<float> normal;

	float cellSize = (float)dimensions / (float)cellnum;
	heightmap = getHeights(cellnum, maxHeight);

	for (int z = 0; z < cellnum; z++)
	{
		for (int x = 0; x < cellnum; x++)
		{
			vec3f tl(x*cellSize, heightmap[z*cellnum + x], z*cellSize); vec3f tr((x + 1)*cellSize, heightmap[z*cellnum + x + 1], z*cellSize);
			vec3f bl(x*cellSize, heightmap[(z+1)*cellnum + x], (z+1)*cellSize); vec3f br((x + 1)*cellSize, heightmap[(z+1)*cellnum + x + 1], (z+1)*cellSize);

			addQuad(position, tl + origin, tr + origin, bl + origin, br + origin);

			vec3f n1 = tl - tr;
			vec3f n2 = bl - tr;
			vec3f n = n1.CrossProduct(n2);
			n = n.getNormal();
			addPoint(normal, n); addPoint(normal, n); addPoint(normal, n);

			n1 = bl - tr;
			n2 = br - tr;
			n = n1.CrossProduct(n2);
			n = n.getNormal();
			addPoint(normal, n); addPoint(normal, n); addPoint(normal, n);
		}
	}
//	terrainModel.uploadDataToAttribute(0, &position[0], position.size()*sizeof(float), 3, position.size() / 3);
//	terrainModel.uploadDataToAttribute(1, &normal[0], normal.size()*sizeof(float), 3, position.size() / 3);
}
void Terrain::Render()
{
	terrainModel.Render();
};