#version 330 core
layout (location = 0 ) in vec3 aPos;
layout (location = 1 ) in vec3 aColor;
layout (location = 2 ) in vec2 aTex;
layout (location = 3 ) in vec3 aNormal;

out vec3 color; 
out vec2 texCoord;
out vec3 Normal;
out vec3 crntPos;
out vec3 vertNormal;

uniform mat4 camMatrix;
uniform mat4 model;
uniform vec3 camPos;

void main()
{
	gl_Position = camMatrix * model * vec4(aPos, 1.0);
	crntPos = vec3(model * vec4(aPos, 1.0));
	color = aColor;
	texCoord = aTex;
	Normal = aNormal;

	vertNormal = normalize(crntPos- vec3(3.0f, 1.0f, 1.0f) + aNormal);

}