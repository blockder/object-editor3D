#include"Plane.h"
#include"Line.h"
#include <glm/gtx/vector_angle.hpp>
#include"Math.h"

//editors
Vertex e1(glm::vec3(-0.05f, -0.05f, -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex e2(glm::vec3(0.05f, -0.05f, -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex e3(glm::vec3(0.05f, 0.05f, -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex e4(glm::vec3(-0.05f, 0.05f, -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex e5(glm::vec3(-0.05f, -0.05f, 0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex e6(glm::vec3(0.05f, -0.05f, 0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex e7(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex e8(glm::vec3(-0.05f, 0.05f, 0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
//arrows
Vertex a1(glm::vec3(-0.05f, -0.05f, -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex a2(glm::vec3(-0.05f, 0.05f, 0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex a3(glm::vec3(-0.25f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex a4(glm::vec3(-0.05f, 0.05f, 0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex a5(glm::vec3(0.05f, 0.05f, -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex a6(glm::vec3(0.0f, 0.25f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex a7(glm::vec3(-0.05f, -0.05f, -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex a8(glm::vec3(0.05f, 0.05f, -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex a9(glm::vec3(0.0f, 0.0f, -0.25f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));

GLuint Indices[] =
{
	1,0,3,
	3,2,1
};


Plane::Plane(Texture texture, Vertex p1, Vertex p2, Vertex p3, Vertex p4) : Mesh3D(texture)
{
	this->name = "plane";
	Texture blank("blank.png", 2);
	Mesh3D::leftEditor = new Editor(blank, e1, e2, e3, e4, e5, e6, e7, e8); leftEditor->scale(0.5f);
	Mesh3D::rightEditor = new Editor(blank, e1, e2, e3, e4, e5, e6, e7, e8); rightEditor->scale(0.5f);
	Mesh3D::forwardEditor = new Editor(blank, e1, e2, e3, e4, e5, e6, e7, e8);  forwardEditor->scale(0.5f);
	Mesh3D::backwardEditor = new Editor(blank, e1, e2, e3, e4, e5, e6, e7, e8); backwardEditor->scale(0.5f);
	Mesh3D::upwardEditor = new Editor(blank, e1, e2, e3, e4, e5, e6, e7, e8);  upwardEditor->scale(0.5f);
	Mesh3D::downwardEditor = new Editor(blank, e1, e2, e3, e4, e5, e6, e7, e8); downwardEditor->scale(0.5f);
	
	Mesh3D::rotator = new Line(blank, e1, e2);
	
	
	Plane::p1 = p1;
	Plane::p2 = p2;
	Plane::p3 = p3;
	Plane::p4 = p4;

	updateVBO();

	Mesh3D::EBO1 = EBO(Indices, sizeof(Indices));
}

Plane::Plane(const Plane& other) : Mesh3D(other)
{
	this->name = "plane";
	editMode = "false";
	Texture blank("blank.png", 2);
	Mesh3D::leftEditor = new Editor(blank, e1, e2, e3, e4, e5, e6, e7, e8); leftEditor->scale(0.5f);
	Mesh3D::rightEditor = new Editor(blank, e1, e2, e3, e4, e5, e6, e7, e8); rightEditor->scale(0.5f);
	Mesh3D::forwardEditor = new Editor(blank, e1, e2, e3, e4, e5, e6, e7, e8);  forwardEditor->scale(0.5f);
	Mesh3D::backwardEditor = new Editor(blank, e1, e2, e3, e4, e5, e6, e7, e8); backwardEditor->scale(0.5f);
	Mesh3D::upwardEditor = new Editor(blank, e1, e2, e3, e4, e5, e6, e7, e8);  upwardEditor->scale(0.5f);
	Mesh3D::downwardEditor = new Editor(blank, e1, e2, e3, e4, e5, e6, e7, e8);  downwardEditor->scale(0.5f);

	Mesh3D::rotator = new Line(blank, e1, e2);


	Plane::p1 = other.p1;
	Plane::p2 = other.p2;
	Plane::p3 = other.p3;
	Plane::p4 = other.p4;

	
	updateVBO();

	Mesh3D::EBO1 = EBO(Indices, sizeof(Indices));
}





void Plane::updateVBO() 
{
	std::vector<Vertex> vertexArray;
	vertexArray.push_back(p1);
	vertexArray.push_back(p2);
	vertexArray.push_back(p3);
	vertexArray.push_back(p4);

	Mesh3D::VBO1.Delete();
	Mesh3D::VBO1 = VBO(vertexArray);
}

void Plane::draw(Shader& shaderProgram, Camera& camera)
{
	Mesh3D::draw(shaderProgram, camera);

	if (editMode == "rotationX" || editMode == "rotationY" || editMode == "rotationZ")
	{
		rotator->draw(); 
	}
	
	if (select)
	{
		if (editModeMode == "edit")
		{
			leftEditor->draw(shaderProgram, camera);
			rightEditor->draw(shaderProgram, camera);
			forwardEditor->draw(shaderProgram, camera);
			backwardEditor->draw(shaderProgram, camera);
		}
		
	}
}



bool Plane::hitMesh(Camera& camera)
{
	glm::vec3 rayDirection = camera.generateRay(camera.mouse);
	std::vector<Vertex> points;
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	points.push_back(p4);
	for (int i = 0; i < sizeof(Indices) / sizeof(GLuint); i+=3)
	{
		glm::vec3 rp1 = modelToWorldSpace(points[Indices[i]].position);
		glm::vec3 rp2 = modelToWorldSpace(points[Indices[i+1]].position);
		glm::vec3 rp3 = modelToWorldSpace(points[Indices[i+2]].position);

		if (Math::hitTriangle(camera.loc, rayDirection, rp1, rp2, rp3))
		{
			return true;
		}
	}
	return false;
}
glm::vec3 Plane::whereHit(Camera& camera)
{
	glm::vec3 rayDirection = camera.generateRay(camera.mouse);
	std::vector<Vertex> points;
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	points.push_back(p4);
	
	glm::vec3 hitLoc(-99, -99, -99);
	for (int i = 0; i < sizeof(Indices) / sizeof(GLuint); i += 3)
	{
		glm::vec3 rp1 = modelToWorldSpace(points[Indices[i]].position);
		glm::vec3 rp2 = modelToWorldSpace(points[Indices[i + 1]].position);
		glm::vec3 rp3 = modelToWorldSpace(points[Indices[i + 2]].position);
		if (Math::hitTriangle(camera.loc, rayDirection, rp1, rp2, rp3))
		{
			glm::vec3 newHitLoc = Math::planeIntersetion(glm::cross(rp1 - rp3, rp2 - rp3), rp1, rayDirection, camera.loc);
			if (hitLoc.x == -99 || glm::distance(newHitLoc, camera.loc) < glm::distance(hitLoc, camera.loc))
				hitLoc = newHitLoc;

		}

	}
	return hitLoc;

}
void Plane::setColor(glm::vec3 color) 
{
	Mesh3D::color = color;
	p1.color = color;
	p2.color = color;
	p3.color = color;
	p4.color = color;
	updateVBO();
}