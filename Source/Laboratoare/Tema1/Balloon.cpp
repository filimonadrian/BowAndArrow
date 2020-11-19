#include "Balloon.h"

#include <Core/Engine.h>
#include "Transform2D.h"
#include <iostream>
#include <random>

Balloon::Balloon() {
}

Balloon::~Balloon() {
}

Balloon::Balloon(float x, float y) {
	this->x = x;
	this->y = y;
}


Mesh* Balloon::CreateBalloon(std::string name, float scale, int numberOfTriangles, glm::vec3 color, bool fill)
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	float x;
	float PI = 3.149f;
	int i = 0;

	vertices.emplace_back(glm::vec3(0, 0, 0), color);
	for (i = 0; i < numberOfTriangles; i++) {

		x = i * (2 * PI) / numberOfTriangles;

		vertices.emplace_back(glm::vec3(cos(x) * scale, sin(x) * (scale + 10), 0), color);
		indices.push_back(i);

	}
	
	indices.push_back(numberOfTriangles);
	indices.push_back(1);
		
	Mesh* balloon = new Mesh(name);

	if (!fill) {
		balloon->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		balloon->SetDrawMode(GL_POLYGON);
	}

	balloon->InitFromData(vertices, indices);
	return balloon;
}

void Balloon::reset() {
	this->x = 0;
	this->y = -10;
	this->scaleX = 1;
	this->scaleY = 1;
	this->ready = true;
	this->color = "";
	this->hit = false;
}

// generates random x and y
// x will be between 300 -> 1280
// y will be between [-15, 0] => the objects will not appear in the same time
void Balloon::generateBalloon() {
	this->x = generateFloat(300, 1180);
	this->y = (-1) * generateFloat(10, 100);
	this->color = generateInt(0, 1);
	this->ready = false;
	int aux_color = generateInt(0, 1);
	if (aux_color == 0) {
		this->color = "red-balloon";
	}
	else {
		this->color = "yellow-balloon";
	}
}

void Balloon::move(glm::mat3* modelMatrix, float deltaTimeSeconds, float speed) {
	// if the balloon is not used => i can't move it
	if (this->ready) {
		return;
	}
	// if ballon is to high or is hit and is too low => reset it
	if (this->y > 1290 || (this->hit && this-> y < -20)) {
		this->reset();
	}

	// if the balloon is not hit => rises too the sky
	if (!this->hit) {
		*modelMatrix *= Transform2D::Translate(x, y);
		this->y += deltaTimeSeconds * speed;
	} else {
		*modelMatrix *= Transform2D::Translate(x, y);
		this->y -= deltaTimeSeconds * speed;
	}
}