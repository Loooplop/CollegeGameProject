#include "Terrain.h"
#define addVectorDataToVector(x,y) y.push_back(x.getX());y.push_back(x.getY());y.push_back(x.getZ());
#define addVectorDataToVectorTex(x,y) y.push_back(x.getX());y.push_back(x.getY());
Terrain::Terrain(std::string terrainTextureFilename)
{
	terrain = new TexturedModel();
	terrain->setTexture(new Texture(terrainTextureFilename.c_str(), GL_TEXTURE_2D));
	Model* terrainModel = new Model();
	heights = new float*[AmountOfVerticesPerLine+1];
	for (int i = 0; i < AmountOfVerticesPerLine+1; i++)
	{
		heights[i] = new float[AmountOfVerticesPerLine+1];
	}
	std::vector<float> pos, norm, tex;
	float distancebetweenpoint = TerrainSize/AmountOfVerticesPerLine;
	float textureCoord = 1.0f / AmountOfVerticesPerLine;
	NoiseGenerator gen(rand());
	for (int y = 0; y < AmountOfVerticesPerLine+1; y++)
	{
		for (int x = 0; x < AmountOfVerticesPerLine+1; x++)
		{
			heights[x][y] = 0;
		}
	}
	
	for (int z = 0; z < AmountOfVerticesPerLine; z++)
	{
		for (int x = 0; x < AmountOfVerticesPerLine; x++)
		{
			vec3f topLeft(x*distancebetweenpoint, heights[x][z], z*distancebetweenpoint);
			vec3f topRight((x + 1)*distancebetweenpoint, heights[x + 1][z], z*distancebetweenpoint);

			vec3f bottomLeft(x*distancebetweenpoint, heights[x][z+1], (z+1)*distancebetweenpoint);
			vec3f bottomRight((x + 1)*distancebetweenpoint, heights[x + 1][z+1], (z+1)*distancebetweenpoint);
			std::cout << topLeft << topRight << bottomLeft << bottomRight << std::endl;
			
			//Position
			addVectorDataToVector(bottomLeft, pos);
			addVectorDataToVector(topLeft, pos);
			addVectorDataToVector(topRight, pos);

			addVectorDataToVector(bottomLeft, pos);
			addVectorDataToVector(topRight, pos);
			addVectorDataToVector(bottomRight, pos);
			//Normal
			vec3f U = topLeft - bottomLeft;
			vec3f V = topRight - topLeft;
			U = U.getNormal();
			V = V.getNormal();
			vec3f triangleNormal = U.CrossProduct(V);
			addVectorDataToVector(triangleNormal, norm); addVectorDataToVector(triangleNormal, norm); addVectorDataToVector(triangleNormal, norm);


			U = topRight - bottomLeft;
			V = bottomRight - topRight;
			U = U.getNormal();
			V = V.getNormal();
			triangleNormal = U.CrossProduct(V);
			addVectorDataToVector(triangleNormal, norm); addVectorDataToVector(triangleNormal, norm); addVectorDataToVector(triangleNormal, norm);
			//Texture
			vec2f texTopLeft(x*textureCoord, z*textureCoord);
			vec2f texTopRight((x+1)*textureCoord, z*textureCoord);
			vec2f texBottomLeft(x*textureCoord, (z+1)*textureCoord);
			vec2f texBottomRight((x+1)*textureCoord, (z+1)*textureCoord);

			addVectorDataToVectorTex(bottomLeft, tex);
			addVectorDataToVectorTex(topLeft, tex);
			addVectorDataToVectorTex(topRight, tex);

			addVectorDataToVectorTex(bottomLeft, tex);
			addVectorDataToVectorTex(topRight, tex);
			addVectorDataToVectorTex(bottomRight, tex);
		}
	}
	terrainModel->uploadDataToAttribute(0, 3, pos);
	terrainModel->uploadDataToAttribute(1, 3, norm);
	terrainModel->uploadDataToAttribute(2, 2, tex);
	terrain->setModel(terrainModel);
}

Terrain::~Terrain()
{
	delete terrain;

	for (int i = 0; i < AmountOfVerticesPerLine+1; i++)
	{
		delete heights[i];
	}
	delete heights;
}
