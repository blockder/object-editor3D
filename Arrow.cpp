#include"Arrow.h"
#include"Math.h"

GLuint Indices3[] =
{
	0,1,2,
};
Arrow::Arrow(Texture texture, Vertex p1, Vertex p2, Vertex p3) : Mesh3D(texture)
{
	Arrow::p1 = p1;
	Arrow::p2 = p2;
	Arrow::p3 = p3;

	updateVBO();

	Mesh3D::EBO1 = EBO(Indices3, sizeof(Indices3));
}

void Arrow::updateVBO()
{
	std::vector<Vertex> vertexArray;
	vertexArray.push_back(p1);
	vertexArray.push_back(p2);
	vertexArray.push_back(p3);

	Mesh3D::VBO1.Delete();
	Mesh3D::VBO1 = VBO(vertexArray);
}


bool Arrow::hitMesh(Camera& camera) 
{
	glm::vec3 rayDirection = camera.generateRay(camera.mouse);
	glm::vec3 rp1 = modelToWorldSpace(p1.position);
	glm::vec3 rp2 = modelToWorldSpace(p2.position);
	glm::vec3 rp3 = modelToWorldSpace(p3.position);
	return Math::hitTriangle(camera.loc, rayDirection, rp1, rp2, rp3);
}

void Arrow::setColor(glm::vec3 color)
{
	p1.color = color; 
	p2.color = color;
	p3.color = color;

	updateVBO();
}
glm::vec3 Arrow::whereHit(Camera& camera)
{
	return glm::vec3(-99, -99, -99);
}
