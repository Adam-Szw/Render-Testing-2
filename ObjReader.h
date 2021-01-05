#pragma once
#include "model.h"

class ObjReader
{
public:
	/* Fills out vertexData and indexData of target model object using .obj file at loc */
	static void readVerticesObj(Model* target, std::string objFileLoc);
};

