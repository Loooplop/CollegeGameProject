#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include "Texture.h"
#include "Model.h"
#define Position 0
#define Position_Normal 1
#define Position_Texture 2
#define Position_Texture_Normal 3
struct  ModelInformation
{
	std::vector<float> position;
	std::vector<float> normal;
	std::vector<float> textureCoordinates;
	std::vector<unsigned int> indexbuffer;
	int NumOfVertices;
};

class ResourceLoader
{
public:
	//Model
	static ModelInformation loadModelDatafromOBJFile(const char* filename, int flag);
	static void loadModelfromOBJFile(const char* filename, int flag, bool indexed,Model *model);
	static void loadModel(string filename, bool indexed);
	static Model* getModel(string filename);

	//Texture
	static void loadTexture(string filename, GLenum textureType);
	static Texture* getTexture(string filename);

	//Resource Loader Management
	static void InitResourceLoader();
	static void CleanUpResourceLoader();
private:
	static ModelInformation objLoaderPT(const char*filename);
	static ModelInformation objLoaderPN(const char*filename);
	static ModelInformation objLoaderPTN(const char*filename);
	static ModelInformation objLoaderPTN_indexed(const char*filename);
	ResourceLoader();
	~ResourceLoader();
	static map<string, Model*> models;
	static map<string, Texture*> textures;
};

