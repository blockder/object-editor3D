#include"Tile.h"

GLuint Indices4[] =
{
	0,1,2,
	2,3,0
};
Tile::Tile(Texture texture, Vertex p1, Vertex p2, Vertex p3, Vertex p4) : Mesh(texture)
{

	Tile::p1 = p1;
	Tile::p2 = p2;
	Tile::p3 = p3;
	Tile::p4 = p4;

	Mesh::VBO1.Delete();
	Mesh::EBO1 = EBO(Indices4, sizeof(Indices4));

	updateVBO();
}

void Tile::updateVBO()
{
	std::vector<Vertex> vertexArray;
	vertexArray.push_back(p1);
	vertexArray.push_back(p2);
	vertexArray.push_back(p3);
	vertexArray.push_back(p4);

	Mesh::VBO1.Delete();
	Mesh::VBO1 = VBO(vertexArray); 
}

void Tile::setColor(glm::vec3 color)
{
	p1.color = color;
	p2.color = color;
	p3.color = color;
	p4.color = color;
	updateVBO();
}

bool Tile::hitMesh(Camera& camera)
{
	glm::vec2 currentMouse(camera.mouse.x / (camera.screenWidth / 2), -camera.mouse.y / (camera.screenHeight / 2));

	return currentMouse.x > p3.position.x && currentMouse.x < p1.position.x && currentMouse.y < p3.position.y && currentMouse.y > p2.position.y;
	
}

void Tile::move(glm::vec3 move)
{
	p1.position += move;
	p2.position += move;
	p3.position += move;
	p4.position += move;
	updateVBO(); 
}