#pragma once
#include"Mesh3D.h"
#include"Editor.h"
#include"Line.h"
#include"Arrow.h"


class Plane : public Mesh3D
{
public:
	Vertex p1;
	Vertex p2;
	Vertex p3;
	Vertex p4;


	Plane(Texture texture, Vertex p1, Vertex p2, Vertex p3, Vertex p4);
	Plane(const Plane& other);
	Plane() = default;

	void updateVBO() override;

	void draw(Shader& shaderProgram, Camera& camera) override;

	bool hitMesh(Camera& camera) override; 

	glm::vec3 whereHit(Camera& camera) override;

	void setColor(glm::vec3 color) override;


private:
	

};