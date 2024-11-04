#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"

class Object{
public:
	enum class Rotation {
		X,
		Y,
		Z,
	};

	// Position of object
	glm::vec3 Position;
	glm::vec3 m_scale;
	
	// Matrix model
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	// Matrixe for transformation
	glm::mat4 modelPos = glm::mat4(1.0f);
	glm::mat4 modelRotate = glm::mat4(1.0f);
	glm::mat4 modelScale = glm::mat4(1.0f);

	// Orientation for storing variable
	glm::vec3 m_orientationEuler;
	glm::quat m_orientationQuat;

	// Which shader renders this object
	GLuint shaderWhichRenderObject_ID;

	Object(Shader shaderWhichRenderObject, glm::vec3 scaleFactor, glm::quat orientationQuat, glm::vec3 positionObject, glm::vec3 orientationEuler);

	// Setters
	void setPosition(glm::vec3 newPosition);
	void setScale(glm::vec3 scaleFactor);
	void setRotateEuler(glm::vec3 rotationEuler);
	void setRotateQuat(glm::quat orientationQuat);
	// Getters
	float getOritationEuler(Rotation rotation);
};
#endif // !OBJECT_CLASS_H