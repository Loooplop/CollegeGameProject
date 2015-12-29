#pragma once
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <vector>

#include "Program.h"
class Model
{
public:
	Model();
	Model(std::string filename, int objFileStructureFlag, bool isIndexed);
	~Model();
	void uploadDataToAttribute(int attribute,int componentsize, std::vector<float> data);
	void uploadDataToElement(std::vector<unsigned int> indices)
	{
		glBindVertexArray(this->VAO);
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		isIndexed = true;
		numOfVertices = indices.size();
	};
	void Render();
	void prepareModel();
	void renderModel();
	void unprepareModel();
	unsigned int getModelID()
	{
		return modelID;
	}
	std::string getModelName()
	{
		return modelName;
	}
private:
	std::string modelName;
	GLuint VAO;
	GLuint EBO;
	bool isIndexed;
	std::vector<GLuint> VBOs;
	std::vector<int> attributes;
	unsigned int numOfVertices;
	unsigned int modelID;
	static unsigned int curretModelIndex;
};

