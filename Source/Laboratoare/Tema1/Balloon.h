#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include "Random.h"

class Balloon {
public:
	float x = 0.0f, y = 0.0f;
	float scaleX = 1.0f, scaleY = 1.0f;
	bool ready = true;
	bool hit = false;
	std::string color;
	float collisionX = 60.0f;
	float collisionY = 50.0f;

	float MAX_WIDTH;
	float MAX_HEIGHT;
	
public:
	Balloon();
	Balloon(float x, float y);
	~Balloon();

public:
	Mesh* CreateBalloon(std::string name, float scale, int numberOfTriangles, glm::vec3 color, bool fill = false);
	void reset();
	void generateBalloon();
	void move(glm::mat3* modelMatrix, float deltaTimeSeconds, float speed);
};