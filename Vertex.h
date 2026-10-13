#pragma once
#include<glm/vec3.hpp>
#include<glm/vec2.hpp>


class Vertex
{
public:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texCoord;

	Vertex(glm::vec3 position, glm::vec3 color, glm::vec2 texCoord);

	

	Vertex();
};