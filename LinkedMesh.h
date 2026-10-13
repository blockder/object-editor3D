#pragma once
#include<glm/glm.hpp>
#include<vector>
#include"Camera.h"
class Line;
class Arrow;
class Mesh3D;

class LinkedMesh
{
public:

	Line* rotator;
	Arrow* right;
	Arrow* up;
	Arrow* backward;

	bool showArrows;
	const char* editMode;
	glm::vec3 center;

	std::vector<Mesh3D*> list;

	LinkedMesh();

	void addMesh(Mesh3D* mesh);
	void remove(int index);
	void erase();
	int size();

	void Edit(GLFWwindow* window, Camera& camera);

	bool selectArrows(GLFWwindow* window, Camera& camera);

	void draw(Shader& shaderProgram, Camera& camera);
private:
	void updateCenter();
	void updateArrows();
	void move(glm::vec3 step);
	void rotate(float angle, glm::vec3 axis);

	glm::vec3 findRotation(Camera& camera, glm::vec2 currentMouse, glm::vec3 axis);
	glm::vec3 calulateStep(Camera& camera, glm::vec2 currentMouse, glm::vec3 moveDirection);
	float roundAngle(int roundDegree, glm::vec3 axis, Camera& camera); 
	float getAngle(Camera& camera, glm::vec3 axis, glm::vec2 mouse);
	glm::vec3 normalRot = glm::vec3(0);
};