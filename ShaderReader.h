#pragma once
#include <string>
#include <vector>

/* This is a utility class that reads, creates and stores shader programs for GLSL*/
class ShaderReader
{
public:
	enum class shaderType
	{
		vertex, fragment
	};

	struct shader
	{
		shaderType type;
		const char* shader;
		unsigned int shaderObject;
	};

	static unsigned int readShader(shaderType shad, const std::string& path);
	static unsigned int linkShaders(unsigned int vertexShader, unsigned int fragmentShader);

	static std::vector<unsigned int> vertexShaders;
	static std::vector<unsigned int> fragmentShaders;
	static std::vector<unsigned int> shaderPrograms;
};

