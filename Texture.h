#pragma once
#include <string>

class Texture
{
public:
	int width, height, channelCount;

	unsigned int textureObject;

	void loadTexture(std::string sourcePath);
	bool loaded = false;

	Texture();
	Texture(std::string sourcePath);
};

