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

// Verteces cordinates for triangle
GLfloat vertices_triangle[] =
{
//  |      CORDINATES         |           COLOR          |   TEX-CORD    |
	-0.5f,  0.0f,  0.5f,         1.0f,  0.0f,  0.0f,        0.0f, 0.0f,  // 0 red
	 0.0f,  1.0f,  0.0f,         0.0f,  1.0f,  0.0f,        2.5f, 5.0f,  // 1 green
	-0.5f,  0.0f, -0.5f,         0.0f,  0.0f,  1.0f,        5.0f, 0.0f,  // 2 blue
	 0.5f,  0.0f,  0.5f,         1.0f,  1.0f,  1.0f,        5.0f, 0.0f,  // 3 white quad
	 0.5f,  0.0f, -0.5f,         0.0f,  0.0f,  0.0f,        0.0f, 0.0f   // 4 black quad
};

// Indices for verteces order
GLuint indices_triangle[] =
{
	0, 3, 1,
	0, 1, 2, 
	2, 4, 1,
	4, 1, 3,
	4, 3, 2,
	0, 2, 3,
};

 // Vertices for Light source  
GLfloat vertices_lightSource[] =
{
		// Prednja strana
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		// Zadnja strana
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		// Leva strana
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		// Desna strana
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		 // Donja strana
		 -0.5f, -0.5f, -0.5f,
		  0.5f, -0.5f, -0.5f,
		  0.5f, -0.5f,  0.5f,
		  0.5f, -0.5f,  0.5f,
		 -0.5f, -0.5f,  0.5f,
		 -0.5f, -0.5f, -0.5f,

		 // Gornja strana
		 -0.5f,  0.5f, -0.5f,
		  0.5f,  0.5f, -0.5f,
		  0.5f,  0.5f,  0.5f,
		  0.5f,  0.5f,  0.5f,
		 -0.5f,  0.5f,  0.5f,
		 -0.5f,  0.5f, -0.5f
};

glm::vec3 lightColor(1.0f, 0.0f, 0.0f);
glm::vec3 positionOfLightSource(7.0f, 10.0f, 1.0f);

glm::vec3 objectColor(1.0f, 1.0f, 1.0f);

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

	// Generates Vertex Array Object and binds it
	VAO TRIANGLE_SHAPE_VAO;
	TRIANGLE_SHAPE_VAO.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO TRIANGLE_SHAPE_VBO(vertices_triangle, sizeof(vertices_triangle));
	// Generates Element Buffer Object and links it to indices
	EBO TRIANGLE_SHAPE_EBO(indices_triangle, sizeof(indices_triangle));

	// Links VBO attributes such as cordinates and colors to VAO
	TRIANGLE_SHAPE_VAO.LinkAttrib(TRIANGLE_SHAPE_VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	TRIANGLE_SHAPE_VAO.LinkAttrib(TRIANGLE_SHAPE_VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	TRIANGLE_SHAPE_VAO.LinkAttrib(TRIANGLE_SHAPE_VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	TRIANGLE_SHAPE_VAO.Unbind();
	TRIANGLE_SHAPE_VBO.Unbind();
	TRIANGLE_SHAPE_EBO.Unbind();

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

	// Textures
	Texture popCat("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgramForObjects, "tex0", 0);
	
	// Enable the depth buffer
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Main while loop
	while(!glfwWindowShouldClose(window))
	{	
		// Setting rendering mode to line
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// Specify the color of the background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Handling input to move camera
		camera.Inputs(window);
		{
			// Tell OpenGL which Shader Program we want to use 
			shaderProgramForObjects.Activate();

			camera.updateCameraMatrix(45.0f, 0.1f, 100.0f);
			camera.sendMatrixToShader(shaderProgramForObjects, "camMatrix");
			shaderProgramForObjects.sendVec3ToShader("lightColor", lightColor);
			shaderProgramForObjects.sendVec3ToShader("objectColor", objectColor);

			// Binding texture so its appear at render
			popCat.Bind();
			// Bind the VAO so OpenGL knows to use it
			TRIANGLE_SHAPE_VAO.Bind();
			// Draw the pyramid using the GL_TRIANGLES primitive
			glDrawElements(GL_TRIANGLES, sizeof(indices_triangle) / sizeof(int), GL_UNSIGNED_INT, 0);
		}
		{
			// Activating shader that is used only for lightSource
			lightSourceShader.Activate();

			// Passing camMatrix in uniform to lightSourceCube in shader for projection matrix
			camera.updateCameraMatrix(45.0f, 0.1f, 100.0f);
			camera.scaleObjectWithModelMatrix(glm::vec3(0.2f));
			camera.translateObjectWithModelMatrih(positionOfLightSource);
			camera.sendMatrixToShader(lightSourceShader, "camMatrix");

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
