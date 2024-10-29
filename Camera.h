#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shaderClass.h"

class Camera
{
public:
	// Stores the main vectors of the camera
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	// Preventing the camera from jumpping around when first clicking left click
	bool firstClick = true;

	// Stores width and height of window
	int width;
	int height;

	float speed = 0.1f;
	float sensitivity = 100.0f;

	// Camera constructor to set up variables and initialization
	Camera(int width, int height, glm::vec3 position);

	// Updates the camera matrix to the Vertex Shader
	void updateCameraMatrix(float FOVdeg, float nearPlane, float farPlane);
	// Exports the camera matrix to a shader
	void sendCamMatrixToShader(Shader& shader, const char* uniform);
	// Scale object works only on 0,0,0
	void scaleObjectWithModelMatrix(glm::vec3 factorToScale, glm::vec3 curcurentPosition);
	// Translate object
	void translateObjectWithModelMatrih(glm::vec3 newPosition, glm::mat4 model);
	// Handles camera inputs
	void Inputs(GLFWwindow* window, glm::vec3& lightColor, glm::vec3& positionOfLightSource, bool& blinn, bool& specularMap_Switch);

	// Getters
	glm::mat4 getModelMatrix();
	glm::mat4 getCameraMatrix();
};
#endif