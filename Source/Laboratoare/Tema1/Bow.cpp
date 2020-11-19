#include "Bow.h"

#include <Core/Engine.h>

Bow::Bow() {
	this->modelMatrix *= Transform2D::Translate(this->x, this->y);
	modelMatrix *= Transform2D::Scale(3, 3);
}

Bow::~Bow() {
}

Bow::Bow(float x, float y) {
	this->x = x;
	this->y = y;
	this->modelMatrix *= Transform2D::Translate(this->x, this->y);
	modelMatrix *= Transform2D::Scale(3, 3);
}

Mesh* Bow::CreateBow(std::string name, float scale, glm::vec3 color) {
	
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	vertices.emplace_back(glm::vec3(0, 0, 0), color);

	float angle;
	for (int i = 0; i < 100; i++)
	{
		angle = 3.14 * i / 100;
		vertices.emplace_back(glm::vec3(scale * cos(angle), scale / 2 * sin(angle), 0), color);

		indices.push_back(i);
	}
	indices.push_back(100);

	Mesh* bow = new Mesh(name);

	bow->SetDrawMode(GL_LINE_LOOP);
	bow->InitFromData(vertices, indices);
	return bow;
}

void Bow::moveUp(float deltaTime) {
	if (this->y < MAX_HEIGHT - 80) {
		this->y += deltaTime * speed;
		resetModelMatrix();
		modelMatrix *= Transform2D::Translate(this->x, this->y);
		this->rotate(mouseX, mouseY);
	}
}

void Bow::moveDown(float deltaTime) {
	if (this->y > 100) {
		this->y -= deltaTime * speed;
		resetModelMatrix();
		modelMatrix *= Transform2D::Translate(this->x, this->y);
		this->rotate(mouseX, mouseY);
	}
}

void Bow::rotate(int mouseX, int mouseY) {
	
	this->mouseY = MAX_HEIGHT - mouseY;
	this->mouseX = mouseX;

	float a = this->mouseX - this->x;
	float b =this->mouseY - this->y;
	float angle = atan(b / a);

	this->resetModelMatrix();

	modelMatrix *= Transform2D::Translate(this->x, this->y);
	
	modelMatrix *= Transform2D::Rotate(-1.35);
	modelMatrix *= Transform2D::Rotate(angle);
	modelMatrix *= Transform2D::Scale(3, 3);

}

void Bow::resetModelMatrix() {
	this->modelMatrix = glm::mat3(1);
}