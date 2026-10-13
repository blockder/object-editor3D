#include"Camera.h"
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include"Mesh.h"


Camera::Camera(glm::vec3 loc, glm::vec3 direction, glm::vec3 up, float screenWidth, float screenHeight)
{
	Camera::screenWidth = screenWidth;
	Camera::screenHeight = screenHeight;
	Camera::loc = loc;
	Camera::direction = direction;
	Camera::up = up;
	Camera::active = true;
}



void Camera::sendToShader(Shader& shaderProgram, const char* name)
{
	glm::mat4 prespective = glm::perspective( FOV, screenWidth / screenHeight, nearPlane, farPlane);
	glm::mat4 lookAt = glm::lookAt(loc, loc + direction, up);
	Camera::cameraMatrix = prespective * lookAt ;

	//make sure shaderPrgram is active
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.id, name), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::Inputs(GLFWwindow* window)
{
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	mouse.x =  mouseX - screenWidth /2;
	mouse.y =  mouseY - screenHeight /2;
	
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE )
	{
		active = true;
		clickBefore = false;
	}
	if (!active)
	{
		return;
	}
	//first click part 2
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !clickBefore)
	{
		clickBefore = true;
		mouse.x = 0, mouse.y = 0;
	}
	//hold click
	 if (clickBefore )
	{
		//rotate x
		glm::vec3 newDirection = glm::rotate(direction, glm::radians(-mouse.x * sesitivity), up);
		//rotate y
		newDirection = glm::rotate(newDirection, glm::radians(-mouse.y * sesitivity), glm::normalize(glm::cross(newDirection, up)));
		//don't rotate too much
		if (glm::dot(newDirection, up) < 0.999f && glm::dot(newDirection, up) > -0.999f)
		{
			direction = newDirection;
		}

		glfwSetCursorPos(window, (screenWidth / 2), (screenHeight / 2));
	}
	//move around
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		loc += speed * glm::normalize(glm::vec3(direction.x, 0, direction.z));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		loc -= speed * glm::normalize(glm::vec3(direction.x, 0, direction.z));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		loc += speed * glm::normalize(glm::vec3(glm::cross(direction, up).x, 0, glm::cross(direction, up).z));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		loc -= speed * glm::normalize(glm::vec3(glm::cross(direction, up).x, 0, glm::cross(direction, up).z));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		loc += speed * up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		loc -= speed * up;
	}

	
}


bool Camera::firstClick(GLFWwindow* window)
{
	return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !clickBefore;
}

void Camera::setClickBefore(bool state)
{
	clickBefore = state;
}

glm::vec2 Camera::projectPoint(glm::vec3 point)
{
	glm::vec4 temp =  Camera::cameraMatrix * glm::vec4(point, 1.0f);
	return glm::vec2(temp.x/temp.w ,temp.y/temp.w);
}

glm::vec3 Camera::generateRay(glm::vec2 mouse)
{
	float aspectRation = screenWidth / screenHeight;
	glm::vec2 normalizedMouse(mouse.x / (screenWidth / 2.0f) * aspectRation, -mouse.y / (screenHeight / 2.0f)); 
	glm::vec3 side = glm::normalize(glm::cross(direction, up)); 
	glm::vec3 newUp = glm::normalize(glm::cross(side, direction)); 
	float Edge = glm::tan(FOV / 2.0f) * nearPlane;
	return (side * normalizedMouse.x * Edge) + (newUp * normalizedMouse.y * Edge) + (direction * nearPlane);
}