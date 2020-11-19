#pragma once

#include <Core/GPU/Mesh.h>
#include "Transform2D.h"
#include <include/glm.h>


class Heart {
public:
	float x, y;
	float length = 10.0f, width = 1.0f;

public:
	Heart();
	Heart(float x, float y);
	~Heart();
public:
	Mesh* Heart::CreateHeart(std::string name, glm::vec3 color, bool fill);

};