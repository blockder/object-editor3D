#version 330 core

layout (triangles) in;
layout (line_strip, max_vertices = 4) out;



in DATA
{	
	vec3 color;
	vec2 texCoord;
	mat4 cameraMatrix1;
} data_in[];

void main()
{

	//line 1
	gl_Position = data_in[0].cameraMatrix1 * gl_in[0].gl_Position;
	EmitVertex();

	gl_Position = data_in[1].cameraMatrix1 * gl_in[1].gl_Position;
	EmitVertex();

	EndPrimitive();
	//line 2
	gl_Position = data_in[1].cameraMatrix1 * gl_in[1].gl_Position;
	EmitVertex();

	gl_Position = data_in[2].cameraMatrix1 * gl_in[2].gl_Position;
	EmitVertex();

	//EndPrimitive();
}