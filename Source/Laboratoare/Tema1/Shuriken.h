#pragma once

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Random.h"

class Shuriken {
public:
	float x = 1280.0f, y = 100.0f;
	float rotation = 1.0f;
	float speed = 100;
	bool ready = true;
	bool hit = false;
	float collisionX = 50.0f;
	float collisionY = 50.0f;
	float MAX_WIDTH = 1280;
	float MAX_HEIGHT = 720;


public:
	Shuriken();
	Shuriken(float x, float y);
	~Shuriken();

public: 
	Mesh* CreateShuriken(std::string name, float scale, glm::vec3 base, float length, glm::vec3 color, bool fill = false);
	void reset();
	void generateShuriken();
	void move(glm::mat3 *modelMatrix, float deltaTimeSeconds, float speed);
};