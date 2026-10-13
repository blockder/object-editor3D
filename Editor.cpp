#include"Editor.h"
#include"Plane.h"
#include"Math.h"

GLuint Indices2[] =
{
	0,1,2,
	2,3,0,
	1,5,6,
	6,2,1,
	4,0,3,
	3,7,4,
	5,4,7,
	7,6,5,
	3,2,6,
	6,7,3,
	4,5,1,
	1,0,4
	
};

Editor::Editor(Texture texture, Vertex p1, Vertex p2, Vertex p3, Vertex p4, Vertex p5, Vertex p6, Vertex p7, Vertex p8) : Mesh3D(texture)
{

	Editor::p1 = p1;
	Editor::p2 = p2;
	Editor::p3 = p3;
	Editor::p4 = p4;
	Editor::p5 = p5;
	Editor::p6 = p6;
	Editor::p7 = p7;
	Editor::p8 = p8;

	updateVBO();

	Mesh3D::EBO1 = EBO(Indices2, sizeof(Indices2));

}

void Editor::updateVBO()
{
	std::vector<Vertex> vertexArray;
	vertexArray.push_back(p1);
	vertexArray.push_back(p2);
	vertexArray.push_back(p3);
	vertexArray.push_back(p4);
	vertexArray.push_back(p5);
	vertexArray.push_back(p6);
	vertexArray.push_back(p7);
	vertexArray.push_back(p8);

	Mesh3D::VBO1.Delete();
	Mesh3D::VBO1 = VBO(vertexArray);
	
}


void Editor::setColor(glm::vec3 color)
{
	this->color = color;
	p1.color = color;
	p2.color = color;
	p3.color = color;
	p4.color = color;
	p5.color = color;
	p6.color = color;
	p7.color = color;
	p8.color = color;

	updateVBO();
}


bool Editor::hitMesh(Camera& camera)
{
	glm::vec3 rayDirection = camera.generateRay(camera.mouse);
	std::vector<Vertex> points;
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	points.push_back(p4);
	points.push_back(p5);
	points.push_back(p6);
	points.push_back(p7);
	points.push_back(p8);
	for (int i = 0; i < sizeof(Indices2) / sizeof(GLuint); i += 3)
	{
		glm::vec3 rp1 = modelToWorldSpace(points[Indices2[i]].position);
		glm::vec3 rp2 = modelToWorldSpace(points[Indices2[i + 1]].position);
		glm::vec3 rp3 = modelToWorldSpace(points[Indices2[i + 2]].position);
		if (Math::hitTriangle(camera.loc, rayDirection, rp1, rp2, rp3))
		{
			return true;
		}
	
	}
	return false;
}

void Editor::scale(float value)
{
	p1.position *= value;
	p2.position *= value;
	p3.position *= value;
	p4.position *= value;
	p5.position *= value;
	p6.position *= value;
	p7.position *= value;
	p8.position *= value;
	return;
}

glm::vec3 Editor::whereHit(Camera& camera)
{
	return glm::vec3(-99, -99, -99);
}
