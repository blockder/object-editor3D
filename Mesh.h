#pragma once
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"VBO.h"
#include"VAO.h"
#include"EBO.h"
#include"Shader.h"
#include"Texture.h"
#include"Camera.h"


class Mesh
{
public:
	
	VAO VAO1;
	VBO VBO1;
	EBO EBO1;
	Texture texture;

	bool select = false;
	float transparency;
	glm::vec3 color;
	
	Mesh(Texture texture);
	Mesh() = default;

	virtual void draw(Shader& shaderProgram, Camera& camera);

	virtual void updateVBO() = 0;
	
	virtual void setColor(glm::vec3 color) = 0;
	
	virtual bool hitMesh(Camera& camera) = 0; 

	virtual void move(glm::vec3 move) = 0;



protected:
	
	void updateVAO();
	
};