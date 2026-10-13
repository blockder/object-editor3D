#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D texUnit;
uniform float transparency;
uniform bool select;

void main()
{	
	vec3 finalColor = color;
	if(select)
	{
		finalColor += 0.4f;
	}
	FragColor = texture(texUnit, texCoord) * vec4(finalColor, transparency);
}