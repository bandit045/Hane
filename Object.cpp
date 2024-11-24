#include "Object.h"

Object::Object(Shader shaderWhichRenderObject, glm::vec3 scaleFactor, glm::quat orientationQuat, glm::vec3 positionObject, glm::vec3 orientationEuler) /**/
{
	// Positions
	Object::m_position = positionObject;
	setPosition(positionObject);

	// Orientation
	Object::m_orientationEuler = orientationEuler;
	Object::m_orientationQuat = orientationQuat;
	setRotateEuler(orientationEuler);

	// Scale
	Object::m_scale = scaleFactor;
	setScale(scaleFactor);

	// Storing shaders
	shaderWhichRenderObject_ID = shaderWhichRenderObject.ID;
}
void Object::setScale(glm::vec3 scaleFactor)
{
	glm::mat4 matrixScale = glm::mat4(1.0f);
	matrixScale = glm::scale(matrixScale, scaleFactor);

	// We update our scaling factor to Object Class
	Object::m_scale = scaleFactor;

	// We update our modelScale inside Object Class
	Object::modelScale = matrixScale;

	glUniformMatrix4fv(glGetUniformLocation(Object::shaderWhichRenderObject_ID, "modelScale"), 1, GL_FALSE, glm::value_ptr(Object::modelScale));
};
void Object::setPosition(glm::vec3 newPosition)
{
	glm::mat4 matrixPos = glm::mat4(1.0f);
	matrixPos = glm::translate(matrixPos, newPosition);

	// We update our position insde Object class 
	Object::m_position = newPosition;

	// We update our modelPos inside Object Class
	Object::modelPos = matrixPos;

	glUniformMatrix4fv(glGetUniformLocation(Object::shaderWhichRenderObject_ID, "modelPos"), 1, GL_FALSE, glm::value_ptr(Object::modelPos));
};
void Object::setRotateEuler(glm::vec3 rotationEuler)
{
	// Apply rotations around each axis (in the order X, Y, Z)
	glm::mat3 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(rotationEuler.x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat3 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(rotationEuler.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat3 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotationEuler.z), glm::vec3(0.0f, 0.0f, 1.0f));

	// We set our curent euar inside class
	Object::m_orientationEuler = rotationEuler;

	// We update our modelRotate inside Object Class
	Object::modelRotate = Object::modelRotate * glm::mat4(rotationZ * rotationY * rotationX);

	glUniformMatrix4fv(glGetUniformLocation(Object::shaderWhichRenderObject_ID, "modelRotate"), 1, GL_FALSE, glm::value_ptr(Object::modelRotate));
};
void Object::setRotateQuat(glm::quat orientationQuat) // This type of rotation solve gimbal lock
{
	// We define axis for rotation
	glm::vec3 axis(1.0f, 1.0f, 1.0f);
	glm::quat quatRot_local_rotation;
	glm::quat quatRot_total(1.0f, 0.0f, 0.0f, 0.0f);

	// Black magic
 	quatRot_local_rotation.w = cosf(orientationQuat.w / 2);
	quatRot_local_rotation.x = axis.x * sinf(glm::radians(orientationQuat.x) / 2);
	quatRot_local_rotation.y = axis.y * sinf(glm::radians(orientationQuat.y) / 2 );
	quatRot_local_rotation.z = axis.z * sinf(glm::radians(orientationQuat.z) / 2);

	quatRot_local_rotation = glm::normalize(quatRot_local_rotation);

	glm::quat quatRot_total_new = quatRot_local_rotation * quatRot_total;
	Object::modelRotate = glm::mat4_cast(quatRot_total_new);
	
	Object::m_orientationQuat = quatRot_local_rotation;

	glUniformMatrix4fv(glGetUniformLocation(Object::shaderWhichRenderObject_ID, "modelRotate"), 1, GL_FALSE, glm::value_ptr(Object::modelRotate));
};
float Object::getOritationEuler(Object::Rotation rotationAxl) 
{
	if (rotationAxl == Object::Rotation::X) {
		return Object::m_orientationEuler.x;
	}
	else if(rotationAxl == Object::Rotation::Y)
	{
		return Object::m_orientationEuler.y;
	}
	else if(rotationAxl == Object::Rotation::Z)
	{
		return Object::m_orientationEuler.z;
	}
};