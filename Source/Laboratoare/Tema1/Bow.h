#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include "Transform2D.h"


class Bow {
public:
	float x = 20.0f, y = 250.0f;
	float length = 80;
	float speed = 700.0f;
	int mouseX, mouseY;
	glm::mat3 modelMatrix = glm::mat3(1);
	float MAX_HEIGHT;
	float MAX_WIDTH;


public:
	Bow();
	Bow(float x, float y);
	~Bow();

public:
	Mesh* CreateBow(std::string name, float scale, glm::vec3 color);
	void moveUp(float deltaTime);
	void moveDown(float deltaTime);
	void rotate(int mouseX, int mouseY);
	void resetModelMatrix();
};