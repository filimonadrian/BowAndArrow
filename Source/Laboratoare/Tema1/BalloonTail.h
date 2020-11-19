#pragma once

#include <Core/GPU/Mesh.h>
#include "Transform2D.h"
#include <include/glm.h>


class BalloonTail {
public:
	float x, y, size = 1;

public:
	BalloonTail();
	BalloonTail(float x, float y);
	~BalloonTail();
public:
	Mesh* BalloonTail::CreateBalloonTail(std::string name, glm::vec3 color);

};