#include "Model.h"
#include "ObjReader.h"
#include <iostream>

void Model::printModel()
{
	std::cout << "Model stats: " << std::endl;

	for (const Model::Vertex& v : this->vertexData)
	{
		std::cout << "vertex" << std::endl;
		std::cout << "positions: " << v.posX << ' ' << v.posY << ' ' << v.posZ << std::endl;
		std::cout << "normals: " << v.normX << ' ' << v.normY << ' ' << v.normZ << std::endl;
		std::cout << "texture coords: " << v.teX << ' ' << v.teY << std::endl;
	}
	std::cout << "total vertices: " << this->vertexData.size() << std::endl;

	for (unsigned int i = 0; i < this->indexData.size(); i += 3)
	{
		std::cout << "triangle" << std::endl;
		std::cout << this->indexData[i] << ' ' << this->indexData[i + 1] << ' ' << this->indexData[i + 2] << std::endl;
	}
	std::cout << "total triangles: " << this->indexData.size() / 3 << std::endl;
}

void Model::loadModel(std::string sourcePath)
{
	ObjReader::readVerticesObj(this, sourcePath);
	loaded = true;
}

Model::Model(std::string sourcePath)
{
	loadModel(sourcePath);
}

Model::Model(std::vector<Vertex>* verticesPtr)
{
}
