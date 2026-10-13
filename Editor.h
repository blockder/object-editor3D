#pragma once
#include"Mesh3D.h"
class Plane;

class Editor : public Mesh3D
{
public:
	Vertex p1;
	Vertex p2;
	Vertex p3;
	Vertex p4;
	Vertex p5;
	Vertex p6;
	Vertex p7;
	Vertex p8;


	Editor(Texture texture, Vertex p1, Vertex p2, Vertex p3, Vertex p4, Vertex p5, Vertex p6, Vertex p7, Vertex p8);
	Editor() = default;
	

	void updateVBO() override;

	bool hitMesh(Camera& camera) override;

	void setColor(glm::vec3 color) override;

	glm::vec3 whereHit(Camera& camera) override;

	void scale(float value);
	
	
};