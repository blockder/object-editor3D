#pragma once
#include"Mesh.h"

class Tile : public Mesh
{
public:
	Vertex p1;
	Vertex p2;
	Vertex p3;
	Vertex p4;

	Tile(Texture texture, Vertex p1, Vertex p2, Vertex p3, Vertex p4);
	Tile() = default;

	void updateVBO() override;

	bool hitMesh(Camera& camera) override;

	void setColor(glm::vec3 color) override;

	void move(glm::vec3 move) override;
};