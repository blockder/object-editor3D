#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 color;
in vec2 texCoord;
in vec4 shadowCoord;
in vec3 lightDirection;
in vec3 camDirection;


uniform sampler2D texUnit;
uniform sampler2D shadowMap;
uniform bool select;
uniform bool applyShadow;

void main()
{	
	vec3 lightDirection = normalize(lightDirection);
	vec3 camDirection = normalize(camDirection);
	float light = max(dot(Normal, lightDirection), 0.0f) + pow(max(dot(reflect(-lightDirection, Normal), camDirection), 0.0f),32)*0.4f + 0.5f;

	//shadow map
	vec3 lightCoords = shadowCoord.xyz / shadowCoord.w;
	lightCoords = lightCoords * 0.5f + 0.5f;
	float closeDepth = texture(shadowMap, lightCoords.xy).r;
	float currentDepth = lightCoords.z;

	if(currentDepth > closeDepth + 0.0001f)
	light = 0.5f;
	if(select || !applyShadow)
	light = 1.0f;

	FragColor = texture(texUnit, texCoord) * vec4(light * color, 1.0f);
	//FragColor.w = 1.0f;
}