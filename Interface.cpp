#include"Interface.h"
#include"Mesh3D.h"
#include"LinkedMesh.h"

//background
Vertex p1(glm::vec3(-0.25f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
Vertex p2(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f));
Vertex p3(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));
Vertex p4(glm::vec3(-0.25f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
//editMode select
Vertex p5(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
Vertex p6(glm::vec3(-0.1f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
Vertex p7(glm::vec3(-0.1f, 0.1f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
Vertex p8(glm::vec3(0.0f, 0.1f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
Vertex p9(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
Vertex p10(glm::vec3(-0.08f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
Vertex p11(glm::vec3(-0.08f, 0.08f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
Vertex p12(glm::vec3(0.0f, 0.08f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
Vertex p13(glm::vec3(-0.045f, 0.04f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
//texture tiles
Vertex p14(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.75f, 0.25f));
Vertex p15(glm::vec3(-0.2f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.25f, 0.25f));
Vertex p16(glm::vec3(-0.2f, 0.2f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.25f, 0.75f));
Vertex p17(glm::vec3(0.0f, 0.2f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.75f, 0.75f));



Interface::Interface(LinkedMesh* linkedList)
{
	show = false;
	target = NULL; 
	this->linkedList = linkedList;

	blank = Texture("blank.png", 2);
	wood = Texture("wood.png", 2);
	plane = Texture("plane.png", 2);
	cube = Texture("cube.png", 2);
	//background
	background = Tile(blank, p1, p2, p3, p4); 
	background.setColor(glm::vec3(0.1, 0.1, 0.1));
	background.transparency = 0.85f;

	editModeS = Tile(blank, p5, p6, p7, p8); editModeS.move(glm::vec3(-0.8f, 0.8f, 0));
	editMode = Tile(blank, p9, p10, p11, p12); editMode.move(glm::vec3(-0.81f, 0.81f, 0)); editMode.setColor(glm::vec3(0.2, 0.2, 0.2));
	whiteBS = Tile(blank, p5, p6, p7, p8); whiteBS.move(glm::vec3(-0.8f, 0.6f, 0)); 
	whiteB = Tile(blank, p9, p10, p11, p12); whiteB.move(glm::vec3(-0.81f, 0.61f, 0)); whiteB.select = true;
	redBS = Tile(blank, p5, p6, p7, p8); redBS.move(glm::vec3(-0.65f, 0.6f, 0));
	redB = Tile(blank, p9, p10, p11, p12); redB.move(glm::vec3(-0.66f, 0.61f, 0)); redB.setColor(glm::vec3(1, 0, 0));
	blueBS = Tile(blank, p5, p6, p7, p8); blueBS.move(glm::vec3(-0.50f, 0.6f, 0));
	blueB = Tile(blank, p9, p10, p11, p12); blueB.move(glm::vec3(-0.51f, 0.61f, 0)); blueB.setColor(glm::vec3(0, 0, 1));
	greenBS = Tile(blank, p5, p6, p7, p8); greenBS.move(glm::vec3(-0.35f, 0.6f, 0));
	greenB = Tile(blank, p9, p10, p11, p12); greenB.move(glm::vec3(-0.36f, 0.61f, 0)); greenB.setColor(glm::vec3(0, 1, 0));
	grayBS = Tile(blank, p5, p6, p7, p8); grayBS.move(glm::vec3(-0.8f, 0.4f, 0));
	grayB = Tile(blank, p9, p10, p11, p12); grayB.move(glm::vec3(-0.81f, 0.41f, 0)); grayB.setColor(glm::vec3(0.2, 0.2, 0.2));
	triangle = Tile(blank, p13, p6, p7, p13); triangle.move(glm::vec3(-0.8f, 0.1f, 0));
	blankT = Tile(blank, p14, p15, p16, p17); blankT.move(glm::vec3(-0.7f, -0.1f, 0));
	woodT = Tile(wood, p14, p15, p16, p17); woodT.move(glm::vec3(-0.4f, -0.1f, 0));
	cubeM = Tile(cube, p14, p15, p16, p17); cubeM.move(glm::vec3(-0.7f, 0.7f, 0));
	planeM = Tile(plane, p14, p15, p16, p17); planeM.move(glm::vec3(-0.4f, 0.7f, 0));
}

void Interface::draw(Shader& shaderProgram, Camera& camera)
{
	if (buildMode)
	{
		glDisable(GL_DEPTH_TEST);
		background.draw(shaderProgram, camera);
		cubeM.draw(shaderProgram, camera);
		planeM.draw(shaderProgram, camera);
		glEnable(GL_DEPTH_TEST);
		return;
	}
	if (!show)
		return;
	glDisable(GL_DEPTH_TEST);
	background.draw(shaderProgram, camera);

	editModeS.draw(shaderProgram, camera);
	editMode.draw(shaderProgram, camera);
	whiteBS.draw(shaderProgram, camera);
	whiteB.draw(shaderProgram, camera);
	redBS.draw(shaderProgram, camera);
	redB.draw(shaderProgram, camera);
	blueBS.draw(shaderProgram, camera);
	blueB.draw(shaderProgram, camera);
	greenBS.draw(shaderProgram, camera);
	greenB.draw(shaderProgram, camera);
	grayBS.draw(shaderProgram, camera);
	grayB.draw(shaderProgram, camera);
	triangle.draw(shaderProgram, camera); 
	if (triangle.select)
	{
		blankT.draw(shaderProgram, camera);
		woodT.draw(shaderProgram, camera);
	}

	glEnable(GL_DEPTH_TEST);
}

void Interface::setTarget(LinkedMesh* linkedList)
{
	if (linkedList->size() != 1)
	{
		if (this->target != NULL)
		{
			editMode.select = false;
			this->target->editModeMode = "move";
		}
		show = false;
		return;
	}
	Mesh3D* target = linkedList->list[0];

	show = true;
	setParameters(target);
	Interface::target = target;
}
void Interface::setParameters(Mesh3D* target)
{
	//set editmode button
	if (editMode.select) {
		target->editModeMode = "edit";
		linkedList->showArrows = false;
	}
	if (!editMode.select) {
		target->editModeMode = "move";
		linkedList->showArrows = true;
	}
	//set color
	if (color != NULL) color->select = false;
	color = &whiteB;
	if (target->color == glm::vec3(1, 0, 0))
		color = &redB;
	if (target->color == glm::vec3(0, 1, 0))
		color = &greenB;
	if (target->color == glm::vec3(0, 0, 1))
		color = &blueB;
	if (target->color == glm::vec3(0.2, 0.2, 0.2))
		color = &grayB;
	color->select = true;
	//set texture
	if (texture != NULL) texture->select = false;
	texture = &blankT;
	if (target->texture.location == "wood.png")
		texture = &woodT;
	texture->select = true;
	
}
bool Interface::selectButton(GLFWwindow* window, Camera& camera)
{
	if (camera.firstClick(window) && camera.active)
	{
		//click of edit button
		if (editMode.hitMesh(camera))
		{
			editMode.select = !editMode.select;
			linkedList->showArrows = !editMode.select;
			target->editModeMode = editMode.select ? "edit" : "move";
			
		}
		//white button press
		if (whiteB.hitMesh(camera))
		{
			if (color != NULL) color->select = false;
			color = &whiteB;
			color->select = true;
			target->setColor(glm::vec3(1, 1, 1));
		}
		//red button press
		if (redB.hitMesh(camera))
		{
			if (color != NULL) color->select = false;
			color = &redB;
			color->select = true;
			target->setColor(glm::vec3(1, 0, 0));
			
		}
		//blue button press
		if (blueB.hitMesh(camera))
		{
			if (color != NULL) color->select = false;
			color = &blueB;
			color->select = true;
			target->setColor(glm::vec3(0, 0, 1));
		}
		//green button press
		if (greenB.hitMesh(camera))
		{
			if (color != NULL) color->select = false;
			color = &greenB;
			color->select = true;
			target->setColor(glm::vec3(0, 1, 0));
		}
		if (grayB.hitMesh(camera))
		{
			if (color != NULL) color->select = false;
			color = &grayB;
			color->select = true;
			target->setColor(glm::vec3(0.2, 0.2, 0.2));
		}
		//triangle press
		if (triangle.hitMesh(camera))
		{
			triangle.select = !triangle.select;
			if (triangle.select)
			{
				triangle.p1 = p13;
				triangle.p2 = p13;
				triangle.p3 = p7;
				triangle.p4 = p8;
				triangle.move(glm::vec3(-0.8f, 0.1f, 0));
				triangle.updateVBO();
			}
			else
			{
				triangle.p1 = p13;
				triangle.p2 = p6;
				triangle.p3 = p7;
				triangle.p4 = p13;
				triangle.move(glm::vec3(-0.8f, 0.1f, 0));
				triangle.updateVBO();
			}
		}
		//texture blank press
		if (triangle.select)
		{
			if (blankT.hitMesh(camera))
			{
				if (texture != NULL) texture->select = false;
				texture = &blankT; 
				texture->select = true;
				target->texture = blank;
			}
			if (woodT.hitMesh(camera))
			{
				if (texture != NULL) texture->select = false;
				texture = &woodT;
				texture->select = true;
				target->texture = wood; 
			}
		}


	}

	return background.hitMesh(camera);


}
const char* Interface::selectType(GLFWwindow* window, Camera& camera)
{
	if (cubeM.hitMesh(camera))
	{
		planeM.select = false;
		cubeM.select = true;
		return "cube";
	}
	if (planeM.hitMesh(camera))
	{
		cubeM.select = false;
		planeM.select = true;
		return "plane";
	}
	if (background.hitMesh(camera))
	{
		return"background";
	}
	return "build";
}
