#include"Line.h"

GLuint indices3[] =
{
	0,1
};
Shader shaderProgram;
Line::Line(Texture texture, Vertex p1, Vertex p2) : Mesh(texture)
{
	
	Line::p1 = p1;
	Line::p2 = p2;
	shaderProgram = Shader("render.vert", "render.frag");

	updateVBO();

	Mesh::EBO1 = EBO(indices3, sizeof(indices3));
}

void Line::updateVBO()
{
	std::vector<Vertex> vertexArray;
	vertexArray.push_back(p1);
	vertexArray.push_back(p2);

	Mesh::VBO1.Delete();
	Mesh::VBO1 = VBO(vertexArray);
}

void Line::draw() 
{
	updateVBO();
	updateVAO();

	shaderProgram.Active();
	VAO1.bind();
	texture.bind();

	//send texture
	texture.sendToShader(shaderProgram);
	//send select
	glUniform1i(glGetUniformLocation(shaderProgram.id, "select"), false);
	//send transparency
	glUniform1f(glGetUniformLocation(shaderProgram.id, "transparency"), transparency);

	glLineWidth(5.0f);
	glDrawElements(GL_LINES, EBO1.size, GL_UNSIGNED_INT, 0);
	glLineWidth(1.0f);

	VAO1.unBind();
	texture.unBind();
}

void Line::setColor(glm::vec3 color)
{
	p1.color = color;
	p2.color = color;
	return;
}
bool Line::hitMesh(Camera& camera)
{
	return false;
}
void Line::move(glm::vec3 move)
{
	return;
}