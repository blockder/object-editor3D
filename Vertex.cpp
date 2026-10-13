#include"Vertex.h"

Vertex::Vertex(glm::vec3 position, glm::vec3 color, glm::vec2 texCoord)
{
	Vertex::position = position;
	Vertex::color = color;
	Vertex::texCoord = texCoord;
}



Vertex::Vertex()
{

}

