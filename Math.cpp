#include "Math.h"
#include<iostream>

glm::vec3 Math::planeIntersetion(glm::vec3 planeN, glm::vec3 planeP, glm::vec3 vector, glm::vec3 vecLoc)
{
	glm::vec3 intersectionPoint;
	double t;
	double topEquation = planeN.x * (planeP.x - vecLoc.x) + planeN.y * (planeP.y - vecLoc.y) + planeN.z * (planeP.z - vecLoc.z);
	double buttomEquation = planeN.x * vector.x + planeN.y * vector.y + planeN.z * vector.z;
	t = topEquation / buttomEquation;

	intersectionPoint = vecLoc + vector * (float)t;
	return intersectionPoint;
}

std::string Math::toString(glm::vec3 vector)
{
	std::ostringstream string;
	string << vector.x << ", " << vector.y << ", " << vector.z;
	return string.str();
}

bool Math::hitTriangle(glm::vec3 rayLoc, glm::vec3 rayDirection, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	glm::vec3 planeN = glm::normalize(glm::cross(p2 - p1, p3 - p1));
	glm::vec3 pop = planeIntersetion(planeN, p1, rayDirection, rayLoc);
	return insideTriangle(pop, p1, p2, p3);
}

float Math::distanceFromPlane(glm::vec3 planeN, glm::vec3 planeP, glm::vec3 vector)
{
	glm::vec3 pop = planeIntersetion(planeN, planeP, -planeN, vector);
	return glm::distance(vector, pop);
}
//has to be projected on the plane first
bool Math::insideTriangle(glm::vec3 vector, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	glm::vec3 normal = -glm::cross(p2 - p1, p3 - p1);
	bool Edge1 = glm::dot(normal, glm::cross(p3 - p1, vector - p1)) >= 0;
	bool Edge2 = glm::dot(normal, glm::cross(p1 - p2, vector - p2)) >= 0;
	bool Edge3 = glm::dot(normal, glm::cross(p2 - p3, vector - p3)) >= 0;
	return Edge1 && Edge2 && Edge3;
}


bool Math::betweenTwoPlanes(glm::vec3 planeN1, glm::vec3 planeP1, glm::vec3 planeN2, glm::vec3 planeP2, glm::vec3 vector)
{
	float d1 = distanceFromPlane(planeN1, planeP1, vector);
	float d2 = distanceFromPlane(planeN2, planeP2, vector);
	float distanceBetweenPlanes = distanceFromPlane(planeN1, planeP1, planeP2);
	return  (d1 + d2) - distanceBetweenPlanes < 0.1;
}

float Math::areaOfTriangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	glm::vec3 AB = p2 - p1;
	glm::vec3 AC = p3 - p1;
	return glm::length(glm::cross(AB, AC)) / 2.0f;
}

float Math::distanceFromLine(glm::vec3 vector, glm::vec3 p1, glm::vec3 p2)
{
	if (glm::length(p2 - p1) < 0.1)
		return glm::distance(vector, p1);
	return areaOfTriangle(p1, p2, vector) * 2.0f / glm::distance(p1, p2);
}

float Math::DFT(glm::vec3 vector, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	glm::vec3 planeP = p1;
	glm::vec3 planeN = glm::normalize(glm::cross(p1, p2));
	glm::vec3 projectedOnPlane = planeIntersetion(planeN, planeP, -planeN, vector);

	//case 1 inside a triangle
	if (insideTriangle(projectedOnPlane, p1, p2, p3))
	{
		return distanceFromPlane(planeN, planeP, vector);
	}
	//case 2 between p1 and p2
	glm::vec3 normal = glm::normalize(p2 - p1);
	if (betweenTwoPlanes(normal, p1, -normal, p2, vector))
	{
		return distanceFromLine(vector, p1, p2);
	}
	//case 3 between p2 and p3
	normal = glm::normalize(p3 - p2);
	if (betweenTwoPlanes(normal, p2, -normal, p3, vector))
	{
		return distanceFromLine(vector, p2, p3);
	}
	//case 4 between p3 and p1
	normal = glm::normalize(p1 - p3);
	if (betweenTwoPlanes(normal, p3, -normal, p1, vector))
	{
		return distanceFromLine(vector, p3, p1);
	}
	//if non above is true return closest point
	float d1 = glm::distance(vector, p1);
	float d2 = glm::distance(vector, p2);
	float d3 = glm::distance(vector, p3);
	return std::min(std::min(d1, d2), d3);
}