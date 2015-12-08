#include "Program.h"
#include <fstream>
#include <iostream>
#include <string>
Program::Program()
{
	ProgramID = glCreateProgram();
	uniformLocations = std::vector<std::pair<std::string, GLuint>>();
	shaders = std::vector<GLuint>();
}


Program::~Program()
{
	for (int i = 0; i < shaders.size(); i++)
	{
		glDetachShader(ProgramID, shaders[i]);
		glDeleteShader(shaders[i]);
	};
	glDeleteProgram(ProgramID);
	uniformLocations.clear();
}
GLuint Program::getProgramID()
{
	return ProgramID;
};
void Program::AddShader(const char *filename, GLenum type)
{
	GLuint shader;
	std::string shaderSource;
	std::ifstream file;
	file.open(std::string(filename), std::ifstream::in);
	if (file.bad())
	{
		std::cout << "Shit" << std::endl;
		file.close();
		return;
	}
	if (file.is_open())
	{
		std::string temp;
		while (std::getline(file, temp))
		{
			shaderSource += "\n"+temp;
		}
	}
	file.close();
	shader = glCreateShader(type);
	const char *info = shaderSource.c_str();
	glShaderSource(shader, 1, &info, NULL);
	glCompileShader(shader);
	GLint compileStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
	if (0 == compileStatus)
	{
		char *buffer= new char[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		std::cout << "Error on Shader File: " << filename << std::endl << buffer << std::endl;
		delete(buffer);
	}
	else
	{
		shaders.push_back(shader);
	}
};
void Program::AddShaderByString(const char *shaderData, GLenum type)
{
	std::cout << shaderData << std::endl;
	GLuint shader;
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderData, NULL);
	glCompileShader(shader);
	GLint compileStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
	if (0 == compileStatus)
	{
		std::cout << "Shader Not Added" << std::endl;
		char *buffer = new char[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		delete(buffer);
	}
	else
	{
		std::cout << "Shader Added" << std::endl;
		shaders.push_back(shader);
	}
};
void Program::CompileProgram()
{
	
	for (int i = 0; i < shaders.size(); i++)
	{
		glAttachShader(ProgramID, shaders[i]);
	}
	glLinkProgram(ProgramID);
	GLint linkStatus;
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == 0)
	{
		char *buffer = new char[512];
		glGetProgramInfoLog(ProgramID, 512, NULL, buffer);
		std::cout << "Problem Linking Program" << std::endl;
		std::cout << buffer << std::endl;
		delete(buffer);
	}
	std::cout << "Linked Correctly" << std::endl;
};


