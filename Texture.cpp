#include "Texture.h"
#include <stb_image.h>
#include <glad/glad.h>

void Texture::loadTexture(std::string sourcePath)
{
	//for now loading in constructor TEMPORARY
	glGenTextures(1, &textureObject);
	glBindTexture(GL_TEXTURE_2D, textureObject);
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(sourcePath.c_str(), &width, &height, &channelCount, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	free(data);
	loaded = true;
}

Texture::Texture()
{
}

Texture::Texture(std::string sourcePath)
{
	loadTexture(sourcePath);
}
