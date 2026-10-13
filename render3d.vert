#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out DATA
{	
	vec3 color;
	vec2 texCoord;
	mat4 cameraMatrix1;
} data_out;

uniform mat4 cameraMatrix;
uniform mat4 rotation;
uniform mat4 movement;
uniform mat4 model;

void main()
{
	data_out.cameraMatrix1 = cameraMatrix;
	data_out.color = aColor;
	data_out.texCoord = aTexCoord;
	gl_Position = movement * rotation * model * vec4(aPos, 1.0f);
}