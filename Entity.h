#pragma once
#include "Model.h"
#include "Texture.h"
#include <vector>
#include <map>
#include "Material.h"
#include "Maths.h"

class Entity
{
public:
	bool entityUpdate = true;

	std::vector<Model*> models;
	std::map<unsigned int, std::vector<Texture*>> texturesMap;
	std::map<unsigned int, std::vector<Maths::mat4>> modelMatrixMap;
	std::map<unsigned int, Material*> materialsMap;

	Entity();
};

