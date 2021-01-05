#pragma once
#include <vector>
#include <string>

class Model
{
public:
	struct Vertex
	{
		float posX, posY, posZ;
		float normX, normY, normZ;
		float teX, teY;
	};

	std::vector<Vertex> vertexData;
	std::vector<int> indexData;

	void printModel();
	void loadModel(std::string sourcePath);
	bool loaded = false;

	Model(std::string sourcePath);
	Model(std::vector<Vertex>* verticesPtr);
};

