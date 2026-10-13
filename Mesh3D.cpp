#include"Mesh3D.h"
#include"Line.h"
#include"Arrow.h"
#include"Editor.h"
#include"Math.h"
#include <glm/gtx/vector_angle.hpp>

Mesh3D::Mesh3D(Texture texture) : Mesh(texture)
{
	this->name = "mesh3D";

	this->movement = glm::mat4(1.0f);
	this->rotation = glm::mat4(1.0f);
	this->model = glm::mat4(1.0f);
}
Mesh3D::Mesh3D(const Mesh3D& other) : Mesh(other.texture)
{
	name = other.name;
	select = false;
	
	this->movement = other.movement;
	this->rotation = other.rotation;
	this->model = other.model;
}
void Mesh3D::draw(Shader& shaderProgram, Camera& camera)
{
	updateVAO();

	shaderProgram.Active();
	VAO1.bind();
	texture.bind();

	//send texture
	texture.sendToShader(shaderProgram);
	//send camera matrix
	camera.sendToShader(shaderProgram, "cameraMatrix");
	//send camera loc
	glUniform3fv(glGetUniformLocation(shaderProgram.id, "camLoc"), 1, glm::value_ptr(camera.loc));
	//send select
	glUniform1i(glGetUniformLocation(shaderProgram.id, "select"), select ? 1 : 0);
	//send rotation matrix
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.id, "rotation"), 1, GL_FALSE, glm::value_ptr(rotation));
	//send movement matrix
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.id, "movement"), 1, GL_FALSE, glm::value_ptr(movement));
	//send movement matrix
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.id, "model"), 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, EBO1.size, GL_UNSIGNED_INT, 0);

	VAO1.unBind();
	texture.unBind();
}
void Mesh3D::draw(Shader& shaderProgram, Camera& camera, Texture& shadowMap, Camera& lightView, bool applyShadow)
{
	shaderProgram.Active();
	shadowMap.bind();
	//send cameraMatrix
	lightView.sendToShader(shaderProgram, "lightView");
	//send shadowMap
	glUniform1i(glGetUniformLocation(shaderProgram.id, "shadowMap"), shadowMap.slot);
	//send lightPos
	glUniform3f(glGetUniformLocation(shaderProgram.id, "lightPos"), 0.0f, 10.0f, 0.0f);
	//send applyShadow
	glUniform1i(glGetUniformLocation(shaderProgram.id, "applyShadow"), applyShadow ? 1 : 0);
	draw(shaderProgram, camera);
}
glm::vec3 Mesh3D::modelToWorldSpace(glm::vec3 point)
{
	glm::vec4 temp = movement * rotation * model * glm::vec4(point, 1.0f);
	return glm::vec3(temp.x, temp.y, temp.z);
}
void Mesh3D::Edit(GLFWwindow* window, Camera& camera)
{
	updateEditorLocation();

	//always have to hold house buttom to edit
	if (!camera.firstClick(window))
	{
		editMode = "false";
		camera.active = true;
		return;
	}
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	glm::vec3 normal(0.0f, 1.0f, 0.0f);
	glm::vec3 origin = modelToWorldSpace(glm::vec3(0, 0, 0));
	glm::vec2 center = camera.projectPoint(origin);
	//in pixels
	glm::vec2 currentPos(mouseX - camera.screenWidth / 2, mouseY - camera.screenHeight / 2);
	//screen coordinates
	glm::vec2 currentMouse(currentPos.x / (camera.screenWidth / 2), -currentPos.y / (camera.screenHeight / 2));


	rotator->p1.position = glm::vec3(currentMouse, 0.0f);
	rotator->p2.position = glm::vec3(center, 0);


	//edit
	if (editMode == "right")
	{
		glm::vec3 step = calulateStep(camera, currentPos, origin, rotation, glm::vec3(1, 0, 0));
		movement = glm::translate(movement, glm::vec3(rotation * glm::vec4(step, 1.0f)));
		model[0] -= glm::vec4(step * 2.0f, 0);
	}
	if (editMode == "left")
	{
		glm::vec3 step = calulateStep(camera, currentPos, origin, rotation, glm::vec3(1, 0, 0));
		movement = glm::translate(movement, glm::vec3(rotation * glm::vec4(step, 1.0f)));
		model[0] += glm::vec4(step * 2.0f, 0);
	}
	if (editMode == "forward")
	{
		glm::vec3 step = calulateStep(camera, currentPos, origin, rotation, glm::vec3(0, 0, 1));
		movement = glm::translate(movement, glm::vec3(rotation * glm::vec4(step, 1.0f)));
		model[2] += glm::vec4(step * 2.0f, 0);
	}
	if (editMode == "backward")
	{
		glm::vec3 step = calulateStep(camera, currentPos, origin, rotation, glm::vec3(0, 0, 1));
		movement = glm::translate(movement, glm::vec3(rotation * glm::vec4(step, 1.0f)));
		model[2] -= glm::vec4(step * 2.0f, 0);
	}
	if (editMode == "upward")
	{
		glm::vec3 step = calulateStep(camera, currentPos, origin, rotation, glm::vec3(0, 1, 0));
		movement = glm::translate(movement, glm::vec3(rotation * glm::vec4(step, 1.0f)));
		model[1] += glm::vec4(step * 2.0f, 0);
	}
	if (editMode == "downward")
	{
		glm::vec3 step = calulateStep(camera, currentPos, origin, rotation, glm::vec3(0, 1, 0));
		movement = glm::translate(movement, glm::vec3(rotation * glm::vec4(step, 1.0f)));
		model[1] -= glm::vec4(step * 2.0f, 0);
	}
	
}
bool Mesh3D::selectEditors(GLFWwindow* window, Camera& camera)
{
	glm::vec3 rayDirection = camera.generateRay(camera.mouse);

	if (editMode != "false")
		return true;
	
	//if ppress on editor
	if (editModeMode == "edit")
	{
		if (rightEditor->hitMesh(camera))
		{
			editMode = "right";
			rightEditor->setColor(glm::vec3(1.0f, 0.5f, 0.5f));
			return true;
		}
		rightEditor->setColor(glm::vec3(0.7f, 0.0f, 0.0f));

		if (leftEditor->hitMesh(camera))
		{
			editMode = "left";
			leftEditor->setColor(glm::vec3(1.0f, 0.5f, 0.5f));
			return true;
		}
		leftEditor->setColor(glm::vec3(0.7f, 0.0f, 0.0f));

		if (forwardEditor->hitMesh(camera))
		{
			editMode = "forward";
			forwardEditor->setColor(glm::vec3(0.8f, 1.8f, 0.8f));
			return true;
		}
		forwardEditor->setColor(glm::vec3(0.3f, 0.6f, 0.3f));

		if (backwardEditor->hitMesh(camera))
		{
			editMode = "backward";
			backwardEditor->setColor(glm::vec3(0.8f, 1.8f, 0.8f));
			return true;
		}
		backwardEditor->setColor(glm::vec3(0.3f, 0.6f, 0.3f));

		if (upwardEditor->hitMesh(camera))
		{
			editMode = "upward";
			upwardEditor->setColor(glm::vec3(0.8f, 0.8f, 1.8f));
			return true;
		}
		upwardEditor->setColor(glm::vec3(0.3f, 0.3f, 0.8f));

		if (downwardEditor->hitMesh(camera))
		{
			editMode = "downward";
			downwardEditor->setColor(glm::vec3(0.8f, 0.8f, 1.8f));
			return true;
		}
		downwardEditor->setColor(glm::vec3(0.3f, 0.3f, 0.8f));
	}
	
	return false;

}
void Mesh3D::move(glm::vec3 move)
{
	movement = glm::translate(glm::mat4(1.0f), move);
}
void Mesh3D::rotate(float angle, glm::vec3 axis)
{
	//rotate in world space
	this->rotation =  glm::rotate(glm::mat4(1.0), angle, axis) * rotation;
}


glm::vec3 Mesh3D::findRotation(Camera& camera, glm::vec2 mouse, glm::vec3 axis)
{
	glm::vec3 origin = modelToWorldSpace(glm::vec3(0, 0, 0));
	glm::vec3 lookVec = camera.generateRay(mouse);
	glm::vec3 rotationVector = Math::planeIntersetion(axis, origin, lookVec, camera.loc);
	return rotationVector - origin;
}
glm::vec3 Mesh3D::calulateStep(Camera& camera, glm::vec2 currentMouse, glm::vec3 origin, glm::mat4 rotation, glm::vec3 moveDirection)
{
	glm::vec3 moveLine = rotation * glm::vec4(moveDirection, 1.0f);
	glm::vec3 planeN = Math::planeIntersetion(moveLine, origin, -moveLine, camera.loc) - origin;
	glm::vec3 inter1 = Math::planeIntersetion(planeN, origin, camera.generateRay(currentMouse), camera.loc);
	glm::vec3 inter2 = Math::planeIntersetion(planeN, origin, camera.generateRay(camera.mouse), camera.loc);
	return glm::dot(inter1 - inter2, moveLine) * moveDirection * 0.5f;
}

void Mesh3D::updateEditorLocation()
{
	glm::vec3 leftPos = modelToWorldSpace(glm::vec3(0.5, 0, 0));
	glm::vec3 rightPos = modelToWorldSpace(glm::vec3(-0.5, 0, 0));
	glm::vec3 forwardPos = modelToWorldSpace(glm::vec3(0, 0, 0.5));
	glm::vec3 backwardPos = modelToWorldSpace(glm::vec3(0, 0, -0.5));
	glm::vec3 upwardPos = modelToWorldSpace(glm::vec3(0, 0.5, 0));
	glm::vec3 downPos = modelToWorldSpace(glm::vec3(0, -0.5, 0));

	//sets the movement matrix for editors
	leftEditor->move(leftPos);
	rightEditor->move(rightPos);
	forwardEditor->move(forwardPos);
	backwardEditor->move(backwardPos);
	upwardEditor->move(upwardPos);
	downwardEditor->move(downPos);

	//sets the rotation matrix for editors
	leftEditor->rotation = rotation;
	rightEditor->rotation = rotation;
	forwardEditor->rotation = rotation;
	backwardEditor->rotation = rotation;
	upwardEditor->rotation = rotation;
	downwardEditor->rotation = rotation;
}