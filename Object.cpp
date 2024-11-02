#include "Object.h"

Object::Object(Shader shaderWhichRenderObject)
{
	shaderWhichRenderObject_ID = shaderWhichRenderObject.ID;
}

void Object::setPosition(glm::vec3 newPosition)
{
	// Kreiraj lokalnu model matricu za piramidu
	glm::mat4 modelPos = glm::mat4(1.0f); // Resetovana matrica
	modelPos = glm::translate(modelPos, Object::Position + newPosition);  // Translacija piramide

	Object::modelMatrix = Object::modelMatrix * modelPos;
	Object::Position = Object::Position + newPosition;

	glUniformMatrix4fv(glGetUniformLocation(Object::shaderWhichRenderObject_ID, "model"), 1, GL_FALSE, glm::value_ptr(Object::modelMatrix));  // Pošalji model matricu u shader
};
void Object::setOrientationDegre(Rotation axlToRotate, float degreToRotate)
{
	glm::vec3 aroudTheAxle;
	if (axlToRotate == Rotation::X) {
		aroudTheAxle = glm::vec3(1.0f, 0.0f, 0.0f);

		glm::mat4 modelRot = glm::mat4(1.0f);
		glm::mat4 modelPos = glm::mat4(1.0f);
		modelPos = glm::translate(modelPos, -Object::Position);
		modelRot = glm::rotate(modelRot, glm::radians((float)degreToRotate), aroudTheAxle);
		modelPos = glm::translate(modelPos, Object::Position);

		Object::modelMatrix = Object::modelMatrix * modelRot;
		Object::OrientationX_ = Object::OrientationX_ + degreToRotate;

		glUniformMatrix4fv(glGetUniformLocation(Object::shaderWhichRenderObject_ID, "model"), 1, GL_FALSE, glm::value_ptr(Object::modelMatrix));  // Pošalji model matricu u shader
	}
	else if (axlToRotate == Rotation::Y){
		aroudTheAxle = glm::vec3(0.0f, 1.0f, 0.0f);
		
		glm::mat4 modelRot = glm::mat4(1.0f);
		glm::mat4 modelPos = glm::mat4(1.0f);
		modelPos = glm::translate(modelPos, -Object::Position);
		modelRot = glm::rotate(modelRot, glm::radians(degreToRotate), aroudTheAxle);
		modelPos = glm::translate(modelPos, Object::Position);

		Object::modelMatrix = Object::modelMatrix * modelRot;
		Object::OrientationY_ = Object::OrientationY_ + degreToRotate;

		glUniformMatrix4fv(glGetUniformLocation(Object::shaderWhichRenderObject_ID, "model"), 1, GL_FALSE, glm::value_ptr(Object::modelMatrix));  // Pošalji model matricu u shader
	}
	else if (axlToRotate == Rotation::Z) {
		aroudTheAxle = glm::vec3(0.0f, 0.0f, 1.0f);

		glm::mat4 modelRot = glm::mat4(1.0f);
		glm::mat4 modelPos = glm::mat4(1.0f);
		modelPos = glm::translate(modelPos, -Object::Position);
		modelRot = glm::rotate(modelRot, glm::radians(degreToRotate), aroudTheAxle);
		modelPos = glm::translate(modelPos, Object::Position);

		Object::modelMatrix = Object::modelMatrix * modelRot;
		Object::OrientationZ_ = Object::OrientationZ_ + degreToRotate;

		glUniformMatrix4fv(glGetUniformLocation(Object::shaderWhichRenderObject_ID, "model"), 1, GL_FALSE, glm::value_ptr(Object::modelMatrix));  // Pošalji model matricu u shader
	}
};
void Object::scaleBy(glm::vec3 factorToScale)
{
	
};

glm::vec3 Object::getPosition()
{
	return Object::Position;
};
float Object::getOritation(Rotation rotationAxl)
{
	if (rotationAxl == Rotation::X) {
		return Object::OrientationX_;
	}
	else if(rotationAxl == Rotation::Y)
	{
		return Object::OrientationY_;
	}
	else if(rotationAxl == Rotation::Z)
	{
		return Object::OrientationZ_;
	}
};