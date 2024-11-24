#include "Transform.h"

TransformObject::TransformObject(Shader shaderProgram)
{
	setScale(transformParameters.m_objectScale);
	setRotateEuler(transformParameters.m_objectRotEuler);
	setPosition(transformParameters.m_objectPos);
	shaderID = shaderProgram.ID;
}
TransformObject::TransformObject()
{
	shaderID = -1; // !!!!!!!!!!!!!!!!
};
void TransformObject::setPosition(const glm::vec3& newPosition)
{
	glm::mat4 matrixPos = glm::mat4(1.0f);
	matrixPos = glm::translate(matrixPos, newPosition);

	// We update our position insde Object class 
	transformParameters.m_objectPos = newPosition;

	// We update our modelPos inside Object Class
	modelPos = matrixPos;

	glUniformMatrix4fv(glGetUniformLocation(shaderID, "modelPos"), 1, GL_FALSE, glm::value_ptr(modelPos));
}
void TransformObject::setScale(const glm::vec3& newScale)
{
	glm::mat4 matrixScale = glm::mat4(1.0f);
	matrixScale = glm::scale(matrixScale, newScale);

	// We update our scaling factor to Object Class
	transformParameters.m_objectScale = newScale;

	// We update our modelScale inside Object Class
	modelScale = matrixScale;

	glUniformMatrix4fv(glGetUniformLocation(shaderID, "modelScale"), 1, GL_FALSE, glm::value_ptr(modelScale));
}
void TransformObject::setRotateEuler(const glm::vec3& newRotationEuler)
{
	// Apply rotations around each axis (in the order X, Y, Z)
	glm::mat3 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(newRotationEuler.x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat3 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(newRotationEuler.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat3 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(newRotationEuler.z), glm::vec3(0.0f, 0.0f, 1.0f));

	// We set our curent euar inside class
	transformParameters.m_objectRotEuler = newRotationEuler;

	// We update our modelRotate inside Object Class
	modelRotate = modelRotate * glm::mat4(rotationZ * rotationY * rotationX);

	glUniformMatrix4fv(glGetUniformLocation(shaderID, "modelRotate"), 1, GL_FALSE, glm::value_ptr(modelRotate));
}
void TransformObject::setRotateQuat(const glm::quat& newOrientationQuat) // This type of rotation solve gimbal lock
{
	// We define axis for rotation
	glm::vec3 axis(1.0f, 1.0f, 1.0f);
	glm::quat quatRot_local_rotation;
	glm::quat quatRot_total(1.0f, 0.0f, 0.0f, 0.0f);

	// Black magic
	quatRot_local_rotation.w = cosf(newOrientationQuat.w / 2);
	quatRot_local_rotation.x = axis.x * sinf(glm::radians(newOrientationQuat.x) / 2);
	quatRot_local_rotation.y = axis.y * sinf(glm::radians(newOrientationQuat.y) / 2);
	quatRot_local_rotation.z = axis.z * sinf(glm::radians(newOrientationQuat.z) / 2);

	quatRot_local_rotation = glm::normalize(quatRot_local_rotation);

	glm::quat quatRot_total_new = quatRot_local_rotation * quatRot_total;
	modelRotate = glm::mat4_cast(quatRot_total_new);

	transformParameters.m_objectRotQuat = quatRot_local_rotation;

	glUniformMatrix4fv(glGetUniformLocation(shaderID, "modelRotate"), 1, GL_FALSE, glm::value_ptr(modelRotate));
};
void TransformObject::inputs(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			if (transformParameters.m_objectPos.y <= 100.0f)
			{
				transformParameters.m_objectPos.y += 0.01f;
			}
		}
		else
		{
			transformParameters.m_objectPos.y -= 0.01f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			if (transformParameters.m_objectPos.x <= 100.0f)
			{
				transformParameters.m_objectPos.x += 0.01f;
			}
		}
		else
		{
			transformParameters.m_objectPos.x -= 0.01f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			if (transformParameters.m_objectPos.z <= 100.0f) {
				transformParameters.m_objectPos.z += 0.01f;
			}
		}
		else
		{
			transformParameters.m_objectPos.z -= 0.01f;
		}
	}
}

TransformParameters& TransformObject::getTransformParameters()
{
	return transformParameters;
}