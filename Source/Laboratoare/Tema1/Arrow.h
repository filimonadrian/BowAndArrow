#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include "Transform2D.h"

class Arrow {
public: 
	float x = 0.0f, y = 0.0f;
	float MAX_WIDTH = 1280;
	float MAX_HEIGHT = 720;

	float speed = 1;
	bool ready = true;
	float length = 150.0f;
	int mouseX, mouseY;
	glm::mat3 modelMatrix = glm::mat3(1);
	float topX, topY;

public: 
	Arrow();
	Arrow(float x, float y);
	~Arrow();

public:
	Mesh* CreateArrow(std::string name, float scale, glm::vec3 base, glm::vec3 color, bool fill = false);
	void reset();
	void move(glm::mat3* modelMatrix, float deltaTimeSeconds);
	void rotate(glm::mat3* modelMatrix, int mouseX, int mouseY);
	void resetModelMatrix();
};