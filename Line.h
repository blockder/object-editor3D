#pragma once
#include"Mesh.h"

class Line : public Mesh
{
public:
	Vertex p1;
	Vertex p2;

	Line(Texture texture, Vertex p1, Vertex p2);
	Line() = default;
	

	 void updateVBO() override;

	void draw();

	void setColor(glm::vec3 color) override;

	bool hitMesh(Camera& camera);

	void move(glm::vec3 move);


};