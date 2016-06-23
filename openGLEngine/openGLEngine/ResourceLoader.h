#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include "Texture.h"
#include "Model.h"
#include "Font.h"
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

	//Font
	static void loadFont(string filename);
	static Font* getFont(string filename);

	//Resource Loader Management
	static void InitResourceLoader();
	static void CleanUpResourceLoader();
	static void loadResourcesFromFile(std::string filename);
private:
	ResourceLoader();
	~ResourceLoader();

	static ModelInformation objLoaderPT(const char*filename);
	static ModelInformation objLoaderPN(const char*filename);
	static ModelInformation objLoaderPTN(const char*filename);
	static ModelInformation objLoaderPTN_indexed(const char*filename);

	static map<string, Model*> models;
	static map<string, Texture*> textures;
	static map<string, Font*> fonts;
};

