#include"Mesh.h"
#include"Line.h"
#include"Arrow.h"
#include"Editor.h"
#include"Math.h"
#include <glm/gtx/vector_angle.hpp>



Mesh::Mesh(Texture texture)
{
	Mesh::texture = texture;
	Mesh::transparency = 1.0f;
	Mesh::color = glm::vec3(1, 1, 1);
	Mesh::VAO1 = VAO();
	
	//EBO and VBO will be set in the child class
	
}


void Mesh::updateVAO()
{

	VAO1.setLayer(VBO1, EBO1, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);					//pos
	VAO1.setLayer(VBO1, EBO1, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));	//color
	VAO1.setLayer(VBO1, EBO1, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));	//texCoord
}

void Mesh::draw(Shader& shaderProgram, Camera& camera)
{
	updateVAO();
	
	shaderProgram.Active();
	VAO1.bind();
	texture.bind();

	//send texture
	texture.sendToShader(shaderProgram);
	//send select
	glUniform1i(glGetUniformLocation(shaderProgram.id, "select"), select ? 1 : 0);
	//send transparency
	glUniform1f(glGetUniformLocation(shaderProgram.id, "transparency"), transparency);

	glDrawElements(GL_TRIANGLES, EBO1.size, GL_UNSIGNED_INT, 0);

	VAO1.unBind();
	texture.unBind();

} 



