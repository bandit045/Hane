#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Camera.h"


const unsigned int width = 900;
const unsigned int height = 900;

// Vertices coordinates
GLfloat vertices_pyramide[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-0.5f, 0.0f,  0.5f,     1.00f, 0.00f, 0.00f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 1.00f, 0.00f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.00f, 0.00f, 1.00f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     1.00f, 1.00f, 0.00f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 1.70f, 0.00f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.00f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.00f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 1.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     1.83f, 0.70f, 1.00f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.00f, 0.00f, 0.00f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 1.00f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     1.00f, 0.00f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.00f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 1.00f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     1.00f, 0.00f, 0.04f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.00f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};

// Indices for vertices order
GLuint indices_pyramide[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};

// Vertices for cube
GLfloat vertices_cube[] =
{
	// Positions          // Normals (x, y, z)

	// Front face (z = 1.0)
	-1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,  // Bottom-left
	 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  6.0f, 0.0f,  0.0f,  0.0f,  1.0f,  // Bottom-right
	 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  6.0f, 6.0f,  0.0f,  0.0f,  1.0f,  // Top-right
	-1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 6.0f,  0.0f,  0.0f,  1.0f,  // Top-left

	// Back face (z = -1.0)
	-1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,  // Bottom-left
	 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  6.0f, 0.0f,  0.0f,  0.0f, -1.0f,  // Bottom-right
	 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  6.0f, 6.0f,  0.0f,  0.0f, -1.0f,  // Top-right
	-1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 6.0f,  0.0f,  0.0f, -1.0f,  // Top-left

	// Left face (x = -1.0)
	-1.0f, -1.0f, -1.0f, 1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  -1.0f,  0.0f,  0.0f,  // Bottom-left
	-1.0f, -1.0f,  1.0f, 1.0f,  0.0f,  0.0f,  6.0f, 0.0f,  -1.0f,  0.0f,  0.0f,  // Bottom-right
	-1.0f,  1.0f,  1.0f, 1.0f,  0.0f,  0.0f,  6.0f, 6.0f,  -1.0f,  0.0f,  0.0f,  // Top-right
	-1.0f,  1.0f, -1.0f, 1.0f,  0.0f,  0.0f,  0.0f, 6.0f,  -1.0f,  0.0f,  0.0f,  // Top-left

	// Right face (x = 1.0)
	 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,  // Bottom-left
	 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  6.0f, 0.0f,  1.0f,  0.0f,  0.0f,  // Bottom-right
	 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  6.0f, 6.0f,  1.0f,  0.0f,  0.0f,  // Top-right
	 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 6.0f,  1.0f,  0.0f,  0.0f,  // Top-left

	// Top face (y = 1.0)
	-1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,  // Top-left
	 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,  // Top-right
	 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,  // Bottom-right
	-1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,  // Bottom-left

	// Bottom face (y = -1.0)
	-1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,  // Bottom-left
	 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  6.0f, 0.0f,  0.0f, -1.0f,  0.0f,  // Bottom-right
	 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  6.0f, 6.0f,  0.0f, -1.0f,  0.0f,  // Top-right
	-1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 6.0f,  0.0f, -1.0f,  0.0f   // Top-left
};

// Indices for cube
GLuint indices_cube[] =
{
	// Front face
	0, 1, 2,  2, 3, 0,

	// Back face
	4, 5, 6,  6, 7, 4,

	// Left face
	8, 9, 10,  10, 11, 8,

	// Right face
	12, 13, 14,  14, 15, 12,

	// Top face
	16, 17, 18,  18, 19, 16,

	// Bottom face
	20, 21, 22,  22, 23, 20
};

 // Vertices for Light source  
GLfloat vertices_lightSource[] =
{
		// Prednja strana
		-0.01f, -0.01f,  0.01f,
		 0.01f, -0.01f,  0.01f,
		 0.01f,  0.01f,  0.01f,
		 0.01f,  0.01f,  0.01f,
		-0.01f,  0.01f,  0.01f,
		-0.01f, -0.01f,  0.01f,

		// Zadnja strana
		-0.01f, -0.01f, -0.01f,
		 0.01f, -0.01f, -0.01f,
		 0.01f,  0.01f, -0.01f,
		 0.01f,  0.01f, -0.01f,
		-0.01f,  0.01f, -0.01f,
		-0.01f, -0.01f, -0.01f,

		// Leva strana
		-0.01f,  0.01f,  0.01f,
		-0.01f,  0.01f, -0.01f,
		-0.01f, -0.01f, -0.01f,
		-0.01f, -0.01f, -0.01f,
		-0.01f, -0.01f,  0.01f,
		-0.01f,  0.01f,  0.01f,

		// Desna strana
		 0.01f,  0.01f,  0.01f,
		 0.01f,  0.01f, -0.01f,
		 0.01f, -0.01f, -0.01f,
		 0.01f, -0.01f, -0.01f,
		 0.01f, -0.01f,  0.01f,
		 0.01f,  0.01f,  0.01f,

		 // Donja strana
		 -0.01f, -0.01f, -0.01f,
		  0.01f, -0.01f, -0.01f,
		  0.01f, -0.01f,  0.01f,
		  0.01f, -0.01f,  0.01f,
		 -0.01f, -0.01f,  0.01f,
		 -0.01f, -0.01f, -0.01f,

		 // Gornja strana
		 -0.01f,  0.01f, -0.01f,
		  0.01f,  0.01f, -0.01f,
		  0.01f,  0.01f,  0.01f,
		  0.01f,  0.01f,  0.01f,
		 -0.01f,  0.01f,  0.01f,
		 -0.01f,  0.01f, -0.01f
};

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "Hello World!"
	GLFWwindow* window = glfwCreateWindow(width, height, "Hello World!", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL) {

		std::cout << "Failed to create window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	//Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0,0, width, height);

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgramForObjects("default.vert", "default.frag");
	Shader lightSourceShader("lightingSourceShader.vert", "lightingSourceShader.frag");
//---------------------------------------------------------------------------------------------------------------------------------------
	// Generates Vertex Array Object and binds it
	VAO TRIANGLE_SHAPE_VAO;
	TRIANGLE_SHAPE_VAO.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO TRIANGLE_SHAPE_VBO(vertices_pyramide, sizeof(vertices_pyramide));
	// Generates Element Buffer Object and links it to indices
	EBO TRIANGLE_SHAPE_EBO(indices_pyramide, sizeof(indices_pyramide));

	// Links VBO attributes such as cordinates and colors to VAO
	TRIANGLE_SHAPE_VAO.LinkAttrib(TRIANGLE_SHAPE_VBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	TRIANGLE_SHAPE_VAO.LinkAttrib(TRIANGLE_SHAPE_VBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	TRIANGLE_SHAPE_VAO.LinkAttrib(TRIANGLE_SHAPE_VBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	TRIANGLE_SHAPE_VAO.LinkAttrib(TRIANGLE_SHAPE_VBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	TRIANGLE_SHAPE_VAO.Unbind();
	TRIANGLE_SHAPE_VBO.Unbind();
	TRIANGLE_SHAPE_EBO.Unbind();
//----------------------------------------------------------------------------------------------------------------------------------------
	// Generates Vertex Array Object and binds it
	VAO CUBE_SHAPE_VAO;
	CUBE_SHAPE_VAO.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO CUBE_SHAPE_VBO(vertices_cube, sizeof(vertices_cube));
	// Generates Element Buffer Object and links it to indices
	EBO CUBE_SHAPE_EBO(indices_cube, sizeof(indices_cube));

	// Links VBO attributes such as cordinates and colors to VAO
	CUBE_SHAPE_VAO.LinkAttrib(CUBE_SHAPE_VBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);              
	CUBE_SHAPE_VAO.LinkAttrib(CUBE_SHAPE_VBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	CUBE_SHAPE_VAO.LinkAttrib(CUBE_SHAPE_VBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	CUBE_SHAPE_VAO.LinkAttrib(CUBE_SHAPE_VBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	CUBE_SHAPE_VAO.Unbind();
	CUBE_SHAPE_VBO.Unbind();
	CUBE_SHAPE_EBO.Unbind();
//----------------------------------------------------------------------------------------------------------------------------------------
	// Generates Vertex Array Object and binds it
	VAO LIGHT_SOURCE_VAO;
	LIGHT_SOURCE_VAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO LIGHT_SOURCE_VBO(vertices_lightSource, sizeof(vertices_lightSource));

	// Links VBO attributes such as cordinates to VAO
	LIGHT_SOURCE_VAO.LinkAttrib(LIGHT_SOURCE_VBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	// Unbind all to prevent accidentally modifying them
	LIGHT_SOURCE_VAO.Unbind();
	LIGHT_SOURCE_VBO.Unbind();

	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
	glm::vec3 positionOfLightSource(1.0f, 1.0f, 1.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, positionOfLightSource);

	glm::vec3 pyramideColor(1.0f, 1.0f, 1.0f);
	glm::vec3 pyramidPos = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	glm::vec3 cubeColor(1.0f, 1.0f, 1.0f);
	glm::vec3 cubePos = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::mat4 cubeModel = glm::mat4(1.0f);
	cubeModel = glm::translate(cubeModel, cubePos);

	lightSourceShader.Activate();
	glUniformMatrix4fv(glGetAttribLocation(lightSourceShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform3f(glGetUniformLocation(lightSourceShader.ID, "lightColor"), lightColor.r, lightColor.g, lightColor.b);
	shaderProgramForObjects.Activate();
	glUniform3f(glGetUniformLocation(shaderProgramForObjects.ID, "lightColor"), lightColor.r, lightColor.g, lightColor.b);
	glUniform3f(glGetUniformLocation(shaderProgramForObjects.ID, "objectColor"), pyramideColor.r, pyramideColor.g, pyramideColor.b);
	glUniformMatrix4fv(glGetAttribLocation(shaderProgramForObjects.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));

	// Textures
	Texture popCat("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgramForObjects, "tex0", 0);

	// Enable the depth buffer
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 2.0f, 5.0f));

	// Main while loop
	while(!glfwWindowShouldClose(window))
	{	
		// Setting rendering mode to line
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// Specify the color of the background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Handling input to move camera, light positon ond light color
		camera.Inputs(window, lightColor, positionOfLightSource);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateCameraMatrix(45.0f, 0.1f, 100.0f);

		{
			// Tell OpenGL which Shader Program we want to use 
			shaderProgramForObjects.Activate();

			// Exports the camera Position to the Fragment Shader for specular lighting
			glUniform3f(glGetUniformLocation(shaderProgramForObjects.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
			// Export the camMatrix to the Vertex Shader of the pyramid
			camera.sendCamMatrixToShader(shaderProgramForObjects, "camMatrix");

			// Exprort light position for dynamic light
			glUniform3f(glGetUniformLocation(shaderProgramForObjects.ID, "lightPos"), positionOfLightSource.x, positionOfLightSource.y, positionOfLightSource.z);

			// Binding texture so its appear at render
			popCat.Bind();

			// Kreiraj lokalnu model matricu za piramidu
			glm::mat4 pyramidModel = glm::mat4(1.0f); // Resetovana matrica
			pyramidModel = glm::translate(pyramidModel, glm::vec3(2.0f, 1.0f, 1.0f));;  // Translacija piramide
			shaderProgramForObjects.sendMat4x4ToShader("model", pyramidModel);  // Pošalji model matricu u shader

			// Bind the VAO so OpenGL knows to use it
			TRIANGLE_SHAPE_VAO.Bind();
			// Draw the pyramid using the GL_TRIANGLES primitive
			glDrawElements(GL_TRIANGLES, sizeof(indices_pyramide) / sizeof(int), GL_UNSIGNED_INT, 0);
			// Unbind texture
			popCat.Unbind();
		}
		{
			// Activating shader that is used only for objects
			shaderProgramForObjects.Activate();
			// Export the camMatrix to the Vertex Shader of the cube
			camera.sendCamMatrixToShader(shaderProgramForObjects, "camMatrix");

			// Binding texture so its appear at render
			popCat.Bind();

			// Kreiraj lokalnu model matricu za kocku
			glm::mat4 cubeModel = glm::mat4(1.0f);  // Resetovana matrica
			cubeModel = glm::translate(cubeModel, glm::vec3(10.0f, 1.0f, 1.0f)); // Transplantacija kocke
			shaderProgramForObjects.sendMat4x4ToShader("model", cubeModel);  // Pošalji model matricu u shader

			// Bind the VAO so OpenGL knows to use it
			CUBE_SHAPE_VAO.Bind();
			// Draw the pyramid using the GL_TRIANGLES primitive
			glDrawElements(GL_TRIANGLES, sizeof(indices_cube) / sizeof(int), GL_UNSIGNED_INT, 0);
			// Unbind texture
			popCat.Unbind();
		}
		{
			// Activating shader that is used only for lightSource
			lightSourceShader.Activate();

			// Kreiraj lokalnu model matricu za svetlosni izvor
			glm::mat4 lightModel = glm::mat4(1.0f); // Resetovana matrica
			lightModel = glm::translate(lightModel, positionOfLightSource); // Translantacija svetla
			lightSourceShader.sendMat4x4ToShader("model", lightModel);  // Pošalji model matricu u shader

			// Passing camMatrix in uniform to lightSourceCube in shader for projection matrix
			camera.sendCamMatrixToShader(lightSourceShader, "camMatrix");

			// We setting up which is the color of lightSource cube
			lightSourceShader.sendVec3ToShader("lightColor", lightColor);

			// Binding light source vao in order to draws it
			LIGHT_SOURCE_VAO.Bind();
			// Draw light source cube using DrawArrays no-index(EBO)
			glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices_lightSource) / sizeof(float));
		}

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	TRIANGLE_SHAPE_VAO.Delete();
	TRIANGLE_SHAPE_VBO.Delete();
	TRIANGLE_SHAPE_EBO.Delete();
	LIGHT_SOURCE_VAO.Delete();
	LIGHT_SOURCE_VBO.Delete();
	popCat.Delete();
	shaderProgramForObjects.Delete();
	lightSourceShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
