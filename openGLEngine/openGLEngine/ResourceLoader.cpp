#include "ResourceLoader.h"
#include <vector>

ResourceLoader::ResourceLoader()
{

}


ResourceLoader::~ResourceLoader()
{

}
ModelInformation ResourceLoader::loadModelDatafromOBJFile(const char *filename, int flag)
{
	ModelInformation temp;
	switch (flag)
	{
	case Position:
		break;
	case Position_Normal:
		temp=objLoaderPN(filename);
		break;
	case Position_Texture:
		temp = objLoaderPT(filename);
		break;
	case Position_Texture_Normal:
		temp = objLoaderPTN(filename);
		break;

	default:
		temp.NumOfVertices = 0;
		break;
	};
	return temp;
}
void ResourceLoader::loadModelfromOBJFile(const char* filename, int flag,bool indexed,Model *model)
{
	ModelInformation temp;
	std::cout << "Error0" << std::endl;
	if (indexed)
	{
		temp = ResourceLoader::objLoaderPTN_indexed(filename);
	}
	else
	{
		temp = ResourceLoader::loadModelDatafromOBJFile(filename, flag);
	}

	model->uploadDataToAttribute(0, 3, temp.position);
	std::cout << "Error1" << std::endl;
	if (flag==Position_Normal||flag==Position_Texture_Normal)
	model->uploadDataToAttribute(1, 3, temp.normal);
	std::cout << "Error2" << std::endl;
	if (flag==Position_Texture||flag==Position_Texture_Normal)
	model->uploadDataToAttribute(2, 2, temp.textureCoordinates);
	std::cout << "Error3" << std::endl;
	if (!temp.indexbuffer.empty())
	{
		model->uploadDataToElement(temp.indexbuffer);
	}
}
ModelInformation ResourceLoader::objLoaderPT(const char*filename)
{
	ModelInformation tempindexed;
	ModelInformation tempNonIndexed;
	std::ifstream file(filename);
	std::vector<int> indicesPos;
	std::vector<int> indicesTex;

	std::string line;
	while (std::getline(file, line))
	{
		if (line[0] != '#')
		{
			if (line[0] == 'v')
			{
				if (line[1] == 't')
				{
					line = line.substr(2);
					float x, y = 0;
					sscanf_s(line.c_str(), "%f %f", &x, &y);
					tempNonIndexed.textureCoordinates.push_back(x);
					tempNonIndexed.textureCoordinates.push_back(y);
				}
				else if (line[1] == ' ')
				{
					line = line.substr(2);
					float x, y, z = 0;
					sscanf_s(line.c_str(), "%f %f %f", &x, &y, &z);
					tempNonIndexed.position.push_back(x);
					tempNonIndexed.position.push_back(y);
					tempNonIndexed.position.push_back(z);
				}
			}
			else if (line[0] == 'f')
			{
				line = line.substr(1);
				float a, b, c, d, e, f = 0;
				sscanf_s(line.c_str(), "%f/%f  %f/%f  %f/%f", &a, &b, &c, &d, &e, &f);
				indicesPos.push_back(a);
				indicesTex.push_back(b);
				indicesPos.push_back(c);
				indicesTex.push_back(d);
				indicesPos.push_back(e);
				indicesTex.push_back(f);
			}
		}
	}
	file.close();
	tempindexed.NumOfVertices = indicesPos.size();
	for (int i = 0; i < indicesPos.size(); i++)
	{
		tempindexed.position.push_back(tempNonIndexed.position[(indicesPos[i] - 1) * 3]);
		tempindexed.position.push_back(tempNonIndexed.position[(indicesPos[i] - 1) * 3 + 1]);
		tempindexed.position.push_back(tempNonIndexed.position[(indicesPos[i] - 1) * 3 + 2]);
	}
	for (int i = 0; i < indicesTex.size(); i++)
	{
		tempindexed.textureCoordinates.push_back(tempNonIndexed.textureCoordinates[(indicesTex[i] - 1) * 2]);
		tempindexed.textureCoordinates.push_back(tempNonIndexed.textureCoordinates[(indicesTex[i] - 1) * 2 + 1]);
	}
	std::cout << "Amount inside Texture Coordinates: "<<tempindexed.textureCoordinates.size() << std::endl;
	return tempindexed;
}
ModelInformation ResourceLoader::objLoaderPN(const char*filename)
{
	ModelInformation tempindexed;
	ModelInformation tempNonIndexed;
	std::ifstream file(filename);
	std::vector<int> indicesPos;
	std::vector<int> indicesNorm;

	std::string line;
	while (std::getline(file, line))
	{
		if (line[0] != '#')
		{
			if (line[0] == 'v')
			{
				if (line[1] == 'n')
				{
					line = line.substr(2);
					float x, y, z = 0;
					sscanf_s(line.c_str(), "%f %f %f", &x, &y, &z);
					tempNonIndexed.normal.push_back(x);
					tempNonIndexed.normal.push_back(y);
					tempNonIndexed.normal.push_back(z);
				}
				else
				{
					line = line.substr(2);
					float x, y, z = 0;
					sscanf_s(line.c_str(), "%f %f %f", &x, &y, &z);
					tempNonIndexed.position.push_back(x);
					tempNonIndexed.position.push_back(y);
					tempNonIndexed.position.push_back(z);
				}
			}
			else if (line[0] == 'f')
			{
				line = line.substr(1);
				float a, b, c, d, e, f = 0;
				sscanf_s(line.c_str(), "%f//%f  %f//%f  %f//%f", &a, &b, &c, &d, &e, &f);
				indicesPos.push_back(a);
				indicesNorm.push_back(b);
				indicesPos.push_back(c);
				indicesNorm.push_back(d);
				indicesPos.push_back(e);
				indicesNorm.push_back(f);
			}
		}
	}
	file.close();
	tempindexed.NumOfVertices = indicesPos.size();
	for (int i = 0; i < indicesPos.size(); i++)
	{
		tempindexed.position.push_back(tempNonIndexed.position[(indicesPos[i] - 1) * 3]);
		tempindexed.position.push_back(tempNonIndexed.position[(indicesPos[i] - 1) * 3 + 1]);
		tempindexed.position.push_back(tempNonIndexed.position[(indicesPos[i] - 1) * 3 + 2]);
	}
	for (int i = 0; i < indicesNorm.size(); i++)
	{
		tempindexed.normal.push_back(tempNonIndexed.normal[(indicesNorm[i] - 1) * 3]);
		tempindexed.normal.push_back(tempNonIndexed.normal[(indicesNorm[i] - 1) * 3 + 1]);
		tempindexed.normal.push_back(tempNonIndexed.normal[(indicesNorm[i] - 1) * 3 + 2]);
	}
	return tempindexed;
}
ModelInformation ResourceLoader::objLoaderPTN(const char*filename)
{
	ModelInformation tempindexed;
	ModelInformation tempNonIndexed;
	std::ifstream file(filename);
	std::vector<int> indicesPos;
	std::vector<int> indicesTex;
	std::vector<int> indicesNorm;
	double time = glfwGetTime();
	std::string line;
	while (getline(file, line))
	{
		if (line[0] != '#')
		{
			if (line[0] == 'v')
			{
				if (line[1] == 't')
				{
					line = line.substr(2);
					float x, y = 0;
					sscanf_s(line.c_str(), "%f %f", &x, &y);
					tempNonIndexed.textureCoordinates.push_back(x);
					tempNonIndexed.textureCoordinates.push_back(y);
				}
				else if (line[1] == 'n')
				{
					line = line.substr(2);
					float x, y, z = 0;
					sscanf_s(line.c_str(), "%f %f %f", &x, &y, &z);
					tempNonIndexed.normal.push_back(x);
					tempNonIndexed.normal.push_back(y);
					tempNonIndexed.normal.push_back(z);
				}
				else
				{
					line = line.substr(2);
					float x, y, z = 0;
					sscanf_s(line.c_str(), "%f %f %f", &x, &y, &z);
					tempNonIndexed.position.push_back(x);
					tempNonIndexed.position.push_back(y);
					tempNonIndexed.position.push_back(z);
				}
			}
			else if (line[0] == 'f')
			{
				line = line.substr(1);
				float a, b, c, d, e, f, g, h, i = 0;
				sscanf_s(line.c_str(), "%f/%f/%f  %f/%f/%f  %f/%f/%f", &a, &b, &c, &d, &e, &f, &g, &h, &i);
				indicesPos.push_back(a);
				indicesTex.push_back(b);
				indicesNorm.push_back(c);

				indicesPos.push_back(d);
				indicesTex.push_back(e);
				indicesNorm.push_back(f);

				indicesPos.push_back(g);
				indicesTex.push_back(h);
				indicesNorm.push_back(i);
			}
		}
	}
	file.close();
	tempindexed.NumOfVertices = indicesPos.size();
	for (int i = 0; i < indicesPos.size(); i++)
	{
		tempindexed.position.push_back(tempNonIndexed.position[(indicesPos[i] - 1) * 3]);
		tempindexed.position.push_back(tempNonIndexed.position[(indicesPos[i] - 1) * 3 + 1]);
		tempindexed.position.push_back(tempNonIndexed.position[(indicesPos[i] - 1) * 3 + 2]);
	};
	for (int i = 0; i < indicesTex.size(); i++)
	{
		tempindexed.textureCoordinates.push_back(tempNonIndexed.textureCoordinates[(indicesTex[i] - 1) * 2]);
		tempindexed.textureCoordinates.push_back(tempNonIndexed.textureCoordinates[(indicesTex[i] - 1) * 2 + 1]);
	};
	for (int i = 0; i < indicesNorm.size(); i++)
	{
		tempindexed.normal.push_back(tempNonIndexed.normal[(indicesNorm[i] - 1) * 3]);
		tempindexed.normal.push_back(tempNonIndexed.normal[(indicesNorm[i] - 1) * 3 + 1]);
		tempindexed.normal.push_back(tempNonIndexed.normal[(indicesNorm[i] - 1) * 3 + 2]);
	};
	tempindexed.indexbuffer = std::vector<unsigned int>();
	std::cout << "It took " << glfwGetTime() - time << " seconds to read OBJ file: " << filename << std::endl;
	return tempindexed;
}
ModelInformation ResourceLoader::objLoaderPTN_indexed(const char*filename)
{
	ModelInformation tempindexed;
	ModelInformation tempNonIndexed;
	std::ifstream file(filename);
	std::vector<int> indicesPos;
	std::vector<int> indicesTex;
	std::vector<int> indicesNorm;
	int currentindex = 0;
	std::vector<std::pair<vec3f, unsigned int>> element;
	std::vector<unsigned int> indexbuffer;

	std::string line;
	while (getline(file, line))
	{
		if (line[0] != '#')
		{
			if (line[0] == 'v')
			{
				if (line[1] == 't')
				{
					line = line.substr(2);
					float x, y = 0;
					sscanf_s(line.c_str(), "%f %f", &x, &y);
					tempNonIndexed.textureCoordinates.push_back(x);
					tempNonIndexed.textureCoordinates.push_back(y);
				}
				else if (line[1] == 'n')
				{
					line = line.substr(2);
					float x, y, z = 0;
					sscanf_s(line.c_str(), "%f %f %f", &x, &y, &z);
					tempNonIndexed.normal.push_back(x);
					tempNonIndexed.normal.push_back(y);
					tempNonIndexed.normal.push_back(z);
				}
				else
				{
					line = line.substr(2);
					float x, y, z = 0;
					sscanf_s(line.c_str(), "%f %f %f", &x, &y, &z);
					tempNonIndexed.position.push_back(x);
					tempNonIndexed.position.push_back(y);
					tempNonIndexed.position.push_back(z);
				}
			}
			else if (line[0] == 'f')
			{
				line = line.substr(1);
				float a, b, c, d, e, f, g, h, i = 0;
				sscanf_s(line.c_str(), "%f/%f/%f  %f/%f/%f  %f/%f/%f", &a, &b, &c, &d, &e, &f, &g, &h, &i);
				indicesPos.push_back(a);
				indicesTex.push_back(b);
				indicesNorm.push_back(c);

				indicesPos.push_back(d);
				indicesTex.push_back(e);
				indicesNorm.push_back(f);

				indicesPos.push_back(g);
				indicesTex.push_back(h);
				indicesNorm.push_back(i);
			}
		}
	}
	file.close();
	tempindexed.NumOfVertices = indicesPos.size();
	std::cout << "Amount of Indices: " << indicesPos.size() << std::endl;
	vec3f currentVertex;
	for (int i = 0; i<indicesPos.size(); i++)
	{
		std::cout << "At Position: " << i << std::endl;
		currentVertex = vec3f(indicesPos[i], indicesTex[i], indicesNorm[i]);
		if (element.empty())
		{
			element.push_back(std::make_pair(currentVertex, currentindex++));
		}
		for (int i = 0; i<element.size(); i++)
		{
			if (element[i].first.getX() == currentVertex.getX() && element[i].first.getY() == currentVertex.getY() && element[i].first.getZ() == currentVertex.getZ())
			{
				indexbuffer.push_back(element[i].second);
				break;
			}
			if (i == (element.size() - 1))
			{
				element.push_back(std::make_pair(currentVertex, currentindex++));
			}
		}
	}

	for (int i = 0; i < element.size(); i++)
	{
		
		tempindexed.position.push_back(tempNonIndexed.position[(element[i].first.getX() - 1) * 3]);
		tempindexed.position.push_back(tempNonIndexed.position[(element[i].first.getX()-1) * 3 + 1]);
		tempindexed.position.push_back(tempNonIndexed.position[(element[i].first.getX()-1) * 3 + 2]);

		tempindexed.textureCoordinates.push_back(tempNonIndexed.textureCoordinates[(element[i].first.getY()-1) * 2]);
		tempindexed.textureCoordinates.push_back(tempNonIndexed.textureCoordinates[(element[i].first.getY()-1) * 2 + 1]);

		tempindexed.normal.push_back(tempNonIndexed.normal[(element[i].first.getZ() - 1) * 3]);
		tempindexed.normal.push_back(tempNonIndexed.normal[(element[i].first.getZ() - 1) * 3 + 1]);
		tempindexed.normal.push_back(tempNonIndexed.normal[(element[i].first.getZ() - 1) * 3 + 2]);
	};
	tempindexed.indexbuffer = indexbuffer;
	tempindexed.NumOfVertices = indexbuffer.size();
	return tempindexed;
};
Texture ResourceLoader::loadTextureFromBMP(const char*filename)
{
	Texture temp;
	temp.loadTexture(filename);
	return temp;
}
