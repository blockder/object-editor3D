#include"LinkedMesh.h"
#include"Arrow.h"
#include"Line.h"
#include"Mesh3D.h"
#include"Math.h"
#include <glm/gtx/vector_angle.hpp>

//arrows
static Vertex g1(glm::vec3(-0.05f, -0.05f, -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
static Vertex g2(glm::vec3(-0.05f, 0.05f, 0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
static Vertex g3(glm::vec3(-0.25f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
static Vertex g4(glm::vec3(-0.05f, 0.05f, 0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
static Vertex g5(glm::vec3(0.05f, 0.05f, -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
static Vertex g6(glm::vec3(0.0f, 0.25f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
static Vertex g7(glm::vec3(-0.05f, -0.05f, -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
static Vertex g8(glm::vec3(0.05f, 0.05f, -0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
static Vertex g9(glm::vec3(0.0f, 0.0f, -0.25f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));

LinkedMesh::LinkedMesh()
{
	this->editMode = "false";
	this->center = glm::vec3(0.0f);

	Texture blank("blank.png", 2);
	this->rotator = new Line(blank, g1, g2);
	this->right = new Arrow(blank, g1, g2, g3);
	this->up = new Arrow(blank, g4, g5, g6);
	this->backward = new Arrow(blank, g7, g8, g9);
}

void LinkedMesh::addMesh(Mesh3D* mesh)
{
	if (mesh->select)
	{
		remove(std::distance(list.begin(),std::find(list.begin(), list.end(), mesh)));
		return;
	}
	mesh->select = true;
	mesh->editModeMode = "move";
	list.push_back(mesh);
	showArrows = true;
}
void LinkedMesh::remove(int index)
{
	list[index]->select = false;
	list.erase(list.begin() + index);
}

void LinkedMesh::erase()
{
	for (int i = 0; i < list.size(); i++)
	{
		list[i]->select = false;
	}
	list.clear();
	showArrows = false;

}
int LinkedMesh::size()
{
	return list.size();
}
void LinkedMesh::updateCenter()
{
	if (list.size() == 0)
		return;
	glm::vec3 accumilator(0.0f);
	for (int i = 0; i < list.size(); i++)
	{
		accumilator += list[i]->modelToWorldSpace(glm::vec3(0, 0, 0));
	}
	center = accumilator / (float)list.size();
}
void LinkedMesh::updateArrows()
{
	glm::mat4 movement = glm::translate(glm::mat4(1.0f), center);
	right->movement = movement;
	up->movement = movement;
	backward->movement = movement;
}
void LinkedMesh::move(glm::vec3 step)
{
	for (int i = 0; i < list.size(); i++)
	{
		list[i]->movement = glm::translate(list[i]->movement, step);
	}
}
void LinkedMesh::rotate(float angle, glm::vec3 axis)
{
	for (int i = 0; i < list.size(); i++)
	{
		list[i]->rotation = glm::rotate(glm::mat4(1.0f), angle, axis) * list[i]->rotation;
		glm::vec3 relative = center - list[i]->modelToWorldSpace(glm::vec3(0));
		relative = glm::vec3(glm::rotate(glm::mat4(1.0f), angle, axis) * glm::vec4(- relative,1));
		list[i]->move(center + relative);
	}
	
}
void LinkedMesh::Edit(GLFWwindow* window, Camera& camera)
{
	if (list.size() == 1)
		list[0]->Edit(window, camera);
	updateCenter();
	updateArrows();
	//always have to hold house buttom to edit
	if (!camera.firstClick(window))
	{
		editMode = "false";
		camera.active = true;
		normalRot = glm::vec3(0);
		return;
	}
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	glm::vec3 normal(0.0f, 1.0f, 0.0f);
	glm::vec2 centerPoint = camera.projectPoint(center);
	//in pixels
	glm::vec2 currentPos(mouseX - camera.screenWidth / 2, mouseY - camera.screenHeight / 2);
	//screen coordinates
	glm::vec2 currentMouse(currentPos.x / (camera.screenWidth / 2), -currentPos.y / (camera.screenHeight / 2));

	rotator->p1.position = glm::vec3(currentMouse, 0.0f);
	rotator->p2.position = glm::vec3(centerPoint, 0);
	//movement
	if (showArrows)
	{
		if (editMode == "arrowRight")
		{
			glm::vec3 moveDirection(-1, 0, 0);
			glm::vec3 step = calulateStep(camera, currentPos, moveDirection);
			move(step);
		}
		if (editMode == "arrowUp")
		{
			glm::vec3 moveDirection(0, 1, 0);
			glm::vec3 step = calulateStep(camera, currentPos, moveDirection);
			move(step);
		}
		if (editMode == "arrowBack")
		{
			glm::vec3 moveDirection(0, 0, 1);
			glm::vec3 step = calulateStep(camera, currentPos, moveDirection);
			move(step);
		}
		//rotation
		if (editMode == "rotationX")
		{
			//glm::vec3 axis = rotation[0];
			glm::vec3 axis = glm::vec3(1, 0, 0);

			float angle = getAngle(camera, axis, currentPos);
			//round angle
			if (glm::distance(currentMouse, centerPoint) > 0.5f)
			{
				angle = roundAngle(3, axis, camera);
			}
			else
				normalRot = glm::vec3(0);
			rotate(angle, axis);
		}
		if (editMode == "rotationZ")
		{
			//glm::vec3 axis = rotation[2];
			glm::vec3 axis = glm::vec3(0, 0, 1);

			float angle = getAngle(camera, axis, currentPos);
			//round angle
			if (glm::distance(currentMouse, centerPoint) > 0.5f)
			{
				angle = roundAngle(3, axis, camera);
			}
			else
				normalRot = glm::vec3(0);
			rotate(angle, axis);
		}
		if (editMode == "rotationY")
		{
			normal = glm::vec3(0.0f, 0.0f, 1.0f);
			//glm::vec3 axis = rotation[1];
			glm::vec3 axis = glm::vec3(0, 1, 0);

			float angle = getAngle(camera, axis, currentPos);
			//round angle
			if (glm::distance(currentMouse, centerPoint) > 0.5f)
			{
				angle = roundAngle(3, axis, camera);
			}
			else
				normalRot = glm::vec3(0);
			rotate(angle, axis);
		}
	}
}
glm::vec3 LinkedMesh::findRotation(Camera& camera, glm::vec2 currentMouse, glm::vec3 axis)
{
	glm::vec3 lookVec = camera.generateRay(currentMouse);
	glm::vec3 rotationVector = Math::planeIntersetion(axis, center, lookVec, camera.loc);
	return rotationVector - center;
}
glm::vec3 LinkedMesh::calulateStep(Camera& camera, glm::vec2 currentMouse, glm::vec3 moveDirection)
{
	glm::vec3 planeN = Math::planeIntersetion(moveDirection, center, -moveDirection, camera.loc) - center;
	glm::vec3 inter1 = Math::planeIntersetion(planeN, center, camera.generateRay(currentMouse), camera.loc);
	glm::vec3 inter2 = Math::planeIntersetion(planeN, center, camera.generateRay(camera.mouse), camera.loc);
	return glm::dot(inter1 - inter2, moveDirection) * moveDirection;
}
float LinkedMesh::roundAngle(int roundDegree, glm::vec3 axis, Camera& camera)
{
	if (glm::length(normalRot) == 0)
		normalRot = findRotation(camera, camera.mouse, axis);
	float roundValue = 360.0f / std::pow(2, roundDegree);
	glm::vec3 currentRot = findRotation(camera, camera.mouse, axis);
	int rotAngle = glm::degrees(glm::angle(glm::normalize(currentRot), glm::normalize(normalRot))) / roundValue;
	float angle = glm::radians(rotAngle * roundValue);
	float sign = -glm::dot(glm::cross(currentRot, normalRot), axis);
	sign /= sign == 0 ? 1 : std::abs(sign);

	if (rotAngle > 0) {

		normalRot = currentRot;
	}
	return angle * sign;
}
float LinkedMesh::getAngle(Camera& camera, glm::vec3 axis, glm::vec2 mouse)
{
	glm::vec3 currentRot = findRotation(camera, mouse, axis);
	glm::vec3 prevRot = findRotation(camera, camera.mouse, axis);

	float angle = glm::angle(glm::normalize(currentRot), glm::normalize(prevRot));
	float sign = glm::dot(glm::cross(prevRot, currentRot), axis);
	sign /= sign == 0 ? 1 : std::abs(sign);
	return angle * sign;
}
bool LinkedMesh::selectArrows(GLFWwindow* window, Camera& camera)
{
	if (!showArrows)
		return false;
	if (editMode != "false")
		return true;
	//rotation check
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		rotator->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
		editMode = "rotationX";
		return true;
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		rotator->setColor(glm::vec3(0.0f, 0.0f, 1.0f));
		editMode = "rotationZ";
		return true;
	}
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
	{
		rotator->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
		editMode = "rotationY";
		return true;
	}
	if (right->hitMesh(camera))
	{
		editMode = "arrowRight";
		right->setColor(glm::vec3(1.0f, 0.5f, 0.5f));
		return true;
	}
	right->setColor(glm::vec3(0.7f, 0.0f, 0.0f));


	if (up->hitMesh(camera))
	{
		editMode = "arrowUp";
		up->setColor(glm::vec3(0.5f, 0.5f, 1.5f));
		return true;
	}
	up->setColor(glm::vec3(0.0f, 0.0f, 0.7f));


	if (backward->hitMesh(camera))
	{
		editMode = "arrowBack";
		backward->setColor(glm::vec3(0.5f, 1.5f, 0.5f));
		return true;
	}
	backward->setColor(glm::vec3(0.0f, 0.7f, 0.0f));

	return false;
}
void LinkedMesh::draw(Shader& shaderProgram, Camera& camera)
{
	if (list.size() > 0  && showArrows)
	{
		glDisable(GL_DEPTH_TEST);
		right->draw(shaderProgram, camera);
		up->draw(shaderProgram, camera);
		backward->draw(shaderProgram, camera);
		glEnable(GL_DEPTH_TEST);
		if (editMode == "rotationX" || editMode == "rotationY" || editMode == "rotationZ")
		{
			rotator->draw();
		}
	}
}