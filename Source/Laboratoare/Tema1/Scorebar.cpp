#include "Scorebar.h"

#include<Core/Engine.h>

Scorebar::Scorebar() {

}

Scorebar::Scorebar(float x, float y) {
	this->x = x;
	this->y = y;
}

Scorebar::~Scorebar() {

}

Mesh* Scorebar::CreateScorebar(std::string name, glm::vec3 color, bool fill) {

	glm::vec3 base = { 0, 0, 0 };

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(base, color),
		VertexFormat(base + glm::vec3(length, 0, 0), color),
		VertexFormat(base + glm::vec3(length, width, 0), color),
		VertexFormat(base + glm::vec3(0, width, 0), color),

	};

	Mesh* arrow = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 
											1, 2, 
											2, 3,
											0, 3 };

	if (!fill) {
		arrow->SetDrawMode(GL_LINES);
	}
	else {
		arrow->SetDrawMode(GL_POLYGON);
	}

	arrow->InitFromData(vertices, indices);
	return arrow;
}
