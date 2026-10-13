#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

out vec3 Normal;
out vec3 color;
out vec2 texCoord;
out vec4 shadowCoord;
out vec3 lightDirection;
out vec3 camDirection;




uniform vec3 lightPos;
uniform vec3 camLoc;
uniform mat4 lightView;

in DATA
{	
	vec3 color;
	vec2 texCoord;
	mat4 cameraMatrix1;
} data_in[];

void main()
{
	vec3 normal = vec3(0,0,0);
	//3D
	
		vec3 vector0 = vec3(gl_in[2].gl_Position - gl_in[1].gl_Position);
		vec3 vector1 = vec3(gl_in[0].gl_Position - gl_in[1].gl_Position);
		normal = normalize(cross(vector0, vector1));

	Normal = normal;
	
	
	color = data_in[0].color;
	texCoord = data_in[0].texCoord;
	shadowCoord = lightView * gl_in[0].gl_Position;
	lightDirection = lightPos - vec3(gl_in[0].gl_Position);
	camDirection = camLoc - vec3(gl_in[0].gl_Position);
	gl_Position = data_in[0].cameraMatrix1 * gl_in[0].gl_Position;
	EmitVertex();

	color = data_in[1].color;
	texCoord = data_in[1].texCoord;
	shadowCoord = lightView * gl_in[1].gl_Position; 
	lightDirection = lightPos - vec3(gl_in[1].gl_Position);
	camDirection = camLoc - vec3(gl_in[1].gl_Position);
	gl_Position = data_in[0].cameraMatrix1 * gl_in[1].gl_Position;
	EmitVertex();

	color = data_in[2].color;
	texCoord = data_in[2].texCoord;
	shadowCoord = lightView * gl_in[2].gl_Position; 
	lightDirection = lightPos - vec3(gl_in[2].gl_Position);
	camDirection = camLoc - vec3(gl_in[2].gl_Position);
	gl_Position = data_in[0].cameraMatrix1 * gl_in[2].gl_Position;
	EmitVertex();

	EndPrimitive();
}