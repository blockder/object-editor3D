#pragma once
#include<glm/glm.hpp>
#include <sstream>
#include <string>
class Math
{
public:
	static glm::vec3 planeIntersetion(glm::vec3 planeN, glm::vec3 planeP, glm::vec3 vector, glm::vec3 vecLoc); 

	static std::string toString(glm::vec3 vector);

	static bool hitTriangle(glm::vec3 rayLoc, glm::vec3 rayDirection, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
	
	static	float distanceFromPlane(glm::vec3 planeN, glm::vec3 planeP, glm::vec3 vector);
	//has to be projected on the plane first
	static bool insideTriangle(glm::vec3 vector, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

	static bool betweenTwoPlanes(glm::vec3 planeN1, glm::vec3 planeP1, glm::vec3 planeN2, glm::vec3 planeP2, glm::vec3 vector);

	static float areaOfTriangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);


	static float distanceFromLine(glm::vec3 vector, glm::vec3 p1, glm::vec3 p2);

	static float DFT(glm::vec3 vector, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
};

