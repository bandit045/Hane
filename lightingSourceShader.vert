#version 330 core
layout (location = 0 ) in vec3 aPos;
layout (location = 1 ) in vec3 aNormal;

uniform mat4 camMatrix;
uniform mat4 modelPos;
uniform mat4 modelRotate;
uniform mat4 modelScale;

out vec3 Normal;

void main()
{
	gl_Position = camMatrix * modelPos * modelRotate * modelScale * vec4(aPos, 1.0);
	Normal = aNormal;
}