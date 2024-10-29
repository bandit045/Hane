#include"Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::updateCameraMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right side
	view = glm::lookAt(Position, Position + Orientation, Up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / (float)height, nearPlane, farPlane);

	cameraMatrix = projection * view;
}

void Camera::sendCamMatrixToShader(Shader& shader, const char* uniform)
{
	// Exports camera matrix to shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

// Works only in centre 0,0,0
void Camera::scaleObjectWithModelMatrix(glm::vec3 factorToScale, glm::vec3 curcurentPosition)
{
	glm::mat4 model = glm::mat4(1.0f);

	// Step 1: Translate the object to the origin (reverse translation)
	model = glm::translate(model, -curcurentPosition);

	// Step 2: Apply the scaling (scale only the size)
	model = glm::scale(model, factorToScale);

	// Step 3: Translate the object back to its original position
	model = glm::translate(model, curcurentPosition);
}

void Camera::translateObjectWithModelMatrih(glm::vec3 newPosition, glm::mat4 model)
{
	// Pravi lokalnu kopiju model matrice
	glm::mat4 localModel = model;  
	// Primeni translaciju
	localModel = glm::translate(localModel, newPosition);  

	// Kombinuj lokalnu model matricu sa kamerom samo za trenutni objekt
	cameraMatrix = cameraMatrix * localModel;
}

glm::mat4 Camera::getModelMatrix()
{
	return modelMatrix;
}

glm::mat4 Camera::getCameraMatrix()
{
	return Camera::cameraMatrix;
}

void Camera::Inputs(GLFWwindow* window, glm::vec3& lightColor, glm::vec3& positionOfLightSource, bool& blinn, bool& specularMap_Switch)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up;
	}
	/*if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * -Up;
	}*/
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.1f;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) != GLFW_PRESS)
	{
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			if (firstClick)
			{
				glfwSetCursorPos(window, (width / 2), (height / 2));
				firstClick = false;
			}

			double mouseX;
			double mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			float rotx = sensitivity * (float)(mouseY - (height / 2)) / height;
			float roty = sensitivity * (float)(mouseX - (width / 2)) / width;

			glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotx), glm::normalize(glm::cross(Orientation, Up)));

			if (!((glm::angle(newOrientation, Up) <= glm::radians(5.0f)) or (glm::angle(newOrientation, -Up) <= glm::radians(5.0f))));
			{
				Orientation = newOrientation;
			}

			Orientation = glm::rotate(Orientation, glm::radians(-roty), Up);

			glfwSetCursorPos(window, (width / 2), (height / 2));
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			if (lightColor.r < 1.0f)
			{
				lightColor.r += 0.01f;
			}
		}
		else if(lightColor.r > 0.01f)
		{
			lightColor.r -= 0.01f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{
		if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			if (lightColor.g < 1.0f)
			{
				lightColor.g += 0.01f;
			}
		}
		else if(lightColor.g > 0.01f)
		{
			lightColor.g -= 0.01f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
	{
		if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			if (lightColor.b < 1.0f) {
				lightColor.b += 0.01f;
			}
		}
		else if (lightColor.b > 0.01f)
		{
			lightColor.b -= 0.01f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			if (positionOfLightSource.y <= 100.0f)
			{
				positionOfLightSource.y += 0.01f;
			}
		}
		else
		{
			positionOfLightSource.y -= 0.01f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			if (positionOfLightSource.x <= 100.0f)
			{
				positionOfLightSource.x += 0.01f;
			}
		}
		else
		{
			positionOfLightSource.x -= 0.01f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			if (positionOfLightSource.z <= 100.0f) {
				positionOfLightSource.z += 0.01f;
			}
		}
		else
		{
			positionOfLightSource.z -= 0.01f;
		}
	}

	// Blinn-phong switch
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		blinn = false;
	}

	// Phong switch
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
		blinn = true;
	}

	// Specular Map switch
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
	{
		specularMap_Switch = true;
	}

	// Specular Map switch
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
	{
		specularMap_Switch = false;
	}
}