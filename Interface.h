#pragma once
#include"Tile.h"


class LinkedMesh;

class Interface
{
public:
	bool show;
	LinkedMesh* linkedList;
	Mesh3D* target;
	Tile background;
	Tile editModeS;
	Tile editMode;
	Tile whiteBS;
	Tile whiteB;
	Tile redBS;
	Tile redB;
	Tile blueBS;
	Tile blueB;
	Tile greenBS;
	Tile greenB;
	Tile grayBS;
	Tile grayB;
	Tile triangle;
	Tile blankT;
	Tile woodT;
	Tile cubeM;
	Tile planeM;

	Interface(LinkedMesh* linkedList);

	void draw(Shader& shaderProgram, Camera& camera);
	void setTarget(LinkedMesh* linkedList);
	bool selectButton(GLFWwindow* window, Camera& camera);
	const char* selectType(GLFWwindow* window, Camera& camera);
	bool buildMode;
	

private:
	Texture blank;
	Texture wood;
	Texture plane;
	Texture cube;
	Tile* color;
	Tile* texture;
	void setParameters(Mesh3D* target);
};