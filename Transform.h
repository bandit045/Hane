#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "MenageShaders.h"

struct TransformParameters {
	glm::vec3 m_objectPos = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 m_objectRotEuler = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::quat m_objectRotQuat = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	glm::vec3 m_objectScale = glm::vec3(1.0f, 1.0f, 1.0f);
};

class Transform{
public:
	Transform(GLuint shaderProgramID);
	Transform();

	// Setters
	void setPosition(glm::vec3 newPosition);
	void setScale(glm::vec3 newScale);
	void setRotateEuler(glm::vec3 newRotationEuler);
	void setRotateQuat(glm::quat newOrientationQuat);
	void inputs(GLFWwindow* window);
	// Getters
	GLuint getShaderID();
	TransformParameters& transformParams();
	static Transform getDefaultTransform();

	
private:
	GLuint m_shader;
	TransformParameters transformParameters;

	// Matrix model
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	// Matrix model for transformation
	glm::mat4 modelPos = glm::mat4(1.0f);
	glm::mat4 modelRotate = glm::mat4(1.0f);
	glm::mat4 modelScale = glm::mat4(1.0f);
};

#endif // !TRANSFORM_H