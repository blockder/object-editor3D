#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<algorithm>
#include"Plane.h"
#include"Editor.h"
#include"Shader.h"
#include<vector>
#include"Texture.h"
#include"Camera.h"
#include"FBO.h"
#include"RBO.h"
#include"Line.h"
#include"Math.h"
#include"Tile.h"
#include"Interface.h"
#include"Cube.h"
#include"LinkedMesh.h"



const int screenWidth = 1200;
const int screenHeight = 800;
glm::vec3 backgroundColor(0.0f, 0.1f, 0.0f);
const int FPS = 60;
//objects
Camera camera;
Camera lightView;
std::vector<Mesh3D*> DNS;
Cube* sun;
//Mesh3D* Selected;
LinkedMesh* linkedList;
Interface* interface;
bool buildMode = false;
bool applyShadow = false;

	//cube points
	Vertex c1(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
	Vertex c2(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f));
	Vertex c3(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));
	Vertex c4(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
	Vertex c5(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
	Vertex c6(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f));
	Vertex c7(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));
	Vertex c8(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
	//plane points
	Vertex pp1(glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
	Vertex pp2(glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f));
	Vertex pp3(glm::vec3(0.5f, 0.0f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));
	Vertex pp4(glm::vec3(-0.5f, 0.0f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f));

void update(GLFWwindow * window);
void draw(GLFWwindow * window, Shader & renderer3d, Shader& renderer, Shader& mark, RBO& shadowMap);
int main()
{
	//initialize glfw
	glfwInit();
	//specify the version of opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//tel opengl we are using only core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//create a glfwWindow with size and name
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "openGl", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "falied to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	linkedList = new LinkedMesh();
	interface = new Interface(linkedList);
	camera = Camera(glm::vec3(0, 0, -0.5), glm::vec3(0, 0, 1.0f), glm::vec3(0, 1.0f, 0), screenWidth , screenHeight);
	lightView = Camera(glm::vec3(0, 10, 0), glm::vec3(0, -1, 0), glm::vec3(0, 0, 1), screenWidth, screenHeight); 
	
	
	Shader renderer3D = Shader("render3d.vert","render3d.geom", "render3d.frag");
	Shader renderer = Shader("render.vert", "render.frag");
	Shader planeMark = Shader("render3d.vert", "markPlane.geom", "markPlane.frag");
	
	RBO shadowMap = RBO(screenWidth, screenHeight); 

	Texture wood("wood.png", 2);
	Texture blank("blank.png", 2);

	sun =   new Cube(blank, c1, c2, c3, c4, c5, c6, c7, c8);
	sun->scale(0.2f);
	sun->move(glm::vec3(0, 11, 0));
	DNS.push_back(sun);
	
	 Plane plane = Plane(wood, pp1, pp2, pp3, pp4);
	 DNS.push_back(&plane);

	 
	
	
	 double lastTime = 0;
	double currentTime = 0;
	
	//main game loop
	while (!glfwWindowShouldClose(window))
	{
		currentTime = glfwGetTime();
		if (currentTime - lastTime >= 1.0 / FPS)
		{
			update(window);
			draw(window, renderer3D,renderer, planeMark, shadowMap);
			

			lastTime = currentTime;
		}
	}

	renderer3D.Delete();
	//close window and glfw
	glfwDestroyWindow(window);
	glfwTerminate();
	return -1;
}

//functions
bool prevPRess = false;
const char* meshType;
void sortByDistance(std::vector<Mesh3D*>* DNS, glm::vec3 location)
{
	std::sort(DNS->begin(), DNS->end(),
		[location](Mesh3D* a, Mesh3D* b)
		{
			return glm::distance(a->modelToWorldSpace(glm::vec3(0)), location) < glm::distance(b->modelToWorldSpace(glm::vec3(0)), location);
		});
}
void createMesh(Camera& camera, const char* meshType)
{
	Mesh3D* holdTemp = NULL;
	float distanceFromHit = 999;
	for (int i = 0; i < DNS.size(); i++)
	{
		if (DNS[i]->hitMesh(camera) && glm::distance(DNS[i]->whereHit(camera), camera.loc) < distanceFromHit)
		{
			holdTemp = DNS[i];
			distanceFromHit = glm::distance(holdTemp->whereHit(camera), camera.loc);
		}
	}
	glm::vec3 placement(camera.generateRay(camera.mouse) * 25.0f + camera.loc);
	if (distanceFromHit != 999)
		placement = holdTemp->whereHit(camera);
	if (meshType == "cube")
	{
		DNS.push_back(new Cube(Texture("blank.png", 3), c1, c2, c3, c4, c5, c6, c7, c8));
	}
	if (meshType == "plane")
	{
		DNS.push_back(new Plane(Texture("blank.png", 3), pp1, pp2, pp3, pp4));
	}
	linkedList->addMesh(DNS[DNS.size() - 1]);
	DNS[DNS.size() - 1]->move(placement);
	buildMode = false;
}
void build(GLFWwindow* window)
{
	//change buildMode state
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && !prevPRess)
	{
		prevPRess = true;
		buildMode = !buildMode;
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_RELEASE)
		prevPRess = false;
	//set builder type nad build
	if (buildMode)
	{
		linkedList->erase();

		camera.active = false;
		interface->buildMode = true;
		if (camera.firstClick(window))
		{
			const char* type = interface->selectType(window, camera);
			//build
			if (type == "build")
			{
				createMesh(camera, meshType);
				camera.active = true;
				return;
			}
			//set type
			if (type == "background")
				return;
			meshType = type;

		}
		return;
	}
	interface->buildMode = false;
}
void Delete(GLFWwindow* window)
{
	if (linkedList->size() ==0)
		return;
	if (glfwGetKey(window, GLFW_KEY_DELETE) == GLFW_PRESS)
	{
		for(int i=0; i<linkedList->size(); i++)
			DNS.erase(std::remove(DNS.begin(), DNS.end(), linkedList->list[i]), DNS.end());
		linkedList->erase();
	}
}
bool prevPress = false;
void duplicate(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && !prevPress)
	{
		for (int i = linkedList->size()-1; i >= 0; i--)
		{
			prevPress = true;
			if (linkedList->list[i]->name == "cube")
			{
				DNS.push_back(new Cube(dynamic_cast<Cube&>(*linkedList->list[i])));
			}
			if (linkedList->list[i]->name == "plane")
			{
				DNS.push_back(new Plane(dynamic_cast<Plane&>(*linkedList->list[i])));
			}
			linkedList->remove(i);
			linkedList->addMesh(DNS[DNS.size() - 1]);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		prevPress = false;
	}

}
void selectObject(GLFWwindow* window)
{
	 
	if (linkedList->size() > 0)
	{
		if (linkedList->selectArrows(window, camera))
		{
			camera.active = false;
			return;
		}
		if (linkedList->size() == 1)
		{
			//press on editors
			if (linkedList->list[0]->selectEditors(window, camera))
			{
				camera.active = false;
				return;
			}
			//press on interface
			if (interface->selectButton(window, camera))
			{
				camera.active = false;
				return;
			}
		}
		camera.active = true;
	}

	//click on object
	if (camera.firstClick(window))
	{
		glm::vec3 rayDirection = camera.generateRay(camera.mouse);
		//sort DNS by distance from camera
		sortByDistance(&DNS, camera.loc);
		for (int i = 0; i < DNS.size(); i++)
		{
			if (DNS[i]->hitMesh(camera))
			{
				if (linkedList->size() > 0 && glfwGetKey(window, GLFW_KEY_LEFT_ALT) ==  GLFW_RELEASE) linkedList->erase();
				linkedList->addMesh(DNS[i]);
				return;
			}
		}
		
		//click on background
		linkedList->erase();

		return;
		
	}
}
void genShadowMap(GLFWwindow* window,RBO& shadowMap, Shader& renderer)
{
	shadowMap.bind();
	glViewport(0, 0, screenWidth, screenHeight);
	// Specify the color of the background
	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	//draws all objects
	for (int i = 0;i < DNS.size();i++)
	{
		DNS[i]->draw(renderer, lightView);
	}

	shadowMap.unBind();
}
bool canPress = true;
bool toggle(GLFWwindow* window, int key)
{
	if ( canPress && glfwGetKey(window, key) == GLFW_PRESS)
	{
		canPress = false;
		return true;
	}
	if (glfwGetKey(window, key) == GLFW_RELEASE)
		canPress = true;
	return false;
}
//update shit
void update(GLFWwindow* window)
{
	selectObject(window);
	linkedList->Edit(window, camera);
	build(window);
	Delete(window);
	duplicate(window); 
	interface->setTarget(linkedList);
	camera.Inputs(window);
	lightView.loc = sun->modelToWorldSpace(glm::vec3(0,-1,0));
	//shadow toggle
	if (toggle(window, GLFW_KEY_H))
		applyShadow = !applyShadow;
}
//draw shit
void draw(GLFWwindow* window, Shader& renderer3d,Shader& renderer, Shader& mark, RBO& shadowMap)
{
	genShadowMap(window, shadowMap, renderer3d);
	//draw objects
	glViewport(0, 0, screenWidth, screenHeight);
	// Specify the color of the background
	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//draws all objects
	for (int i = 0;i < DNS.size();i++)
	{
		DNS[i]->draw(renderer3d, camera, shadowMap.texture, lightView, applyShadow);
		if (DNS[i]->select)
			DNS[i]->Mesh3D::draw(mark, camera);
	}
	
	//draw interface
	interface->draw(renderer, camera); 
	//draw linkedlist
	linkedList->draw(renderer3d, camera);
	
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);
	// Take care of all GLFW events
	glfwPollEvents();
}