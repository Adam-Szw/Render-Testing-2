#pragma once
#include "Controls.h"

class Camera
{
public:
	Maths::vec3 position;
	Maths::vec3 front = Maths::vec3(0.0f, 0.0f, 1.0f);
	Maths::vec3 up = Maths::vec3(0.0f, 1.0f, 0.0f);
	Maths::mat4 viewMatrix;

	void update(Controls* control);
};

