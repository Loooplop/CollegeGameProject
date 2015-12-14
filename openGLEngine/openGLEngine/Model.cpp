#include "Model.h"
#include "WE_Matrix.h"
#include <string>

#include "ResourceLoader.h"
unsigned int Model::curretModelIndex = 1;
Model::Model()
{
	VAO  = -1;
	VBOs = vector<GLuint>();
	numOfVertices = 0;
	glGenVertexArrays(1, &this->VAO);
	modelID = Model::curretModelIndex++;
}
Model::Model(std::string filename, int objFileStructureFlag, bool isIndexed)
{
	VAO = -1;
	VBOs = vector<GLuint>();
	numOfVertices = 0;
	glGenVertexArrays(1, &this->VAO);
	modelID = Model::curretModelIndex++;
	ModelInformation modelInfo = ResourceLoader::loadModelDatafromOBJFile(filename.c_str(), objFileStructureFlag);
	uploadDataToAttribute(0, 3, modelInfo.position);
	uploadDataToAttribute(1, 3, modelInfo.normal);
	uploadDataToAttribute(2, 2, modelInfo.textureCoordinates);
};
Model::~Model()
{
	glDeleteVertexArrays(1, &VAO);
	
	for (int i = 0; i < VBOs.size();i++)
	glDeleteBuffers(1, &VBOs[i]);

	if (isIndexed)
	glDeleteBuffers(1, &EBO);
	
	VBOs.clear();
	attributes.clear();
	std::cout << "Destroyed Model" << std::endl;
}
void Model::uploadDataToAttribute(int attribute, int componentsize, std::vector<float> data)
{
	this->numOfVertices = (data.size() / componentsize);
	std::cout << "Vertices amount: " << numOfVertices << std::endl;
	glBindVertexArray(this->VAO);
	GLuint VBOtemp;

	glGenBuffers(1, &VBOtemp);
	glBindBuffer(GL_ARRAY_BUFFER, VBOtemp);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*data.size(), &data[0], GL_STATIC_DRAW);
	VBOs.push_back(VBOtemp);

	glVertexAttribPointer(attribute, componentsize, GL_FLOAT, GL_FALSE, 0, (void*)0);
	attributes.push_back(attribute);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
};
void Model::Render()
{
	glBindVertexArray(this->VAO);

	for (int i = 0; i < attributes.size(); i++)
	{
		glEnableVertexAttribArray(attributes[i]);
	}
	if (isIndexed)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	if (isIndexed)
	{
		glDrawElements(GL_TRIANGLES, numOfVertices, GL_UNSIGNED_INT, (void*)0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, numOfVertices);
	}

	if (isIndexed)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	for (int i = 0; i < attributes.size(); i++)
	glDisableVertexAttribArray(attributes[i]);

	glBindVertexArray(0);
};
void Model::prepareModel()
{
	glBindVertexArray(this->VAO);

	for (int i = 0; i < attributes.size(); i++)
		glEnableVertexAttribArray(attributes[i]);
	if (isIndexed)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
};
void Model::renderModel()
{
	if (isIndexed)
	{
		glDrawElements(GL_TRIANGLES, numOfVertices, GL_UNSIGNED_INT, (void*)0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, numOfVertices);
	}
};
void Model::unprepareModel()
{
	if (isIndexed)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	for (int i = 0; i < attributes.size(); i++)
		glDisableVertexAttribArray(attributes[i]);

	glBindVertexArray(0);

};