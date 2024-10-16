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

// Verteces cordinates
GLfloat vertices[] =
{
//  |      CORDINATES           |           COLOR          |   TEX-CORD    |
	-0.5f,  0.0f,  0.5f,         1.0f,  0.0f,  0.0f,        0.0f, 0.0f,  // 0 red
	 0.0f,  1.0f,  0.0f,         0.0f,  1.0f,  0.0f,        2.5f, 5.0f,  // 1 green
	-0.5f,  0.0f, -0.5f,         0.0f,  0.0f,  1.0f,        5.0f, 0.0f,  // 2 blue
	 0.5f,  0.0f,  0.5f,         1.0f,  1.0f,  1.0f,        5.0f, 0.0f,  // 3 white quad
	 0.5f,  0.0f, -0.5f,         0.0f,  0.0f,  0.0f,        0.0f, 0.0f   // 4 black quad
};

// Indices for verteces order
GLuint indices[] =
{
	0, 3, 1,
	0, 1, 2,
	2, 4, 1,
	4, 1, 3,
	4, 3, 2,
	0, 2, 3,
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
	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as cordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Textures
	Texture popCat("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);
	
	// Enable the depth buffer
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Main while loop
	while(!glfwWindowShouldClose(window))
	{	
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// Specify the color of the background
		glClearColor(0.8f, 0.1f, 0.7f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use 
		shaderProgram.Activate();
				
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
				
		// Binding texture so its appear at render
		popCat.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	popCat.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
