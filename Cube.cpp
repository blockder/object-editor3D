#include"Cube.h"
#include"Line.h"
#include"Math.h"
#include"Arrow.h"
#include"Editor.h"
#include <glm/gtx/vector_angle.hpp>
GLuint Indices5[] =
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

//editors
Vertex u1(glm::vec3(-0.05f, -0.05f, -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex u2(glm::vec3(0.05f, -0.05f, -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex u3(glm::vec3(0.05f, 0.05f, -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex u4(glm::vec3(-0.05f, 0.05f, -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex u5(glm::vec3(-0.05f, -0.05f, 0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex u6(glm::vec3(0.05f, -0.05f, 0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex u7(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex u8(glm::vec3(-0.05f, 0.05f, 0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
//arrows
Vertex g1(glm::vec3(-0.05f, -0.05f, -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex g2(glm::vec3(-0.05f, 0.05f, 0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex g3(glm::vec3(-0.25f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex g4(glm::vec3(-0.05f, 0.05f, 0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex g5(glm::vec3(0.05f, 0.05f, -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex g6(glm::vec3(0.0f, 0.25f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex g7(glm::vec3(-0.05f, -0.05f, -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex g8(glm::vec3(0.05f, 0.05f, -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
Vertex g9(glm::vec3(0.0f, 0.0f, -0.25f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));


Cube::Cube(Texture texture, Vertex p1, Vertex p2, Vertex p3, Vertex p4, Vertex p5, Vertex p6, Vertex p7, Vertex p8) : Mesh3D(texture)
{
	this->name = "cube";
	Texture blank("blank.png", 2);
	

	Mesh3D::rotator = new Line(blank, u1, u2);
	Mesh3D::leftEditor = new Editor(blank, u1, u2, u3, u4, u5, u6, u7, u8); leftEditor->scale(0.5f);
	Mesh3D::rightEditor = new Editor(blank, u1, u2, u3, u4, u5, u6, u7, u8); rightEditor->scale(0.5f);
	Mesh3D::forwardEditor = new Editor(blank, u1, u2, u3, u4, u5, u6, u7, u8);  forwardEditor->scale(0.5f);
	Mesh3D::backwardEditor = new Editor(blank, u1, u2, u3, u4, u5, u6, u7, u8); backwardEditor->scale(0.5f);
	Mesh3D::upwardEditor = new Editor(blank, u1, u2, u3, u4, u5, u6, u7, u8);  upwardEditor->scale(0.5f);
	Mesh3D::downwardEditor = new Editor(blank, u1, u2, u3, u4, u5, u6, u7, u8);  downwardEditor->scale(0.5f);

	Mesh3D::rotator = new Line(blank, u1, u2);
	

	Cube::p1 = p1;
	Cube::p2 = p2;
	Cube::p3 = p3;
	Cube::p4 = p4;
	Cube::p5 = p5;
	Cube::p6 = p6;
	Cube::p7 = p7;
	Cube::p8 = p8;

	updateVBO();

	this->EBO1 = EBO(Indices5, sizeof(Indices5));
}
Cube::Cube(const Cube& other) : Mesh3D(other)
{
	this->name = "cube";
	Texture blank("blank.png", 2);


	Mesh3D::rotator = new Line(blank, u1, u2);
	Mesh3D::leftEditor = new Editor(blank, u1, u2, u3, u4, u5, u6, u7, u8); leftEditor->scale(0.5f);
	Mesh3D::rightEditor = new Editor(blank, u1, u2, u3, u4, u5, u6, u7, u8); rightEditor->scale(0.5f);
	Mesh3D::forwardEditor = new Editor(blank, u1, u2, u3, u4, u5, u6, u7, u8); forwardEditor->scale(0.5f);
	Mesh3D::backwardEditor = new Editor(blank, u1, u2, u3, u4, u5, u6, u7, u8); backwardEditor->scale(0.5f);
	Mesh3D::upwardEditor = new Editor(blank, u1, u2, u3, u4, u5, u6, u7, u8);  upwardEditor->scale(0.5f);
	Mesh3D::downwardEditor = new Editor(blank, u1, u2, u3, u4, u5, u6, u7, u8);  downwardEditor->scale(0.5f);

	Mesh3D::rotator = new Line(blank, u1, u2);
	

	this->p1 = other.p1;
	this->p2 = other.p2;
	this->p3 = other.p3;
	this->p4 = other.p4;
	this->p5 = other.p5;
	this->p6 = other.p6;
	this->p7 = other.p7;
	this->p8 = other.p8;

	updateVBO();

	this->EBO1 = EBO(Indices5, sizeof(Indices5));
}

void Cube::updateVBO()
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

void Cube::setColor(glm::vec3 color)
{
	Mesh3D::color = color;
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

bool Cube::hitMesh(Camera& camera)
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
	for (int i = 0; i < sizeof(Indices5) / sizeof(GLuint); i += 3)
	{
		glm::vec3 rp1 = modelToWorldSpace(points[Indices5[i]].position);
		glm::vec3 rp2 = modelToWorldSpace(points[Indices5[i + 1]].position);
		glm::vec3 rp3 = modelToWorldSpace(points[Indices5[i + 2]].position);
		if (Math::hitTriangle(camera.loc, rayDirection, rp1, rp2, rp3))
		{
			return true;
		}

	}
	return false;
}
glm::vec3 Cube::whereHit(Camera& camera)
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
	glm::vec3 hitLoc(-99, -99, -99);
	for (int i = 0; i < sizeof(Indices5) / sizeof(GLuint); i += 3)
	{
		glm::vec3 rp1 = modelToWorldSpace(points[Indices5[i]].position);
		glm::vec3 rp2 = modelToWorldSpace(points[Indices5[i + 1]].position);
		glm::vec3 rp3 = modelToWorldSpace(points[Indices5[i + 2]].position);
		if (Math::hitTriangle(camera.loc, rayDirection, rp1, rp2, rp3))
		{
			glm::vec3 newHitLoc = Math::planeIntersetion(glm::cross(rp1- rp3, rp2-rp3), rp1, rayDirection, camera.loc);
			if (hitLoc.x == -99 || glm::distance(newHitLoc, camera.loc) < glm::distance(hitLoc, camera.loc))
					hitLoc = newHitLoc;
			
		}

	}
	return hitLoc;
	
}
void Cube::scale(float value) 
{
	p1.position *= value;
	p2.position *= value;
	p3.position *= value;
	p4.position *= value;
	p5.position *= value;
	p6.position *= value;
	p7.position *= value;
	p8.position *= value;
	updateVBO();
	return;
}

void Cube::draw(Shader& shaderProgram, Camera& camera)
{
	Mesh3D::draw(shaderProgram, camera);

	if (editMode == "rotationX" || editMode == "rotationY" || editMode == "rotationZ")
	{
		rotator->draw();
	}

	if (select)
	{
		glDisable(GL_DEPTH_TEST);
		if (editModeMode == "edit")
		{
			leftEditor->draw(shaderProgram, camera);
			rightEditor->draw(shaderProgram, camera);
			forwardEditor->draw(shaderProgram, camera);
			backwardEditor->draw(shaderProgram, camera);
			upwardEditor->draw(shaderProgram, camera);
			downwardEditor->draw(shaderProgram, camera);
		}
		
		glEnable(GL_DEPTH_TEST);
	}
}



