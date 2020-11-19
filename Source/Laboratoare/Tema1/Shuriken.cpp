#include "Shuriken.h"

Shuriken::Shuriken() {
}

Shuriken::~Shuriken() {
}

Shuriken::Shuriken(float x, float y) {
	this->x = x;
	this->y = y;
}

Mesh* Shuriken::CreateShuriken(std::string name, float scale, glm::vec3 base, float length, glm::vec3 color, bool fill)
{

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(base, color),
		VertexFormat(base + glm::vec3(length, 0, 0), color),
		VertexFormat(base + glm::vec3(-length, 0, 0), color),
		VertexFormat(base + glm::vec3(0, length, 0), color),
		VertexFormat(base + glm::vec3(0, -length, 0), color),
		VertexFormat(base + glm::vec3(length, length, 0), color),
		VertexFormat(base + glm::vec3(-length, -length, 0), color),
		VertexFormat(base + glm::vec3(-length, length, 0), color),
		VertexFormat(base + glm::vec3(length, -length, 0), color),

	};

	Mesh* shuriken = new Mesh(name);
	std::vector<unsigned short> indices = {
											0, 3, 7, 
											0, 5, 1,
											0, 8, 4,
											0, 6, 2};
	
	shuriken->SetDrawMode(GL_TRIANGLES);

	shuriken->InitFromData(vertices, indices);
	return shuriken;
}

void Shuriken::reset() {
	this->x = 1300;
	this->y = 0;
	rotation = 1.0f;
	speed = 100;
	this->ready = true;
	this->hit = false;
}

void Shuriken::generateShuriken() {
	this->x = generateFloat(1250, 1350);
	this->y = generateFloat(10, 650);
	this->ready = false;
}

void Shuriken::move(glm::mat3 *modelMatrix, float deltaTimeSeconds, float speed) {
	if (this->ready) {
		return;
	}
	if (this->x < -20 || (this->hit && this->y < -20)) {
		this->reset();
	}

	if (!this->hit) {
		*modelMatrix *= Transform2D::Translate(x, y);
		*modelMatrix *= Transform2D::Translate(0, 0);
		rotation += deltaTimeSeconds * speed/30;
		*modelMatrix *= Transform2D::Rotate(rotation);
		*modelMatrix *= Transform2D::Translate(0, 0);
		this->x -= deltaTimeSeconds * speed;
	}
	else {
		*modelMatrix *= Transform2D::Translate(x, y);
		this->y -= deltaTimeSeconds * speed;
	}
}