#pragma once
#include <GL\glew.h>
#include <vector>
#include "WE_Vector.h"
#include "WE_Matrix.h"
#include <algorithm>
class Program
{
public:
	Program();
	Program(std::string vertexShaderFilename, std::string fragmentShaderFilename)
	{
		ProgramID = glCreateProgram();
		uniformLocations = std::vector<std::pair<std::string, GLuint>>();
		shaders = std::vector<GLuint>();

		this->AddShader(vertexShaderFilename.c_str(), GL_VERTEX_SHADER);
		this->AddShader(fragmentShaderFilename.c_str(), GL_FRAGMENT_SHADER);
		this->CompileProgram();
	}
	~Program();

	GLuint getProgramID();
	void AddShader(const char *filename, GLenum type);
	void AddShaderByString(const char *shaderData, GLenum);
	void CompileProgram();
	void start()
	{
		glUseProgram(this->ProgramID);
	};
	void stop()
	{
		glUseProgram(0);
	}

	void uploadUniform_vec2(const std::string uniformname, vec2f data)
	{
		GLuint uniformLocation = UniformLocationFromName(uniformname);
		if (uniformLocation == -1)
		{
			std::cout << uniformname.c_str() << " does not exist in program id: " << ProgramID << std::endl;
		}
		else if (uniformLocation == -2)
		{
			GLuint uniformTrueLocation = glGetUniformLocation(ProgramID, uniformname.c_str());
			uniformLocations.push_back(std::make_pair(uniformname, uniformTrueLocation));
			glUniform2f(uniformTrueLocation, data.getX(), data.getY());
			return;
		}
		glUniform2f(uniformLocation, data.getX(), data.getY());
	};
	void uploadUniform_vec3(const std::string uniformname, vec3f data)
	{
		GLuint uniformLocation = UniformLocationFromName(uniformname);
		if (uniformLocation == -1)
		{
			std::cout << uniformname.c_str() << " does not exist in program id: " << ProgramID << std::endl;
		}
		else if (uniformLocation == -2)
		{
			GLuint uniformTrueLocation = glGetUniformLocation(ProgramID, uniformname.c_str());
			uniformLocations.push_back(std::make_pair(uniformname, uniformTrueLocation));
			glUniform3f(uniformTrueLocation, data.getX(), data.getY(), data.getZ());
			return;
		}
		glUniform3f(uniformLocation, data.getX(), data.getY(), data.getZ());
	};
	void uploadUniform_vec4(const std::string uniformname, vec4f data)
	{
		GLuint uniformLocation = UniformLocationFromName(uniformname);
		if (uniformLocation == -1)
		{
			std::cout << uniformname.c_str() << " does not exist in program id: " << ProgramID << std::endl;
		}
		else if (uniformLocation == -2)
		{
			GLuint uniformTrueLocation = glGetUniformLocation(ProgramID, uniformname.c_str());
			uniformLocations.push_back(std::make_pair(uniformname, uniformTrueLocation));
			glUniform4f(uniformTrueLocation, data.getX(), data.getY(), data.getZ(), data.getW());
			return;
		}
		glUniform4f(uniformLocation, data.getX(), data.getY(), data.getZ(), data.getW());
	};
	void uploadUniform_mat2(const std::string uniformname, mat2f data, bool transpose)
	{
		GLuint uniformLocation = UniformLocationFromName(uniformname);
		if (uniformLocation == -1)
		{
			std::cout << uniformname.c_str() << " does not exist in program id: " << ProgramID << std::endl;
		}
		else if (uniformLocation == -2)
		{
			GLuint uniformTrueLocation = glGetUniformLocation(ProgramID, uniformname.c_str());
			uniformLocations.push_back(std::make_pair(uniformname, uniformTrueLocation));
			glUniformMatrix2fv(uniformTrueLocation, 1, transpose, data.getArray());
			return;
		}
		glUniformMatrix2fv(uniformLocation, 1, transpose, data.getArray());
	};
	void uploadUniform_mat3(const std::string uniformname, mat3f data, bool transpose)
	{
		GLuint uniformLocation = UniformLocationFromName(uniformname);
		if (uniformLocation == -1)
		{
			std::cout << uniformname.c_str() << " does not exist in program id: " << ProgramID << std::endl;
		}
		else if (uniformLocation == -2)
		{
			GLuint uniformTrueLocation = glGetUniformLocation(ProgramID, uniformname.c_str());
			uniformLocations.push_back(std::make_pair(uniformname, uniformTrueLocation));
			glUniformMatrix3fv(uniformTrueLocation, 1, transpose, data.getArray());
			return;
		}
		glUniformMatrix3fv(uniformLocation, 1, transpose, data.getArray());
	};
	void uploadUniform_mat4(const std::string uniformname, mat4f data, bool transpose)
	{
		GLuint uniformLocation = UniformLocationFromName(uniformname);
		if (uniformLocation == -1)
		{
			std::cout << uniformname.c_str() << " does not exist in program id: " << ProgramID << std::endl;
		}
		else if (uniformLocation == -2)
		{
			GLuint uniformTrueLocation = glGetUniformLocation(ProgramID, uniformname.c_str());
			uniformLocations.push_back(std::make_pair(uniformname, uniformTrueLocation));
			glUniformMatrix4fv(uniformTrueLocation, 1, transpose, data.getArray());
			return;
		}
		glUniformMatrix4fv(uniformLocation, 1, transpose, data.getArray());
	};
	void uploadFloat(const std::string uniformname, float data)
	{
		GLuint uniformLocation = UniformLocationFromName(uniformname);

		if (uniformLocation == -1)
		{
			std::cout << uniformname.c_str() << " does not exist in program id: " << ProgramID << std::endl;
		}
		else if (uniformLocation == -2)
		{
			GLuint uniformTrueLocation = glGetUniformLocation(ProgramID, uniformname.c_str());
			uniformLocations.push_back(std::make_pair(uniformname, uniformTrueLocation));
			glUniform1f(uniformTrueLocation, data);
			return;
		}
		glUniform1f(uniformLocation, data);
	}
	void uploadInt(const std::string uniformname, int data)
	{
		GLuint uniformLocation = UniformLocationFromName(uniformname);

		if (uniformLocation == -1)
		{
			std::cout << uniformname.c_str() << " does not exist in program id: " << ProgramID << std::endl;
		}
		else if (uniformLocation == -2)
		{
			GLuint uniformTrueLocation = glGetUniformLocation(ProgramID, uniformname.c_str());
			uniformLocations.push_back(std::make_pair(uniformname, uniformTrueLocation));
			glUniform1f(uniformTrueLocation, data);
			return;
		}
		glUniform1i(uniformLocation, data);
	}
	void printUniformName()
	{
		for (int i = 0; i < uniformLocations.size(); i++)
		{
			std::cout << uniformLocations[i].first.c_str() << std::endl;
		}
	}
private:
	GLuint UniformLocationFromName(std::string uniformName)
	{
		if (uniformLocations.empty())
		{
			return -2;
		}
		for (int i = 0; i < uniformLocations.size(); i++)
		{
			if (uniformLocations[i].first == uniformName)
			{
				return uniformLocations[i].second;
			}
		}
		return -2;
	}
	GLuint ProgramID;
	std::vector<GLuint> shaders;
	std::vector<std::pair<std::string, GLuint>> uniformLocations;
};