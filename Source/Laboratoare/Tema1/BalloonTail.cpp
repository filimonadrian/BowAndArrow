#include "BalloonTail.h"

#include<Core/Engine.h>

BalloonTail::BalloonTail() {

}

BalloonTail::BalloonTail(float x, float y) {
	this->x = x;
	this->y = y;
}

BalloonTail::~BalloonTail() {

}

Mesh* BalloonTail::CreateBalloonTail(std::string name, glm::vec3 color) {

	glm::vec3 base = { 0, 0, 0 };

	std::vector<VertexFormat> vertices =
	{
		// 0, 1, 2(triangle)
		VertexFormat(base, color),
		VertexFormat(glm::vec3(size, size, 0), color),
		VertexFormat(glm::vec3(2 * size, 0, 0), color),
		// 3, 4, 5 -- first line
		VertexFormat(glm::vec3(0.5f, 0, 0), color),
		VertexFormat(glm::vec3(0.4f, -size/2, 0), color),
		VertexFormat(glm::vec3(0, -size, 0), color),
		// 6, 7
		VertexFormat(glm::vec3(size + 0.01f, -2 * size, 0), color),
		VertexFormat(glm::vec3(size, -2 * size, 0), color),
		// 8, 9
		VertexFormat(glm::vec3(0 + 0.01f, -3 * size, 0), color),
		VertexFormat(glm::vec3(0, -3 * size, 0), color),
		// 10, 11
		VertexFormat(glm::vec3(size + 0.01f, -4 * size, 0), color),
		VertexFormat(glm::vec3(size, -4 * size, 0), color),
	};

	Mesh* arrow = new Mesh(name);

	std::vector<unsigned short> indices = { 0, 1, 2,
											3, 4, 5,
											5, 6, 7,
											7, 8, 9,
											9, 10, 11 
											};

	arrow->SetDrawMode(GL_TRIANGLES);

	arrow->InitFromData(vertices, indices);
	return arrow;
}
