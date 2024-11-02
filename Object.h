#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"

enum class Rotation {
	X,
	Y,
	Z,
};

class Object{
public:

	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	float OrientationX_ = 0.0f;
	float OrientationY_ = 0.0f;
	float OrientationZ_ = 0.0f;

	// Which shader renders this object
	GLuint shaderWhichRenderObject_ID;

	// If any transformation is applied
	bool hasAnyTransformApplied = false;

	Object(Shader shaderWhichRenderObject);

	void setPosition(glm::vec3 newPosition);
	float getOritation(Rotation rotation);
	void setOrientationDegre(Rotation aroudTheAxle, float degreToRotate);
	void scaleBy(glm::vec3 factorToScale);

	glm::vec3 getPosition();
	glm::vec3 getScale();

};
#endif // !OBJECT_CLASS_H