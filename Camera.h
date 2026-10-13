#pragma once
#include<glm/glm.hpp>
#include"Shader.h"
#include<GLFW/glfw3.h>
#include"FBO.h"
#include<vector>
class Mesh3D;
class Camera
{
public:
	bool active;
	float screenWidth;
	float screenHeight;
	glm::vec3 loc;
	glm::vec3 direction;
	glm::vec3 up;
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	glm::vec2 mouse = glm::vec2(0.0, 0.0);

	Camera(glm::vec3 loc, glm::vec3 direction, glm::vec3 up, float width, float height);
	Camera() = default;

	void Inputs(GLFWwindow* window);

	void sendToShader(Shader& shaderProgram, const char* name);

	glm::vec2 projectPoint(glm::vec3 point);

	glm::vec3 generateRay(glm::vec2 mouse);

	bool firstClick(GLFWwindow* window); 

	void setClickBefore(bool state);

private:
	bool clickBefore = false;
	float FOV = 90;
	float nearPlane = 0.1;
	float farPlane = 100.0;
	float sesitivity = 0.1f;
	float speed = 0.02f;
};