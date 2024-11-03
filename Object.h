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
	glm::vec3 Scale;
	
	// Matrix model
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	// Matrixe for transformation
	glm::mat4 modelPos = glm::mat4(1.0f);
	glm::mat4 modelRotate = glm::mat4(1.0f);
	glm::mat4 modelScale = glm::mat4(1.0f);

	float OrientationX_;
	float OrientationY_;
	float OrientationZ_;

	glm::quat orientationQuat;

	float PositionX_;
	float PositionY_;
	float PositionZ_;

	// Which shader renders this object
	GLuint shaderWhichRenderObject_ID;

	// If any transformation is applied
	bool hasAnyTransformApplied = false;

	Object(Shader shaderWhichRenderObject, glm::quat *orientationQuat, float *degreToRotateX, float *degreToRotateY, float *degreToRotateZ, float *positionX, float *positionY, float *positionZ);

	// This ones most used
	void setPosition(glm::vec3 newPosition);
	void scaleObject(glm::vec3 scaleFactor);
	void rotateObject(float axisX, float axisY, float axisZ);
	
	// Quat rotation
	void rotateQuat(float componentW, float pitchX, float yawY, float rollZ);

	float getOritation(Rotation rotation);
	void setOrientationDegre(Rotation axlToRotate, float *degreToRotate);
};
#endif // !OBJECT_CLASS_H