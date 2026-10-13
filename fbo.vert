#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;



uniform mat4 cameraMatrix;
uniform mat4 rotation;
uniform mat4 movement;

void main()
{
	gl_Position = cameraMatrix * movement * rotation * vec4(aPos, 1.0f);
}