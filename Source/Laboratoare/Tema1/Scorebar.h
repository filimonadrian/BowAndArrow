#pragma once

#include <Core/GPU/Mesh.h>
#include "Transform2D.h"
#include <include/glm.h>


class Scorebar {
public:
	float x, y;
	float length = 10.0f, width = 1.0f;

public: 
	Scorebar();
	Scorebar(float x, float y);
	~Scorebar();
public: 
	Mesh* Scorebar::CreateScorebar(std::string name, glm::vec3 color, bool fill);

};