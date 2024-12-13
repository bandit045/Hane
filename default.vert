#version 330 core
layout (location = 0 ) in vec3 aPos;
layout (location = 1 ) in vec3 aNormal;
layout (location = 2 ) in vec2 aTex;
layout (location = 3 ) in vec3 aColor;

out vec3 color; 
out vec2 texCoord;
out vec3 Normal;
out vec3 crntPos;
out vec3 vertNormal;

uniform bool useCustomTransform; // In case we only send Model matrix to shader without separete components (Position-Rotate-Scale)

uniform mat4 camMatrix;
uniform vec3 camPos;

uniform mat4 model;
uniform mat4 modelPos;
uniform mat4 modelRotate;
uniform mat4 modelScale;

void main()
{
	// In case we only send Model matrix to shader without separete components (Position-Rotate-Scale)
	if(!useCustomTransform) 
	{
		gl_Position = camMatrix * model * vec4(aPos, 1.0);
		crntPos = vec3(model * vec4(aPos, 1.0));
	}
	else if (useCustomTransform)
	{
		gl_Position =  camMatrix * modelPos * modelRotate * modelScale * vec4(aPos, 1.0);
		crntPos = vec3(modelPos * modelRotate * modelScale * vec4(aPos, 1.0));
	};

	// Passing data to fragment shader
	color = aColor;
	texCoord = aTex;
	Normal = mat3(transpose(inverse( modelPos * modelRotate * modelScale ))) * aNormal;;
	//Normal = aNormal;

	vertNormal = normalize(crntPos- vec3(3.0f, 1.0f, 1.0f) + aNormal);
}