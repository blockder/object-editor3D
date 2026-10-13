#pragma once
#include"Mesh.h"

class Line;
class Arrow;
class Editor;

class Mesh3D : public Mesh 
{
public:
	//parameters
	const char* name;
	const char* editMode = "false";
	const char* editModeMode = "move";

	glm::mat4 rotation;
	glm::mat4 movement;
	glm::mat4 model;

	Editor* leftEditor;
	Editor* rightEditor;
	Editor* forwardEditor;
	Editor* backwardEditor;
	Editor* upwardEditor;
	Editor* downwardEditor;
	Line* rotator;


	//functions
	Mesh3D(Texture texture);
	Mesh3D(const Mesh3D& other);
	Mesh3D() = default;

	virtual void draw(Shader& shaderProgram, Camera& camera) override;
	void draw(Shader& shaderProgram, Camera& camera, Texture& shadowMap, Camera& lightView, bool applyShadow);

	virtual glm::vec3 whereHit(Camera& camera) = 0;
	
	bool selectEditors(GLFWwindow* window, Camera& camera);

	void Edit(GLFWwindow* window, Camera& camera);

	glm::vec3 modelToWorldSpace(glm::vec3 point);

	void rotate(float angle, glm::vec3 axis);

	void move(glm::vec3 move) override;

protected:
	glm::vec3 findRotation(Camera& camera, glm::vec2 mouse, glm::vec3 axis);
	glm::vec3 calulateStep(Camera& camera, glm::vec2 currentMouse, glm::vec3 origin, glm::mat4 rotation, glm::vec3 moveDirection);
	void updateEditorLocation();
	
	
};