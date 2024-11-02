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

	glm::vec3 Position;
	glm::vec3 Orientation;
	glm::vec3 Scale = glm::vec3(1.0f);
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	float OrientationX_;
	float OrientationY_;
	float OrientationZ_;

	float PositionX_;
	float PositionY_;
	float PositionZ_;

	// Which shader renders this object
	GLuint shaderWhichRenderObject_ID;

	// If any transformation is applied
	bool hasAnyTransformApplied = false;

	Object(Shader shaderWhichRenderObject, float *degreToRotateX, float *degreToRotateY, float *degreToRotateZ, float *positionX, float *positionY, float *positionZ);

	void setPosition(glm::vec3 newPosition);
	float getOritation(Rotation rotation);
	void setOrientationDegre(Rotation axlToRotate, float *degreToRotate);
	void scaleBy(glm::vec3 factorToScale);

	glm::vec3 getPosition();
};
#endif // !OBJECT_CLASS_H