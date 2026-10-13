#pragma once
#include"Mesh3D.h"
#include"Editor.h"

class Cube : public Mesh3D
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


	Cube(Texture texture, Vertex p1, Vertex p2, Vertex p3, Vertex p4, Vertex p5, Vertex p6, Vertex p7, Vertex p8);
	Cube(const Cube& other);
	Cube() = default;

	void updateVBO() override;

	void draw(Shader& shaderProgram, Camera& camera) override;

	bool hitMesh(Camera& camera) override;

	glm::vec3 whereHit(Camera& camera) override;

	void setColor(glm::vec3 color) override;
	
	void scale(float value);

};