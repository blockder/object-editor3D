#pragma once
#include"Mesh3D.h"


class Arrow : public Mesh3D
{
public:
	Vertex p1;
	Vertex p2;
	Vertex p3;


	Arrow(Texture texture, Vertex p1, Vertex p2, Vertex p3);
	Arrow() = default;

	void updateVBO() override;

	bool hitMesh(Camera& camera) override;

	void setColor(glm::vec3 color) override;

	glm::vec3 whereHit(Camera& camera);

};