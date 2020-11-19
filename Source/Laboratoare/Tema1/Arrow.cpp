#include "Arrow.h"

#include <Core/Engine.h>


Arrow::Arrow() {
}

Arrow::~Arrow() {
}

Arrow::Arrow(float x, float y) {
	this->x = x;
	this->y = y;
}


Mesh* Arrow::CreateArrow(std::string name, float scale, glm::vec3 base, glm::vec3 color, bool fill) {
	float peakLength = 20.0f;
	float peakWidth = 20.0f;


	std::vector<VertexFormat> vertices =
	{
		VertexFormat(base, color),
		VertexFormat(base + glm::vec3(length, 0, 0), color),
		VertexFormat(base + glm::vec3(length - peakLength, peakWidth, 0), color),
		VertexFormat(base + glm::vec3(length - peakLength, -peakWidth, 0), color)
	};

	Mesh* arrow = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 1, 2, 1, 3, 2, 3};

	if (!fill) {
		arrow->SetDrawMode(GL_LINES);
	}
	else {
		arrow->SetDrawMode(GL_POLYGON);
	}

	arrow->InitFromData(vertices, indices);
	return arrow;
}

void Arrow::reset() {
	this->x = 0;
	this->y = 0;
	this->ready = true;
	this->speed = 1;
}


void Arrow::move(glm::mat3* modelMatrix, float deltaTimeSeconds) {
	// if it's not used => can't move it
	if (this->ready) {
		return;
	}
	if (this->x >= MAX_WIDTH || this->y >= MAX_HEIGHT || 
		this->x < -10 || this->y < -20) {
		this->reset();
	}
	else {
		// calculate the angle
		float a = this->mouseX - this->x;
		float b = this->mouseY - this->y;
		float angle = atan(b / a);
				
		this->x += cos(angle) * deltaTimeSeconds * speed;
		this->y += sin(angle) * deltaTimeSeconds * speed;
		
		
		this->topX = this->x + cos(angle) * this->length;
		this->topY = this->y + sin(angle) * this->length;
		*modelMatrix *= Transform2D::Translate(this->x, this->y);
		*modelMatrix *= Transform2D::Rotate(angle);

	}
}

void Arrow::rotate(glm::mat3* modelMatrix, int mouseX, int mouseY) {
	this->mouseY = MAX_HEIGHT - mouseY - length / 2;
	this->mouseX = mouseX;

	float a = this->mouseX - this->x;
	float b = this->mouseY - this->y;
	float angle = atan(b / a);

	this->resetModelMatrix();

	*modelMatrix *= Transform2D::Translate(this->x, this->y);
	*modelMatrix *= Transform2D::Rotate(angle);
}

void Arrow::resetModelMatrix() {
	this->modelMatrix = glm::mat3(1);
}
