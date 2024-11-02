#include "Object.h"

Object::Object(Shader shaderWhichRenderObject, float* degreToRotateX, float* degreToRotateY, float* degreToRotateZ, float* positionX, float* positionY, float* positionZ) /**/
{
	Object::OrientationX_ = *degreToRotateX;
	Object::OrientationY_ = *degreToRotateY;
	Object::OrientationZ_ = *degreToRotateZ;

	Object::PositionX_ = *positionX;
	Object::PositionY_ = *positionY;
	Object::PositionZ_ = *positionZ;

	shaderWhichRenderObject_ID = shaderWhichRenderObject.ID;

	/*glm::mat4 modelPos = glm::mat4(1.0f);
	glm::mat4 modelPos = glm::translate(modelPos, *position);
	Object::modelMatrix = Object::modelMatrix * modelPos;

	glUniformMatrix4fv(glGetUniformLocation(Object::shaderWhichRenderObject_ID, "model"), 1, GL_FALSE, glm::value_ptr(Object::modelMatrix));  // Pošalji model matricu u shader*/
}

void Object::setPosition(glm::vec3 newPosition)
{
	// Kreiraj lokalnu model matricu za piramidu
	glm::mat4 modelPos = glm::mat4(1.0f); // Resetovana matrica
	modelPos = glm::translate(modelPos, Object::Position + newPosition);  // Translacija piramide

	Object::modelMatrix = Object::modelMatrix * modelPos;
	Object::Position = newPosition;

	glUniformMatrix4fv(glGetUniformLocation(Object::shaderWhichRenderObject_ID, "model"), 1, GL_FALSE, glm::value_ptr(Object::modelMatrix));  // Pošalji model matricu u shader
};
void Object::setOrientationDegre(Object::Rotation axlToRotate, float *degreToRotate)
{
	glm::vec3 aroudTheAxle;
	if (axlToRotate == Object::Rotation::X) {
		aroudTheAxle = glm::vec3(1.0f, 0.0f, 0.0f);

		glm::mat4 modelRot = glm::mat4(1.0f);
		glm::mat4 modelPos = glm::mat4(1.0f);
		modelPos = glm::translate(modelPos, -Object::Position);
		modelRot = glm::rotate(modelRot, glm::radians(*degreToRotate), aroudTheAxle);
		modelPos = glm::translate(modelPos, Object::Position);

		Object::modelMatrix = Object::modelMatrix * modelRot;
		Object::OrientationX_ = *degreToRotate;

		glUniformMatrix4fv(glGetUniformLocation(Object::shaderWhichRenderObject_ID, "model"), 1, GL_FALSE, glm::value_ptr(Object::modelMatrix));  // Pošalji model matricu u shader
	}
	else if (axlToRotate == Object::Rotation::Y){
		aroudTheAxle = glm::vec3(0.0f, 1.0f, 0.0f);
		
		glm::mat4 modelRot = glm::mat4(1.0f);
		glm::mat4 modelPos = glm::mat4(1.0f);
		modelPos = glm::translate(modelPos, -Object::Position);
		modelRot = glm::rotate(modelRot, glm::radians(*degreToRotate), aroudTheAxle);
		modelPos = glm::translate(modelPos, Object::Position);

		Object::modelMatrix = Object::modelMatrix * modelRot;
		OrientationY_ = *degreToRotate;

		glUniformMatrix4fv(glGetUniformLocation(Object::shaderWhichRenderObject_ID, "model"), 1, GL_FALSE, glm::value_ptr(Object::modelMatrix));  // Pošalji model matricu u shader
	}
	else if (axlToRotate == Object::Rotation::Z) {
		aroudTheAxle = glm::vec3(0.0f, 0.0f, 1.0f);

		glm::mat4 modelRot = glm::mat4(1.0f);
		glm::mat4 modelPos = glm::mat4(1.0f);
		modelPos = glm::translate(modelPos, -Object::Position);
		modelRot = glm::rotate(modelRot, glm::radians(*degreToRotate), aroudTheAxle);
		modelPos = glm::translate(modelPos, Object::Position);

		Object::modelMatrix = Object::modelMatrix * modelRot;
		OrientationZ_ = *degreToRotate;

		glUniformMatrix4fv(glGetUniformLocation(Object::shaderWhichRenderObject_ID, "model"), 1, GL_FALSE, glm::value_ptr(Object::modelMatrix));  // Pošalji model matricu u shader
	}
};
void Object::scaleBy(glm::vec3 factorToScale)
{
	
};
glm::vec3 inline Object::getPosition()
{
	return Object::Position;
};
float Object::getOritation(Object::Rotation rotationAxl)
{
	if (rotationAxl == Object::Rotation::X) {
		return Object::OrientationX_;
	}
	else if(rotationAxl == Object::Rotation::Y)
	{
		return Object::OrientationY_;
	}
	else if(rotationAxl == Object::Rotation::Z)
	{
		return Object::OrientationZ_;
	}
};