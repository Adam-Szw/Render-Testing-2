#include "ShaderReader.h"
#include "Utilities.h"
#include <glad/glad.h>
#include <iostream>


std::vector<unsigned int> ShaderReader::vertexShaders;
std::vector<unsigned int> ShaderReader::fragmentShaders;
std::vector<unsigned int> ShaderReader::shaderPrograms;

unsigned int ShaderReader::readShader(shaderType shad, const std::string& path)
{
	std::string shaderStr = Utilities::getFileContentDirect(path);
	const char* shaderSource = shaderStr.c_str();
	int success;
	char infoLog[512];
	if (shad == shaderType::vertex)
	{
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &shaderSource, NULL);
		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		vertexShaders.push_back(vertexShader);
		return vertexShader;
	}
	else if (shad == shaderType::fragment)
	{
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &shaderSource, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		fragmentShaders.push_back(fragmentShader);
		return fragmentShader;
	}
}

unsigned int ShaderReader::linkShaders(unsigned int vertexShader, unsigned int fragmentShader)
{
	int success;
	char infoLog[512];
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	shaderPrograms.push_back(shaderProgram);
	return shaderProgram;
}
