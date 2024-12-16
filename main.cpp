#include <iostream>
#include <vector>
#include <unordered_map>
#include <variant>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "GLErrorHandle.h"

#include "Texture.h"
#include "Shader.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Camera.h"
#include "Object.h"
#include "GUI.h"
#include "Light.h"
#include "Transform.h"
#include "MenageShaders.h"
#include "Importer.h"
#include "UnifformBufferObject.h"
#include "RenderFlags.h"
#include "Material.h"
#include "Face.h" // Only triangle
#include "Mesh.h"

const unsigned int width = 1920;
const unsigned int height = 1080;

float repeat_time_cube = 2.0f;
float repeat_time_cube_top = 8.0f;

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
	// Positions     // Normals      // Texture-cordinates(x, y)    // Colors

	// Front face (z = 1.0)
	-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,  // Bottom-left
	 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  2.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,  // Bottom-right
	 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  2.0f,  2.0f,  1.0f,  0.0f,  0.0f, 1.0f,  // Top-right
	-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  2.0f,  1.0f,  0.0f,  0.0f, 1.0f,  // Top-left
																				
	// Back face (z = -1.0)														
	-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, // Bottom-left
	 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  2.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, // Bottom-right
	 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  2.0f, 2.0f,  1.0f,  0.0f,  0.0f, 1.0f, // Top-right
	-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 2.0f,  1.0f,  0.0f,  0.0f, 1.0f, // Top-left
																				
	// Left face (x = -1.0)														
	-1.0f, -1.0f, -1.0f,  -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f, 1.0f, // Bottom-left
	-1.0f, -1.0f,  1.0f,  -1.0f,  0.0f,  0.0f,  2.0f, 0.0f, 1.0f,  0.0f,  0.0f, 1.0f, // Bottom-right
	-1.0f,  1.0f,  1.0f,  -1.0f,  0.0f,  0.0f,  2.0f, 2.0f, 1.0f,  0.0f,  0.0f, 1.0f, // Top-right
	-1.0f,  1.0f, -1.0f,  -1.0f,  0.0f,  0.0f,  0.0f, 2.0f, 1.0f,  0.0f,  0.0f, 1.0f, // Top-left
																				
	// Right face (x = 1.0)														
	 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, // Bottom-left
	 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  2.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, // Bottom-right
	 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  2.0f, 2.0f,  1.0f,  0.0f,  0.0f, 1.0f, // Top-right
	 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 2.0f,  1.0f,  0.0f,  0.0f, 1.0f, // Top-left
																				
	// Top face (y = 1.0)														
	-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 8.0f,  1.0f,  0.0f,  0.0f, 1.0f, // Top-left
	 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  8.0f, 8.0f,  1.0f,  0.0f,  0.0f, 1.0f, // Top-right
	 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  8.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, // Bottom-right
	-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, // Bottom-left
																				
	// Bottom face (y = -1.0)													
	-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, // Bottom-left
	 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  2.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, // Bottom-right
	 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  2.0f, 2.0f,  1.0f,  0.0f,  0.0f, 1.0f, // Top-right
	-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f, 2.0f,  1.0f,  0.0f,  0.0f, 1.0f, // Top-left
};

// Indices for cube
std::vector<EBO::OrderOfRendering> indices_cube=
{
	// Front face
	EBO::OrderOfRendering{0, 1, 2},  EBO::OrderOfRendering{2, 3, 0},
	
	// Back face
	EBO::OrderOfRendering{5, 4, 6},  EBO::OrderOfRendering{7, 6, 4},
	
	// Left face
	EBO::OrderOfRendering{8, 9, 10},  EBO::OrderOfRendering{10, 11, 8},
	
	// Right face
	EBO::OrderOfRendering{12, 14, 13}, EBO::OrderOfRendering{15, 14, 12},
	
	// Top face
	EBO::OrderOfRendering{17, 16, 18},  EBO::OrderOfRendering{18, 16, 19},
	
	// Bottom face
	EBO::OrderOfRendering{20, 21, 22},  EBO::OrderOfRendering{22, 23, 20}
};

// Vertices for Light source  
GLfloat vertices_lightSource[] =
{
	 // Prednja strana
		-0.01f, -0.01f,  0.01f, 0.0f, 0.0f, 1.0f,
		 0.01f, -0.01f,  0.01f, 0.0f, 0.0f, 1.0f,
		 0.01f,  0.01f,  0.01f, 0.0f, 0.0f, 1.0f,

		 0.01f,  0.01f,  0.01f, 0.0f, 0.0f, 1.0f,
		-0.01f,  0.01f,  0.01f, 0.0f, 0.0f, 1.0f,
		-0.01f, -0.01f,  0.01f, 0.0f, 0.0f, 1.0f,

		// Zadnja strana
		-0.01f, -0.01f, -0.01f, 0.0f, 0.0f, -1.0f,
		 0.01f,  0.01f, -0.01f, 0.0f, 0.0f, -1.0f,
		 0.01f, -0.01f, -0.01f, 0.0f, 0.0f, -1.0f,

		 0.01f,  0.01f, -0.01f, 0.0f, 0.0f, -1.0f,
		-0.01f, -0.01f, -0.01f, 0.0f, 0.0f, -1.0f,
		-0.01f,  0.01f, -0.01f, 0.0f, 0.0f, -1.0f,

		// Leva strana
		-0.01f,  0.01f,  0.01f, -1.0f, 0.0f, 0.0f,
		-0.01f, -0.01f, -0.01f, -1.0f, 0.0f, 0.0f,
		-0.01f,  0.01f, -0.01f, -1.0f, 0.0f, 0.0f,

		-0.01f, -0.01f, -0.01f, -1.0f, 0.0f, 0.0f,
		-0.01f,  0.01f,  0.01f, -1.0f, 0.0f, 0.0f,
		-0.01f, -0.01f,  0.01f, -1.0f, 0.0f, 0.0f,

		// Desna strana
		 0.01f,  0.01f,  0.01f, 1.0f, 0.0f, 0.0f,
		 0.01f, -0.01f, -0.01f, 1.0f, 0.0f, 0.0f,
		 0.01f,  0.01f, -0.01f, 1.0f, 0.0f, 0.0f,

		 0.01f, -0.01f, -0.01f, 1.0f, 0.0f, 0.0f,
		 0.01f,  0.01f,  0.01f, 1.0f, 0.0f, 0.0f,
		 0.01f, -0.01f,  0.01f, 1.0f, 0.0f, 0.0f,

		 // Donja strana
		 -0.01f, -0.01f, -0.01f, 0.0f, 1.0f, 0.0f,
		  0.01f, -0.01f,  0.01f, 0.0f, 1.0f, 0.0f,
		  0.01f, -0.01f, -0.01f, 0.0f, 1.0f, 0.0f,

		  0.01f, -0.01f,  0.01f, 0.0f, 1.0f, 0.0f,
		 -0.01f, -0.01f, -0.01f, 0.0f, 1.0f, 0.0f,
		 -0.01f, -0.01f,  0.01f, 0.0f, 1.0f, 0.0f,

		 // Gornja strana
		 
		  0.01f,  0.01f,  0.01f, 0.0f, -1.0f, 0.0f,
		  0.01f,  0.01f, -0.01f, 0.0f, -1.0f, 0.0f,
		 -0.01f,  0.01f, -0.01f, 0.0f, -1.0f, 0.0f,

		 -0.01f,  0.01f,  0.01f, 0.0f, -1.0f, 0.0f,
		  0.01f,  0.01f,  0.01f, 0.0f, -1.0f, 0.0f,
		 -0.01f,  0.01f, -0.01f, 0.0f, -1.0f, 0.0f,
};

std::vector<EBO::OrderOfRendering> indices_class_cube = // This is only GL_TRIANGLE
{
	// Front face
	EBO::OrderOfRendering{1, 0, 2}, EBO::OrderOfRendering{3, 5, 4},/* EBO::OrderOfRendering{1, 2, 3}*/
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
	glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);
	//glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); // Disable Window Decorations
	//glfwWindowHint(GLFW_FLOATING, GLFW_TRUE); // Allow Floating Behavior
	//glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE); // Set Transparent Background

	// Create a GLFWwindow object of 1920 by 1080 pixels, naming it "Hello World!"
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
//-----------------------------------------------------------------------------------------------
	// Inicialize the GUI
	GUI guiWindow = GUI(window); 
//-----------------------------------------------------------------------------------------------
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 1920, y = 1080
	GLCall(glViewport(0,0, width, height));

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgramForObjects("default.vert", "default.frag");
	Shader lightSourceShader("lightingSourceShader.vert", "lightingSourceShader.frag");
	MenageShaders::setDefaultShadersForAllID(shaderProgramForObjects.ID, lightSourceShader.ID);
	//std::cout << "Light Source Shader(how object look): " << MenageShaders::getDefaultShaderID(DefaultShader::FOR_LIGHT);
	//std::cout << "\nShader Program For Objects(how object look): " << MenageShaders::getDefaultShaderID(DefaultShader::FOR_OBJECTS) << "\n";
//------------------------------------------------------------------------------------------------
	// Generates Vertex Array Object and binds it
	VAO TRIANGLE_SHAPE_VAO;
	TRIANGLE_SHAPE_VAO.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO TRIANGLE_SHAPE_VBO(vertices_pyramide, sizeof(vertices_pyramide));
	// Generates Element Buffer Object and links it to indices
	EBO TRIANGLE_SHAPE_EBO(indices_pyramide, sizeof(indices_pyramide));

	// Links VBO attributes such as cordinates and colors to VAO
	TRIANGLE_SHAPE_VAO.LinkAttrib(TRIANGLE_SHAPE_VBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);                   // Cordinates
	TRIANGLE_SHAPE_VAO.LinkAttrib(TRIANGLE_SHAPE_VBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float))); // Color
	TRIANGLE_SHAPE_VAO.LinkAttrib(TRIANGLE_SHAPE_VBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float))); // Texture cords
	TRIANGLE_SHAPE_VAO.LinkAttrib(TRIANGLE_SHAPE_VBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float))); // Normals
	// Unbind all to prevent accidentally modifying them
	TRIANGLE_SHAPE_VAO.Unbind();
	TRIANGLE_SHAPE_VBO.Unbind();
	TRIANGLE_SHAPE_EBO.Unbind();
//----------------------------------------------------------------------------------------------------------------------------------------
	std::vector< glm::vec3 > importVerticesCube;
	std::vector< glm::vec2 > importUvsCube;
	std::vector< glm::vec3 > importNormalsCube;

	// Used for storing EBO cordinates
	std::vector<unsigned int> importCubeIndex;

	// Normal buffer for storing EBO normals
	std::vector<unsigned int> importCubeIndexNormal;

	// We import our vertex model cordinates, uv, normals inside variable that are passed by reference
	Importer::loadOBJ("mesh.obj", importVerticesCube, importUvsCube, importNormalsCube, importCubeIndex, importCubeIndexNormal); // Cordinates, Texture-cords, Normals, EBO

	// Generates Vertex Array Object for file from import and binds it
	VAO IMPORT_CUBE_SHAPE_VAO;
	IMPORT_CUBE_SHAPE_VAO.Bind();

	// Generates Vertex Buffer Object for impport object cube and links it to vertices
	VBO IMPORT_CUBE_SHAPE_VBO_CORDINATES(importVerticesCube, importVerticesCube.size() * sizeof(glm::vec3));
	VBO IMPORT_CUBE_SHAPE_VBO_NORMALS(   importNormalsCube,  importNormalsCube.size() * sizeof(glm::vec3));
	VBO IMPORT_CUBE_SHAPE_VBO_UV(		 importUvsCube,      importUvsCube.size() * sizeof(glm::vec2));
	// Generates Element Buffer Object for imported cube and links it to indices
	EBO IMPORT_CUBE_SHAPE_CORDINATE_EBO(importCubeIndex, importCubeIndex.size() * sizeof(unsigned int));
	
	IMPORT_CUBE_SHAPE_VAO.LinkAttrib(IMPORT_CUBE_SHAPE_VBO_CORDINATES,  0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0); // Cordinates
	IMPORT_CUBE_SHAPE_VAO.LinkAttrib(IMPORT_CUBE_SHAPE_VBO_NORMALS,     1, 3, GL_FLOAT, 3 * sizeof(float), (void*)0); // Normals
	IMPORT_CUBE_SHAPE_VAO.LinkAttrib(IMPORT_CUBE_SHAPE_VBO_UV,          2, 2, GL_FLOAT, 2 * sizeof(float), (void*)0); // Texture cords
	IMPORT_CUBE_SHAPE_VBO_UV.Unbind();

	// Unbind all to prevent accidentally modifying them
	IMPORT_CUBE_SHAPE_VAO.Unbind();
	IMPORT_CUBE_SHAPE_VBO_CORDINATES.Unbind();
	IMPORT_CUBE_SHAPE_VBO_UV.Unbind();
	IMPORT_CUBE_SHAPE_VBO_NORMALS.Unbind();
	IMPORT_CUBE_SHAPE_CORDINATE_EBO.Unbind();
//----------------------------------------------------------------------------------------------------------------------------------------
	Vertex top_left;
	top_left.setCordinate() = glm::vec3(-1.0f, 1.0f, -1.0f);
	//top_left.setNormal() = glm::vec3(0.0f, 1.0f, 0.0f);
	top_left.setUVCord() = glm::vec2(0.0f, 8.0f);
	top_left.setColor() = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

	Vertex top_right;
	top_right.setCordinate() = glm::vec3(1.0f, 1.0f, -1.0f);
	//top_right.setNormal() = glm::vec3(0.0f, 1.0f, 0.0f);
	top_right.setUVCord() = glm::vec2(8.0f, 8.0f);
	top_right.setColor() = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

	Vertex bottom_left;
	bottom_left.setCordinate() = glm::vec3(-1.0f, 1.0f, 1.0f);
	//bottom_left.setNormal() = glm::vec3(0.0f, 1.0f, 0.0f);
	bottom_left.setUVCord() = glm::vec2(0.0f, 0.0f);
	bottom_left.setColor() = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
//----------------------------------------------------------------------------------------------------
	Vertex bottom_right_second;
	bottom_right_second.setCordinate() = glm::vec3(1.0f, 1.0f, 1.0f);
	//bottom_right_second.setNormal() = glm::vec3(0.0f,  1.0f,  0.0f);
	bottom_right_second.setUVCord() = glm::vec2(8.0f, 0.0f);
	bottom_right_second.setColor() = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

	Vertex bottom_left_second;
	bottom_left_second.setCordinate() = glm::vec3(-1.0f, 1.0f, 1.0f);
	//bottom_left_second.setNormal() = glm::vec3(0.0f, 1.0f, 0.0f);
	bottom_left_second.setUVCord() = glm::vec2(0.0f, 0.0f);
	bottom_left_second.setColor() = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

	Vertex top_right_second;
	top_right_second.setCordinate() = glm::vec3(1.0f, 1.0f, -1.0f);
	//top_right.setNormal() = glm::vec3(0.0f, 1.0f, 0.0f);
	top_right_second.setUVCord() = glm::vec2(8.0f, 8.0f);
	top_right_second.setColor() = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

	Face topFaceOne(top_left, top_right, bottom_left);
	Face topFaceTwo(bottom_right_second, bottom_left_second, top_right_second);
	topFaceOne.calculateAutomaticNormal(true); // Parameter for flip direction of normal true positive
	topFaceTwo.calculateAutomaticNormal(true); // Parameter for flip direction of normal true positive
	topFaceOne.calculateFaceData();
	topFaceTwo.calculateFaceData();

	Mesh meshObject;
	meshObject.addTriangleToMesh(topFaceOne);
	meshObject.addTriangleToMesh(topFaceTwo);

	meshObject.getTriangle(0).getVertex(1).setCordinate() = glm::vec3(21.0f, 05.0f, 1.0f);	


	meshObject.calculateMeshData();
	//meshObject.printMeshData(); // Debug
//----------------------------------------------------------

	VAO CUBE_SHAPE_CLASS_VAO;
	CUBE_SHAPE_CLASS_VAO.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO CUBE_SHAPE_CLASS_VBO(meshObject.getMeshData().data(), sizeof(float) * Vertex::s_offsetOfBufferLayout * meshObject.getNumberOfVertices());
	// Generates Element Buffer Object and links it to indices
	EBO CUBE_SHAPE_CLASS_EBO(indices_class_cube, (indices_class_cube.size() * sizeof(EBO::OrderOfRendering) * sizeof(unsigned int)));

	// Links VBO attributes such as cordinates and colors to VAO
	CUBE_SHAPE_CLASS_VAO.LinkAttrib(CUBE_SHAPE_CLASS_VBO, 0, 3, GL_FLOAT, 12 * sizeof(float), (void*)0); // Cordinates
	CUBE_SHAPE_CLASS_VAO.LinkAttrib(CUBE_SHAPE_CLASS_VBO, 1, 3, GL_FLOAT, 12 * sizeof(float), (void*)(3 * sizeof(float))); // Normals
	CUBE_SHAPE_CLASS_VAO.LinkAttrib(CUBE_SHAPE_CLASS_VBO, 2, 2, GL_FLOAT, 12 * sizeof(float), (void*)(6 * sizeof(float))); // Uv texture
	CUBE_SHAPE_CLASS_VAO.LinkAttrib(CUBE_SHAPE_CLASS_VBO, 3, 3, GL_FLOAT, 12 * sizeof(float), (void*)(8 * sizeof(float))); // Color
	// Unbind all to prevent accidentally modifying them
	CUBE_SHAPE_CLASS_VAO.Unbind();
	CUBE_SHAPE_CLASS_VBO.Unbind();
	CUBE_SHAPE_CLASS_EBO.Unbind();
//---------------------------------------------------------------------------------------------------------------------------------------- 
	// Generates Vertex Array Object and binds it
	VAO CUBE_SHAPE_VAO;
	CUBE_SHAPE_VAO.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO CUBE_SHAPE_VBO_VERTICES(vertices_cube, sizeof(vertices_cube));
	// Generates Element Buffer Object and links it to indices
	EBO CUBE_SHAPE_EBO(indices_cube, (indices_cube.size() * sizeof(EBO::OrderOfRendering) * sizeof(unsigned int)));

	// Links VBO attributes such as cordinates and colors to VAO
	CUBE_SHAPE_VAO.LinkAttrib(CUBE_SHAPE_VBO_VERTICES, 0, 3, GL_FLOAT, 12 * sizeof(float), (void*)0); // Cordinates
	CUBE_SHAPE_VAO.LinkAttrib(CUBE_SHAPE_VBO_VERTICES, 1, 3, GL_FLOAT, 12 * sizeof(float), (void*)(3 * sizeof(float))); // Normals
	CUBE_SHAPE_VAO.LinkAttrib(CUBE_SHAPE_VBO_VERTICES, 2, 2, GL_FLOAT, 12 * sizeof(float), (void*)(6 * sizeof(float))); // Uv texture
	CUBE_SHAPE_VAO.LinkAttrib(CUBE_SHAPE_VBO_VERTICES, 3, 3, GL_FLOAT, 12 * sizeof(float), (void*)(8 * sizeof(float))); // Color
	// Unbind all to prevent accidentally modifying them
	CUBE_SHAPE_VAO.Unbind();
	CUBE_SHAPE_VBO_VERTICES.Unbind();
	CUBE_SHAPE_EBO.Unbind();
//----------------------------------------------------------------------------------------------------------------------------------------
	// Generates Vertex Array Object and binds it
	VAO LIGHT_SOURCE_VAO;
	LIGHT_SOURCE_VAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO LIGHT_SOURCE_VBO(vertices_lightSource, sizeof(vertices_lightSource));

	// Links VBO attributes such as cordinates to VAO
	LIGHT_SOURCE_VAO.LinkAttrib(LIGHT_SOURCE_VBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	LIGHT_SOURCE_VAO.LinkAttrib(LIGHT_SOURCE_VBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	LIGHT_SOURCE_VAO.Unbind();
	LIGHT_SOURCE_VBO.Unbind();
//-------------------------------------------------------------------------------------------------------------------------

	Material lampMaterial;
	Material cubeMaterial;
	Material pyramideMaterial;
	Material globalMaterial;

	Light directionalLight(TypeOfLight::DIRECTIONAL_LIGHT);
	Light pointLight(TypeOfLight::POINT_LIGHT);
	Light spotLight(TypeOfLight::SPOT_LIGHT);

	// Serve as bool value that is send to shader in UBO Buffer to control different state on/off effect etc.
	
	RenderFlags renderFlags;
	renderFlags.addRenderFlag("isPointLightReducingOnDistance", true);
	renderFlags.addRenderFlag("isPhong",                        false);
	renderFlags.addRenderFlag("isBlinnPhong",                   true);
	renderFlags.addRenderFlag("isSpecularMap",                  true);
													            
	renderFlags.addRenderFlag("isDirectionalLight",             false);
	renderFlags.addRenderFlag("isPointLight",                   true);
													            
	renderFlags.addRenderFlag("isAutomaticLuminosity",          false);
	renderFlags.addRenderFlag("isManuelLuminosity",             true);
	renderFlags.addRenderFlag("isLightTurnOff",                 false);
	renderFlags.addRenderFlag("isSpotLight",                    false);
	renderFlags.addRenderFlag("isVisualiseNormal",              false);
	renderFlags.addRenderFlag("isVisualiseUVCordinate",         false);

//-----------------------------------------------------------------------------------------------------------------
	// Textures
	Texture popCat("Textures/pop_cat.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgramForObjects, "textures.baseTexture", 0);

	Texture DiJej("Textures/dj.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
	DiJej.texUnit(shaderProgramForObjects, "textures.baseTexture", 0);

	Texture skenons("Textures/logo_skenons.png", 0, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	skenons.texUnit(shaderProgramForObjects, "textures.baseTexture", 0);

	Texture chicken("Textures/chicken_image.png", 0, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	chicken.texUnit(shaderProgramForObjects, "textures.baseTexture", 0);

	Texture run("Textures/run.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
	run.texUnit(shaderProgramForObjects, "textures.baseTexture", 0);

	Texture wood("Textures/wood.png", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
	wood.texUnit(shaderProgramForObjects, "textures.baseTexture", 0);

	Texture planks("Textures/planks.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
	planks.texUnit(shaderProgramForObjects, "textures.baseTexture", 0);
	Texture planksSpec("Textures/Specular/planksSpec.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
	planksSpec.texUnit(shaderProgramForObjects, "textures.specularMap", 1);

	Texture oak("Textures/oak.png", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
	oak.texUnit(shaderProgramForObjects, "textures.baseTexture", 0);
	Texture oakSpec("Textures/Specular/oakSpec.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
	oakSpec.texUnit(shaderProgramForObjects, "textures.specularMap", 1);

	// Enable the depth buffer
	GLCall(glEnable(GL_DEPTH_TEST));

	// Makeing camera
	Camera camera(width, height, glm::vec3(0.0f, 2.0f, 5.0f));
	camera.setPosition(glm::vec3(0.03f, 4.12f, 4.09));
	camera.setOrientation(glm::vec3(0.39f, -0.53f, -0.74));

	// Creating lamp transform
	Transform lampTransform(MenageShaders::getDefaultShaderID(DefaultShader::FOR_LIGHT));
	lampTransform.setPosition(glm::vec3(2.03f, 2.05f, 0.52f)); // Setting object position when program start

	// Creating cube transform
	Transform cubeTransform(MenageShaders::getDefaultShaderID(DefaultShader::FOR_OBJECTS));
	cubeTransform.setPosition(glm::vec3(3.0f, 1.0f, 1.0f)); // Setting object position at program start

	// Creating pyramide transfer
	Transform pyramideTransform(MenageShaders::getDefaultShaderID(DefaultShader::FOR_OBJECTS));
	pyramideTransform.setPosition(glm::vec3(1.0f, 1.0f, 1.0f)); // Setting object position at program start
	
	//Creating importedMeshOBJ transfer
	Transform importedMeshTransform(MenageShaders::getDefaultShaderID(DefaultShader::FOR_OBJECTS));
	importedMeshTransform.setPosition(glm::vec3(0.0f, 0.0f, 0.0f)); // Setting object position at program start

	Object lampObject("lampObject", lampTransform);
	Object cubeObject("cubeObject", cubeTransform);
	Object pyramideObject("pyramideObject", pyramideTransform);
	Object importedMeshObject("importedmMeshObject", importedMeshTransform);

	// Main while loop
	while(!glfwWindowShouldClose(window))
	{	
		lampObject.m_transform->inputs(window);

		GUI::startGUIframe(false);
		GUI::contextOfGUI(camera, renderFlags, lampObject, cubeObject, lampMaterial, globalMaterial, directionalLight, pointLight, spotLight);

		// Setting rendering mode to line
		//glPolygonMode(GL_FRONT, GL_LINE);
		//glPolygonMode(GL_BACK, GL_FILL);
		// Specify the color of the background
		GLCall(glClearColor(0.012f, 0.012f, 0.012f, 1.0f));
		// Clean the back buffer and assign the new color to it
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		// Handling input to move camera, light positon ond light color
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateCameraMatrix(45.0f, 0.1f, 100.0f);

		// Tell OpenGL which Shader Program we want to use 
		shaderProgramForObjects.Activate();

		UnifformBufferObject::sendBoolsUniformToShader("ControlsOfState", UnifformBufferObject::prepareFlags(renderFlags), shaderProgramForObjects.ID);

		// Export for reducing point light in propotional to distance, a constant term Kc, a linear term Kl, and a quadratic term Kq // https://learnopengl.com/Lighting/Light-casters
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "light.exponentForPointLight"), pointLight.getPointLightParams().exponentForPointLight);
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "light.linearTerm_Kl"), pointLight.getPointLightParams().linearTerm_Kl);
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "light.quadraticTerm_Kq"), pointLight.getPointLightParams().quadraticTerm_Kq);
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "light.constantTerm_Kc"), pointLight.getPointLightParams().constantTerm_Kc);

		// Exprort light position and color for dynamic light
		glUniform3f(glGetUniformLocation(shaderProgramForObjects.ID, "light.lightPos"), lampObject.m_transform->transformParams().m_objectPos.x, lampObject.m_transform->transformParams().m_objectPos.y, lampObject.m_transform->transformParams().m_objectPos.z);
		glUniform4f(glGetUniformLocation(shaderProgramForObjects.ID, "light.lightColor"), lampMaterial.getObjectColor().r, lampMaterial.getObjectColor().g, lampMaterial.getObjectColor().b, lampMaterial.getObjectColor().a);
		
		// Light parameters for directional(Sun) light
		glUniform3f(glGetUniformLocation(shaderProgramForObjects.ID, "light.lightDirection"), directionalLight.getDirectionLightParams().lightDirection.x, directionalLight.getDirectionLightParams().lightDirection.y, directionalLight.getDirectionLightParams().lightDirection.z);
		
		// Light parameters for spotlight
		glUniform3f(glGetUniformLocation(shaderProgramForObjects.ID, "light.spotLightDirection"), spotLight.getSpotLightParams().spotLightDirection.x, spotLight.getSpotLightParams().spotLightDirection.y, spotLight.getSpotLightParams().spotLightDirection.z);
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "light.innerCutOff"), glm::cos(glm::radians(spotLight.getSpotLightParams().innerCutOff)));
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "light.outerCutOff"), glm::cos(glm::radians(spotLight.getSpotLightParams().outerCutOff)));
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "light.intensityMultiplayer"), spotLight.getSpotLightParams().intensityMultiplayer);
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "light.thetaMultiplayer"), spotLight.getSpotLightParams().thetaMultiplayer);
		
		// Export global matrials to shader for different material and component strenght
		shaderProgramForObjects.sendFloat("material.ambientStrenght", globalMaterial.getAmbientStrenght()); // TODO : send vec4f to shader insted 1f
		shaderProgramForObjects.sendFloat("material.diffuseStrenght", globalMaterial.getDiffuseStrenght());
		shaderProgramForObjects.sendFloat("material.specularStrength", globalMaterial.getSpecularStrenght());
		shaderProgramForObjects.sendFloat("material.shininessStrenght", globalMaterial.getShininessStrenght());

		shaderProgramForObjects.Deactivate();

		{ //PYRAMIDE
			// Tell OpenGL which Shader Program we want to use 
			shaderProgramForObjects.Activate();

			// Exports the camera Position to the Fragment Shader for specular lighting calculation
			GLCall(glUniform3f(glGetUniformLocation(shaderProgramForObjects.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z));
			// Export the camMatrix to the Vertex Shader of the pyramid
			camera.sendCamMatrixToShader(shaderProgramForObjects, "camMatrix");

			// Export uniforms to shader for different material
			GLCall(glUniform4f(glGetUniformLocation(shaderProgramForObjects.ID, "material.objectColor"), pyramideMaterial.getObjectColor().r, pyramideMaterial.getObjectColor().g, pyramideMaterial.getObjectColor().b, pyramideMaterial.getObjectColor().a));

			// Binding texture so its appear at render
			planks.Bind();
			planksSpec.Bind();

			shaderProgramForObjects.sendBool("useCustomTransform", true); // If is true it will use modelRotate modelPos modelScale for gl_Position
			pyramideObject.m_transform->setPosition(pyramideTransform.transformParams().m_objectPos);
			pyramideObject.m_transform->setScale(pyramideTransform.transformParams().m_objectScale);
			pyramideObject.m_transform->setRotateEuler(pyramideTransform.transformParams().m_objectRotEuler);

			// Bind the VAO so OpenGL knows to use it
			TRIANGLE_SHAPE_VAO.Bind();
			// Draw the pyramid using the GL_TRIANGLES primitive
			GLCall(glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(sizeof(indices_pyramide) / sizeof(int)), GL_UNSIGNED_INT, 0));
			// Unbind texture and VAO and deactivate shader program
			planks.Unbind();
			planksSpec.Unbind();
			TRIANGLE_SHAPE_VAO.Unbind();
			shaderProgramForObjects.Deactivate();
		}
		{ // CUBE
			// Activating shader that is used only for objects
			shaderProgramForObjects.Activate();

			// Exports the camera Position to the Fragment Shader for specular lighting calculation
			GLCall(glUniform3f(glGetUniformLocation(shaderProgramForObjects.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z));
			// Export the camMatrix to the Vertex Shader of the cube
			camera.sendCamMatrixToShader(shaderProgramForObjects, "camMatrix");

			// Export uniforms to shader for different material and component strenght
			GLCall(glUniform4f(glGetUniformLocation(shaderProgramForObjects.ID, "material.objectColor"), cubeMaterial.getObjectColor().r, cubeMaterial.getObjectColor().g, cubeMaterial.getObjectColor().b, cubeMaterial.getObjectColor().a));

			// Binding texture so its appear at render
			planks.Bind();
			planksSpec.Bind();

			shaderProgramForObjects.sendBool("useCustomTransform", true); // If is true it will use modelRotate modelPos modelScale for gl_Position
			cubeObject.m_transform->setPosition(cubeTransform.transformParams().m_objectPos);
			cubeObject.m_transform->setScale(cubeTransform.transformParams().m_objectScale);
			cubeObject.m_transform->setRotateEuler(cubeTransform.transformParams().m_objectRotEuler);

			// Bind the VAO so OpenGL knows to use it
			CUBE_SHAPE_VAO.Bind();
			// Draw the pyramid using the GL_TRIANGLES primitive
			GLCall(glDrawElements(GL_TRIANGLES, static_cast<GLsizei>((indices_cube.size() * sizeof(EBO::OrderOfRendering)) / sizeof(unsigned int)), GL_UNSIGNED_INT, 0));
			// Unbind texture and VAO and deactivate shader program
			planks.Unbind();
			planksSpec.Unbind();
			CUBE_SHAPE_VAO.Unbind();
			shaderProgramForObjects.Deactivate();
		}
		{ // IMPORTED_CUBE
			// Activating shader that is used only for IMPORT_CUBE
			shaderProgramForObjects.Activate();

			// Exports the camera Position to the Fragment Shader for specular lighting calculation
			GLCall(glUniform3f(glGetUniformLocation(shaderProgramForObjects.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z));
			// Passing camMatrix uniform to lightSourceCube for projection matrix
			camera.sendCamMatrixToShader(shaderProgramForObjects, "camMatrix");

			shaderProgramForObjects.sendBool("useCustomTransform", true); // If is true it will use modelRotate modelPos modelScale for gl_Position
			importedMeshObject.m_transform->setPosition(importedMeshTransform.transformParams().m_objectPos);
			importedMeshObject.m_transform->setScale(importedMeshTransform.transformParams().m_objectScale);
			importedMeshObject.m_transform->setRotateEuler(importedMeshTransform.transformParams().m_objectRotEuler);

			wood.Bind();
		    IMPORT_CUBE_SHAPE_VAO.Bind();
			GLCall(glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(importCubeIndex.size()), GL_UNSIGNED_INT, 0));
			IMPORT_CUBE_SHAPE_VAO.Unbind();
			shaderProgramForObjects.Deactivate();
			wood.Unbind();
		}
		{ // LIGHT CUBE SOURCE
			// Activating shader that is used only for lightSource
			lightSourceShader.Activate();

			lampObject.m_transform->setPosition(lampTransform.transformParams().m_objectPos);
			lampObject.m_transform->setScale(lampTransform.transformParams().m_objectScale);
			lampObject.m_transform->setRotateEuler(lampTransform.transformParams().m_objectRotEuler); // lampObject.m_transform->setRotateQuat(lampObject.m_transform->transformParams().m_objectRotQuat);

			// Passing camMatrix uniform to lightSourceCube for projection matrix
			camera.sendCamMatrixToShader(lightSourceShader, "camMatrix");

			// Sending color of light-cube to light shader so when we change color this change also
			GLCall(glUniform4f(glGetUniformLocation(lightSourceShader.ID, "lightColor"), lampMaterial.getObjectColor().r, lampMaterial.getObjectColor().g, lampMaterial.getObjectColor().b, lampMaterial.getObjectColor().a));

			// Binding light source vao in order to draws it
			LIGHT_SOURCE_VAO.Bind();
			// Draw light source cube using DrawArrays no-index(EBO)
			GLCall(glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices_lightSource) / sizeof(float)));
			// Unbind VAO that we just drawn and deactivate shader program
			LIGHT_SOURCE_VAO.Unbind();
			lightSourceShader.Deactivate();
		}
		{ // DEFINE MESH CLASS
			shaderProgramForObjects.Activate();

			// Exports the camera Position to the Fragment Shader for specular lighting calculation
			GLCall(glUniform3f(glGetUniformLocation(shaderProgramForObjects.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z));
			// Passing camMatrix uniform to lightSourceCube for projection matrix
			camera.sendCamMatrixToShader(shaderProgramForObjects, "camMatrix");

			shaderProgramForObjects.sendBool("useCustomTransform", false); // If is true it will use modelRotate modelPos modelScale for gl_Position
			// Kreiraj lokalnu model matricu za triangle
			glm::mat4 cubeModel = glm::mat4(1.0f);  // Resetovana matrica
			cubeModel = glm::translate(cubeModel, glm::vec3(1.0f, 0.0f, 0.0f)); // Transplantacija triangla
			glUniformMatrix4fv(glGetUniformLocation(shaderProgramForObjects.ID, "model"), 1, GL_FALSE, glm::value_ptr(cubeModel)); // Pošalji model matricu u shader
			
			wood.Bind();
			CUBE_SHAPE_CLASS_VAO.Bind();
			GLCall(glDrawElements(GL_TRIANGLES, static_cast<GLsizei>((indices_class_cube.size() * sizeof(EBO::OrderOfRendering)) / sizeof(unsigned int)), GL_UNSIGNED_INT, 0));
			CUBE_SHAPE_CLASS_VAO.Unbind();
			wood.Unbind();
			shaderProgramForObjects.Deactivate();
		}

		GUI::renderGUI();

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	TRIANGLE_SHAPE_VAO.Delete();
	TRIANGLE_SHAPE_VBO.Delete();
	TRIANGLE_SHAPE_EBO.Delete();
	IMPORT_CUBE_SHAPE_VAO.Delete();
	IMPORT_CUBE_SHAPE_VBO_CORDINATES.Delete();
	IMPORT_CUBE_SHAPE_VBO_NORMALS.Delete();
	IMPORT_CUBE_SHAPE_VBO_UV.Delete();
	IMPORT_CUBE_SHAPE_CORDINATE_EBO.Delete();
	CUBE_SHAPE_VAO.Delete();
	CUBE_SHAPE_VBO_VERTICES.Delete();
	CUBE_SHAPE_EBO.Delete();
	LIGHT_SOURCE_VAO.Delete();
	LIGHT_SOURCE_VBO.Delete();
	CUBE_SHAPE_CLASS_VAO.Delete();
	CUBE_SHAPE_CLASS_VBO.Delete();
	CUBE_SHAPE_CLASS_EBO.Delete();
	popCat.Delete();
	DiJej.Delete();
	skenons.Delete();
	run.Delete();
	chicken.Delete();
	wood.Delete();
	shaderProgramForObjects.Delete();
	lightSourceShader.Delete();

	GUI::clearGUI();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}