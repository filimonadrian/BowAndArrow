#include "Heart.h"

#include<Core/Engine.h>

Heart::Heart() {

}

Heart::Heart(float x, float y) {
	this->x = x;
	this->y = y;
}

Heart::~Heart() {

}

Mesh* Heart::CreateHeart(std::string name, glm::vec3 color, bool fill) {

	glm::vec3 base = { 0, 0, 0 };

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(base + glm::vec3(3, 5, 0), color),
		VertexFormat(base + glm::vec3(3, 6, 0), color),
		VertexFormat(base + glm::vec3(1, 6, 0), color),
		VertexFormat(base + glm::vec3(0, 5, 0), color),
		VertexFormat(base + glm::vec3(0, 3, 0), color),
		VertexFormat(base + glm::vec3(1, 3, 0), color),
		VertexFormat(base + glm::vec3(1, 2, 0), color),
		VertexFormat(base + glm::vec3(2, 2, 0), color),
		VertexFormat(base + glm::vec3(2, 1, 0), color),
		VertexFormat(base + glm::vec3(3, 0, 0), color),
		VertexFormat(base + glm::vec3(4, 0, 0), color),
		VertexFormat(base + glm::vec3(4, 1, 0), color),
		VertexFormat(base + glm::vec3(5, 1, 0), color),
		VertexFormat(base + glm::vec3(5, 2, 0), color),
		VertexFormat(base + glm::vec3(6, 2, 0), color),
		VertexFormat(base + glm::vec3(6, 3, 0), color),
		VertexFormat(base + glm::vec3(7, 3, 0), color),
		VertexFormat(base + glm::vec3(7, 5, 0), color),
		VertexFormat(base + glm::vec3(6, 5, 0), color),
		VertexFormat(base + glm::vec3(6, 6, 0), color),
		VertexFormat(base + glm::vec3(4, 6, 0), color)

	};

	Mesh* arrow = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1,
											1, 2,
											2, 3,
											3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11,
											11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20};

	if (!fill) {
		arrow->SetDrawMode(GL_LINES);
	}
	else {
		arrow->SetDrawMode(GL_POLYGON);
	}

	arrow->InitFromData(vertices, indices);
	return arrow;
}
