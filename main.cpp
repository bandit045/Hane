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
	// Positions     // Colors      // Texture-cordinates(x, y)    // Normals (x, y, z)

	// Front face (z = 1.0)
	-1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,  // Bottom-left
	 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  repeat_time_cube, 0.0f,  0.0f,  0.0f,  1.0f,  // Bottom-right
	 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  repeat_time_cube, repeat_time_cube,  0.0f,  0.0f,  1.0f,  // Top-right
	-1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f, repeat_time_cube,  0.0f,  0.0f,  1.0f,  // Top-left

	// Back face (z = -1.0)
	-1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,  // Bottom-left
	 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  repeat_time_cube, 0.0f,  0.0f,  0.0f, -1.0f,  // Bottom-right
	 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  repeat_time_cube, repeat_time_cube,  0.0f,  0.0f, -1.0f,  // Top-right
	-1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, repeat_time_cube,  0.0f,  0.0f, -1.0f,  // Top-left

	// Left face (x = -1.0)
	-1.0f, -1.0f, -1.0f, 1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  -1.0f,  0.0f,  0.0f,  // Bottom-left
	-1.0f, -1.0f,  1.0f, 1.0f,  0.0f,  0.0f,  repeat_time_cube, 0.0f,  -1.0f,  0.0f,  0.0f,  // Bottom-right
	-1.0f,  1.0f,  1.0f, 1.0f,  0.0f,  0.0f,  repeat_time_cube, repeat_time_cube,  -1.0f,  0.0f,  0.0f,  // Top-right
	-1.0f,  1.0f, -1.0f, 1.0f,  0.0f,  0.0f,  0.0f, repeat_time_cube,  -1.0f,  0.0f,  0.0f,  // Top-left

	// Right face (x = 1.0)
	 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,  // Bottom-left
	 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  repeat_time_cube, 0.0f,  1.0f,  0.0f,  0.0f,  // Bottom-right
	 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  repeat_time_cube, repeat_time_cube,  1.0f,  0.0f,  0.0f,  // Top-right
	 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, repeat_time_cube,  1.0f,  0.0f,  0.0f,  // Top-left

	// Top face (y = 1.0)
	-1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, repeat_time_cube_top,  0.0f,  1.0f,  0.0f,  // Top-left
	 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  repeat_time_cube_top, repeat_time_cube_top,  0.0f,  1.0f,  0.0f,  // Top-right
	 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  repeat_time_cube_top, 0.0f,  0.0f,  1.0f,  0.0f,  // Bottom-right
	-1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,  // Bottom-left

	// Bottom face (y = -1.0)
	-1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,  // Bottom-left
	 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  repeat_time_cube, 0.0f,  0.0f, -1.0f,  0.0f,  // Bottom-right
	 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  repeat_time_cube, repeat_time_cube,  0.0f, -1.0f,  0.0f,  // Top-right
	-1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f, repeat_time_cube,  0.0f, -1.0f,  0.0f   // Top-left
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
		-0.01f, -0.01f,  0.01f, 0.0f, 0.0f, 1.0f,
		 0.01f, -0.01f,  0.01f, 0.0f, 0.0f, 1.0f,
		 0.01f,  0.01f,  0.01f, 0.0f, 0.0f, 1.0f,
		 0.01f,  0.01f,  0.01f, 0.0f, 0.0f, 1.0f,
		-0.01f,  0.01f,  0.01f, 0.0f, 0.0f, 1.0f,
		-0.01f, -0.01f,  0.01f, 0.0f, 0.0f, 1.0f,

		// Zadnja strana
		-0.01f, -0.01f, -0.01f, 0.0f, 0.0f, -1.0f,
		 0.01f, -0.01f, -0.01f, 0.0f, 0.0f, -1.0f,
		 0.01f,  0.01f, -0.01f, 0.0f, 0.0f, -1.0f,
		 0.01f,  0.01f, -0.01f, 0.0f, 0.0f, -1.0f,
		-0.01f,  0.01f, -0.01f, 0.0f, 0.0f, -1.0f,
		-0.01f, -0.01f, -0.01f, 0.0f, 0.0f, -1.0f,

		// Leva strana
		-0.01f,  0.01f,  0.01f, -1.0f, 0.0f, 0.0f,
		-0.01f,  0.01f, -0.01f, -1.0f, 0.0f, 0.0f,
		-0.01f, -0.01f, -0.01f, -1.0f, 0.0f, 0.0f,
		-0.01f, -0.01f, -0.01f, -1.0f, 0.0f, 0.0f,
		-0.01f, -0.01f,  0.01f, -1.0f, 0.0f, 0.0f,
		-0.01f,  0.01f,  0.01f, -1.0f, 0.0f, 0.0f,

		// Desna strana
		 0.01f,  0.01f,  0.01f, 1.0f, 0.0f, 0.0f,
		 0.01f,  0.01f, -0.01f, 1.0f, 0.0f, 0.0f,
		 0.01f, -0.01f, -0.01f, 1.0f, 0.0f, 0.0f,
		 0.01f, -0.01f, -0.01f, 1.0f, 0.0f, 0.0f,
		 0.01f, -0.01f,  0.01f, 1.0f, 0.0f, 0.0f,
		 0.01f,  0.01f,  0.01f, 1.0f, 0.0f, 0.0f,

		 // Donja strana
		 -0.01f, -0.01f, -0.01f, 0.0f, 1.0f, 0.0f,
		  0.01f, -0.01f, -0.01f, 0.0f, 1.0f, 0.0f,
		  0.01f, -0.01f,  0.01f, 0.0f, 1.0f, 0.0f,
		  0.01f, -0.01f,  0.01f, 0.0f, 1.0f, 0.0f,
		 -0.01f, -0.01f,  0.01f, 0.0f, 1.0f, 0.0f,
		 -0.01f, -0.01f, -0.01f, 0.0f, 1.0f, 0.0f,

		 // Gornja strana
		 -0.01f,  0.01f, -0.01f, 0.0f, -1.0f, 0.0f,
		  0.01f,  0.01f, -0.01f, 0.0f, -1.0f, 0.0f,
		  0.01f,  0.01f,  0.01f, 0.0f, -1.0f, 0.0f,
		  0.01f,  0.01f,  0.01f, 0.0f, -1.0f, 0.0f,
		 -0.01f,  0.01f,  0.01f, 0.0f, -1.0f, 0.0f,
		 -0.01f,  0.01f, -0.01f, 0.0f, -1.0f, 0.0f
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
	GUI guiWindow = GUI(window);
//-----------------------------------------------------------------------------------------------
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 1920, y = 1080
	glViewport(0,0, width, height);

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgramForObjects("default.vert", "default.frag");
	Shader lightSourceShader("lightingSourceShader.vert", "lightingSourceShader.frag");
	MenageShaders::setDefaultShadersForAllID(shaderProgramForObjects.ID, lightSourceShader.ID);
	std::cout << "Light Source Shader(how object look): " << MenageShaders::getDefaultShaderID(DefaultShader::FOR_LIGHT);
	std::cout << "\nShader Program For Objects(how object look): " << MenageShaders::getDefaultShaderID(DefaultShader::FOR_OBJECTS) << "\n";
//------------------------------------------------------------------------------------------------
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
	std::vector< glm::vec3 > importVerticesCube;
	std::vector< glm::vec2 > importUvsCube;
	std::vector< glm::vec3 > importNormalsCube;

	// Used for storing EBO cordinates
	std::vector<unsigned int> importCubeIndex;

	// We import our vertex model cordinates, uv, normals inside variable that are passed by reference
	Importer::loadOBJ("ff.obj", importVerticesCube, importUvsCube, importNormalsCube, importCubeIndex); // Cordinates, Texture-cords, Normals, EBO

	// Generates Vertex Array Object for file from import and binds it
	VAO IMPORT_CUBE_SHAPE_VAO;
	IMPORT_CUBE_SHAPE_VAO.Bind();

	// Generates Vertex Buffer Object for impport object cube and links it to vertices
	VBO IMPORT_CUBE_SHAPE_VBO_CORDINATES(importVerticesCube, importVerticesCube.size() * sizeof(glm::vec3));
	VBO IMPORT_CUBE_SHAPE_VBO_NORMALS(importNormalsCube, importNormalsCube.size() * sizeof(glm::vec3));
	VBO IMPORT_CUBE_SHAPE_VBO_UV(importUvsCube, importUvsCube.size() * sizeof(glm::vec2));
	// Generates Element Buffer Object for imported cube and links it to indices
	EBO IMPORT_CUBE_SHAPE_EBO(importCubeIndex, importCubeIndex.size() * sizeof(unsigned int));

	IMPORT_CUBE_SHAPE_VAO.LinkAttrib(IMPORT_CUBE_SHAPE_VBO_CORDINATES, 0 , 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	IMPORT_CUBE_SHAPE_VAO.LinkAttrib(IMPORT_CUBE_SHAPE_VBO_NORMALS, 1 , 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	IMPORT_CUBE_SHAPE_VAO.LinkAttrib(IMPORT_CUBE_SHAPE_VBO_UV, 2 , 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
	// Unbind all to prevent accidentally modifying them
	IMPORT_CUBE_SHAPE_VAO.Unbind();
	IMPORT_CUBE_SHAPE_VBO_CORDINATES.Unbind();
	IMPORT_CUBE_SHAPE_EBO.Unbind();
//----------------------------------------------------------------------------------------------------------------------------------------
	// Generates Vertex Array Object and binds it
	VAO CUBE_SHAPE_VAO;
	CUBE_SHAPE_VAO.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO CUBE_SHAPE_VBO_VERTICES(vertices_cube, sizeof(vertices_cube));
	// Generates Element Buffer Object and links it to indices
	EBO CUBE_SHAPE_EBO(indices_cube, sizeof(indices_cube));

	// Links VBO attributes such as cordinates and colors to VAO
	CUBE_SHAPE_VAO.LinkAttrib(CUBE_SHAPE_VBO_VERTICES, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	CUBE_SHAPE_VAO.LinkAttrib(CUBE_SHAPE_VBO_VERTICES, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	CUBE_SHAPE_VAO.LinkAttrib(CUBE_SHAPE_VBO_VERTICES, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	CUBE_SHAPE_VAO.LinkAttrib(CUBE_SHAPE_VBO_VERTICES, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
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
	LIGHT_SOURCE_VAO.LinkAttrib(LIGHT_SOURCE_VBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	LIGHT_SOURCE_VAO.Unbind();
	LIGHT_SOURCE_VBO.Unbind();
//-------------------------------------------------------------------------------------------------------------------------

	struct Material
	{
		glm::vec4 objectColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		float ambientStrenght = 0.6f;
		float diffuseStrenght = 1.9f;
		float specularStrength = 0.5f;
		float shininessStrenght = 16.0f;
	};
	Material lampMaterial;
	Material cubeMaterial;
	Material pyramideMaterial;
	Material globalMaterial;
	//****

	Light directionalLight(TypeOfLight::DIRECTIONAL_LIGHT);
	Light pointLight(TypeOfLight::POINT_LIGHT);

	/*struct RenderFlags // For different state insade the fragment shader
	{
		bool isPointLightReducingOnDistance = true;
		bool isPhong = false;
		bool isBlinnPhong = true;
		bool isSpecularMap = true;

		bool isDirectionalLight = false; // Light
		bool isPointLight = true; // Light

		bool isAutomaticLuminosity = false; // Light
		bool isManuelLuminosity = true; // Light
	};*/
	RenderFlags renderFlags{
		true,
		false,
		true,
		true,

		false, // Light
		true, // Light

		false, // Light
		true, // Light
	
	};

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
	glEnable(GL_DEPTH_TEST);

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

		GUI::startGUIframe(true);
		GUI::contextOfGUI();
		{
			ImGui::Begin("Performance:");
			
			if (ImGui::Checkbox("Point Light", &renderFlags.isPointLight)) {
				if (renderFlags.isPointLight) {
					renderFlags.isDirectionalLight = false;
					renderFlags.isPointLightReducingOnDistance = true;
					renderFlags.isPhong = false;
					renderFlags.isBlinnPhong = true;
					globalMaterial.ambientStrenght = 0.5f;
				}
			}

			if (ImGui::Checkbox("Direction Light", &renderFlags.isDirectionalLight)) {
				if (renderFlags.isDirectionalLight) {
					renderFlags.isPointLight = false;
					renderFlags.isPointLightReducingOnDistance = false;
					renderFlags.isPhong = true;
					renderFlags.isBlinnPhong = false;
					globalMaterial.ambientStrenght = 0.2f;
				}
			}

			ImGui::Text("Position of camera: %.2f, %.2f, %.2f", camera.Position.x, camera.Position.y, camera.Position.z);
			ImGui::Text("Orientation of camera: %.2f, %.2f, %.2f", camera.Orientation.x, camera.Orientation.y, camera.Orientation.z);
			ImGui::Text("Up of camera: %.2f, %.2f, %.2f", camera.Up.x, camera.Up.y, camera.Up.z);
			ImGui::End();
		}
		{

			ImGui::Begin("Light source");
			if (ImGui::CollapsingHeader("Color and position of light source", ImGuiTreeNodeFlags_DefaultOpen)) {

				ImGui::SeparatorText("Color for light source:"); ImGui::Spacing();
				ImGui::SliderFloat3("Color", &lampMaterial.objectColor.x, 0.0f, 1.0f);
				ImGui::Separator();
				ImGui::DragFloat3("Position for point light", &lampObject.m_transform->transformParams().m_objectPos.x, 0.1f);
				ImGui::SliderFloat3("Rotation vector of point light", &lampObject.m_transform->transformParams().m_objectRotEuler.x, -180.0f, 180.0f);
				ImGui::DragFloat4("Quaternion orbit of lightource", &lampObject.m_transform->transformParams().m_objectRotQuat.x, 64.0f, 720.0f);
				ImGui::SliderFloat3("Scale factor of light", &lampObject.m_transform->transformParams().m_objectScale.x, 0.0f, 64.0f);
				ImGui::Separator();
				ImGui::SliderFloat3("Direction vector of light", &directionalLight.setDirectionLightParams().lightDirection.x, -0.5f, 0.5f);

				ImGui::SeparatorText("Position and color of light source:"); ImGui::Spacing();
				ImGui::Text("Color of the light source in float: R: %.2ff, G: %.2ff, B: %.2ff, A: %.2ff", lampMaterial.objectColor.r, lampMaterial.objectColor.g, lampMaterial.objectColor.b, lampMaterial.objectColor.a);
				ImGui::Separator();
				ImGui::Text("Position of the point light source: %.2f, %.2f, %.2f", lampObject.m_transform->transformParams().m_objectPos.x, lampObject.m_transform->transformParams().m_objectPos.y, lampObject.m_transform->transformParams().m_objectPos.z);
				ImGui::TextWrapped("Rotation of the point light source: %.2f, %.2f, %.2f", lampObject.m_transform->transformParams().m_objectRotEuler.x, lampObject.m_transform->transformParams().m_objectRotEuler.y, lampObject.m_transform->transformParams().m_objectRotEuler.z);
				ImGui::TextWrapped("Quaternion orbite light source: %.2f, %.2f, %.2f, %.2f", lampObject.m_transform->transformParams().m_objectRotQuat.x, lampObject.m_transform->transformParams().m_objectRotQuat.y, lampObject.m_transform->transformParams().m_objectRotQuat.z, lampObject.m_transform->transformParams().m_objectRotQuat.w);
				ImGui::Text("Vector of the directional light source: %.2f, %.2f, %.2f", directionalLight.getDirectionLightParams().lightDirection.x, directionalLight.getDirectionLightParams().lightDirection.y, directionalLight.getDirectionLightParams().lightDirection.z);
			}
			if (ImGui::CollapsingHeader("Attenuation the light equation", ImGuiTreeNodeFlags_DefaultOpen)) {

				ImGui::SeparatorText("State on/off:"); ImGui::Spacing();
				ImGui::Checkbox("Is Point Light Reducing On Distance", &renderFlags.isPointLightReducingOnDistance);

				ImGui::SeparatorText("Control of variables MANUEL:");
				ImGui::SliderFloat("Exponent for distance:", &pointLight.setPointLightParams().exponentForPointLight, -64, 256); ImGui::SameLine(0, 0); if (ImGui::SmallButton("2.0f")) { pointLight.setPointLightParams().exponentForPointLight = 2.0f; }; ImGui::Spacing();
				ImGui::SliderFloat("Linear Term Kl:", &pointLight.setPointLightParams().linearTerm_Kl, -2.683f, 256.0f); ImGui::SameLine(0, 0); if (ImGui::SmallButton("0.7f")) { pointLight.setPointLightParams().linearTerm_Kl = 0.7f; }; ImGui::Spacing();
				ImGui::SliderFloat("Quadratic Term Kq:", &pointLight.setPointLightParams().quadraticTerm_Kq, -64.0f, 64.0f); ImGui::SameLine(0, 0); if (ImGui::SmallButton("1.8f")) { pointLight.setPointLightParams().quadraticTerm_Kq = 1.8f; }; ImGui::Spacing();
				ImGui::SliderFloat("Constant Term Kc:", &pointLight.setPointLightParams().constantTerm_Kc, 0.0f, 64.0f); ImGui::SameLine(0, 0); if (ImGui::SmallButton("1.0f")) { pointLight.setPointLightParams().constantTerm_Kc = 1.0f; }; ImGui::Spacing();

				if (ImGui::Button("RESET EQUATION", ImVec2(120, 40))) {
					pointLight.setPointLightParams().exponentForPointLight = 2.0f;
					pointLight.setPointLightParams().linearTerm_Kl = 0.7f;
					pointLight.setPointLightParams().quadraticTerm_Kq = 1.8f;
					pointLight.setPointLightParams().constantTerm_Kc = 1.0f;
				};  ImGui::SameLine(0, 0); if (ImGui::SmallButton("Set manuel active")) { renderFlags.isManuelLuminosity = true; renderFlags.isAutomaticLuminosity = false; };

				ImGui::SeparatorText("Control of variables AUTOMATIC:"); ImGui::Spacing();
				ImGui::SliderFloat("Overall Light Brightness:", &pointLight.setPointLightParams().overallLightBrightness, 0, 1); ImGui::SameLine(0, 0); if (ImGui::SmallButton("1.0")) { pointLight.setPointLightParams().overallLightBrightness = 1.0f; }; ImGui::Spacing();
				ImGui::SameLine(0, 0); if (ImGui::SmallButton("Set automatic active")) { renderFlags.isManuelLuminosity = false; renderFlags.isAutomaticLuminosity = true; };

				ImGui::SeparatorText("Bref explanation:"); ImGui::Spacing();
				ImGui::BulletText("To reduce the intensity of point light over the distance");

				ImGui::BulletText("More about it: ");
				ImGui::SameLine(0, 4);
				ImGui::TextLinkOpenURL("https://learnopengl.com/Lighting/Light-casters");
			}
			if (ImGui::CollapsingHeader("Model of light reflection", ImGuiTreeNodeFlags_DefaultOpen)) {

				ImGui::SeparatorText("State of specular reflection on/off"); ImGui::Spacing();
				if (ImGui::Checkbox("Phong", &renderFlags.isPhong)) {
					if (renderFlags.isPhong) {
						renderFlags.isBlinnPhong = false;
					}
				}

				if (ImGui::Checkbox("Blinn-Phong", &renderFlags.isBlinnPhong)) {
					if (renderFlags.isBlinnPhong) {
						renderFlags.isPhong = false;
					}
				}
				ImGui::Separator(); ImGui::Spacing();
				ImGui::Checkbox("Specular Map", &renderFlags.isSpecularMap);

				ImGui::SeparatorText("Control of variables:"); ImGui::Spacing();
				ImGui::SliderFloat("Ambient Strenght:", &globalMaterial.ambientStrenght, 0.0f, 32.0f); ImGui::SameLine(0, 0);if(ImGui::SmallButton("0.6f")){ globalMaterial.ambientStrenght = 0.6f; }; ImGui::Spacing();
				ImGui::SliderFloat("Diffuse Strenght:", &globalMaterial.diffuseStrenght, 0.0f, 64.0f); ImGui::SameLine(0, 0); if (ImGui::SmallButton("1.9f")) { globalMaterial.diffuseStrenght = 1.9f; };  ImGui::Spacing();
				ImGui::SliderFloat("Specular Strength:", &globalMaterial.specularStrength, 0.0f, 64.0f); ImGui::SameLine(0, 0); if (ImGui::SmallButton("0.5f")) { globalMaterial.specularStrength = 0.5f; };  ImGui::Spacing();
				ImGui::SliderFloat("Shininess Strength:", &globalMaterial.shininessStrenght, 0.0f, 256.0f); ImGui::SameLine(0, 0); if (ImGui::SmallButton("16.0f")) { globalMaterial.shininessStrenght = 16.0f; };  ImGui::Spacing();

				if (ImGui::Button("RESET STRENGHT", ImVec2(120, 40))) {
					globalMaterial.ambientStrenght = 0.6f;
					globalMaterial.diffuseStrenght = 1.9f;
					globalMaterial.specularStrength = 0.5f;
					globalMaterial.shininessStrenght = 16.0f;
				};
				//ImGui::ArrowButton("Up", ImGuiDir_Up);
				ImGui::Separator();
			}
			ImGui::End();
		}


		// Setting rendering mode to line
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// Specify the color of the background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Handling input to move camera, light positon ond light color
		camera.Inputs(window, lampMaterial.objectColor, renderFlags.isBlinnPhong, renderFlags.isPhong, renderFlags.isSpecularMap);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateCameraMatrix(45.0f, 0.1f, 100.0f);

		// Tell OpenGL which Shader Program we want to use 
		shaderProgramForObjects.Activate();

		/*unsigned int uniformBlockIndexRed = glGetUniformBlockIndex(shaderProgramForObjects.ID, "ControlsOfState");
		glUniformBlockBinding(shaderProgramForObjects.ID, uniformBlockIndexRed, 0);

		unsigned int renderFlagsUnifformObject;
		glGenBuffers(1, &renderFlagsUnifformObject);

		glBindBuffer(GL_UNIFORM_BUFFER, renderFlagsUnifformObject);
		glBufferData(GL_UNIFORM_BUFFER, 8 * sizeof(int), NULL, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glBindBufferRange(GL_UNIFORM_BUFFER, 0, renderFlagsUnifformObject, 0, 8 * sizeof(int));

		int renderFlagsInt[8] = {
			renderFlags.isPointLightReducingOnDistance ? 1 : 0,
			renderFlags.isPhong ? 1 : 0,
			renderFlags.isBlinnPhong ? 1 : 0,
			renderFlags.isSpecularMap ? 1 : 0,
			renderFlags.isDirectionalLight ? 1 : 0,
			renderFlags.isPointLight ? 1 : 0,
			renderFlags.isAutomaticLuminosity ? 1 : 0,
			renderFlags.isManuelLuminosity ? 1 : 0,
		};

		glBindBuffer(GL_UNIFORM_BUFFER, renderFlagsUnifformObject);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(renderFlagsInt), &renderFlagsInt);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);*/

		/*glBindBuffer(GL_UNIFORM_BUFFER, renderFlagsUnifformObject);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, 8 * 4, &renderFlagsShader.isPointLightReducingOnDistance);
		glBufferSubData(GL_UNIFORM_BUFFER, 4, 8 * 4, &renderFlagsShader.isPhong);
		glBufferSubData(GL_UNIFORM_BUFFER, 8, 8 * 4, &renderFlagsShader.isBlinnPhong);
		glBufferSubData(GL_UNIFORM_BUFFER, 12, 8 * 4, &renderFlagsShader.isSpecularMap);
		glBufferSubData(GL_UNIFORM_BUFFER, 16, 8 * 4, &renderFlagsShader.isDirectionalLight);
		glBufferSubData(GL_UNIFORM_BUFFER, 20, 8 * 4, &renderFlagsShader.isPointLight);
		glBufferSubData(GL_UNIFORM_BUFFER, 24, 8 * 4, &renderFlagsShader.isAutomaticLuminosity);
		glBufferSubData(GL_UNIFORM_BUFFER, 28, 8 * 4, &renderFlagsShader.isManuelLuminosity);

		/*		bool isPointLightReducingOnDistance = true;
		bool isPhong = false;
		bool isBlinnPhong = true;
		bool isSpecularMap = true;

		bool isDirectionalLight = false; // Light
		bool isPointLight = true; // Lights

		bool isAutomaticLuminosity = false; // Light
		bool isManuelLuminosity = true; // Light*/

		std::vector<std::string> insertOrder;
		//insertOrder.resize(8);
		std::unordered_map<std::string, bool> flags;

		flags.insert(std::pair<std::string, bool>("isPointLightReducingOnDistance", renderFlags.isPointLightReducingOnDistance));
		insertOrder.push_back("isPointLightReducingOnDistance");

		flags.insert(std::pair<std::string, bool>("isPhong", renderFlags.isPhong));
		insertOrder.push_back("isPhong");

		flags.insert(std::pair<std::string, bool>("isBlinnPhong", renderFlags.isBlinnPhong));
		insertOrder.push_back("isBlinnPhong");

		flags.insert(std::pair<std::string, bool>("isSpecularMap", renderFlags.isSpecularMap));
		insertOrder.push_back("isSpecularMap");

		flags.insert(std::pair<std::string, bool>("isDirectionalLight", renderFlags.isDirectionalLight));
		insertOrder.push_back("isDirectionalLight");

		flags.insert(std::pair<std::string, bool>("isPointLight", renderFlags.isPointLight));
		insertOrder.push_back("isPointLight");

		flags.insert(std::pair<std::string, bool>("isAutomaticLuminosity", renderFlags.isAutomaticLuminosity));
		insertOrder.push_back("isAutomaticLuminosity");

		flags.insert(std::pair<std::string, bool>("isManuelLuminosity", renderFlags.isManuelLuminosity));
		insertOrder.push_back("isManuelLuminosity");


		/*std::vector<int> boolsToSend;
		boolsToSend.resize(8);
		boolsToSend[0] = flags["isPointLightReducingOnDistance"];
		boolsToSend[1] = flags["isPhong"];
		boolsToSend[2] = flags["isBlinnPhong"];
		boolsToSend[3] = flags["isSpecularMap"];
		boolsToSend[4] = flags["isDirectionalLight"];
		boolsToSend[5] = flags["isPointLight"];
		boolsToSend[6] = flags["isAutomaticLuminosity"];
		boolsToSend[7] = flags["isManuelLuminosity"];*/


		//UnifformBufferObject::prepareVectorToSendFromUnordered_map(flags);
		UnifformBufferObject::sendBoolsUniformToShader("ControlsOfState", UnifformBufferObject::prepareVectorToSendFromUnordered_Map(flags, insertOrder), shaderProgramForObjects.ID);
		
		//shaderProgramForObjects.sendUniformBufferStructBool("ControlsOfState", 8, renderFlags);

		// Export state in shader in order to dynamicly change during runtime
		//shaderProgramForObjects.sendBool("control.isPhong", renderFlags.isPhong);																// glUniform1i(glGetUniformLocation(shaderProgramForObjects.ID, "control.isPhong"), renderFlags.isPhong);
		//shaderProgramForObjects.sendBool("control.isBlinnPhong", renderFlags.isBlinnPhong);														// glUniform1i(glGetUniformLocation(shaderProgramForObjects.ID, "control.isBlinnPhong"), renderFlags.isBlinnPhong);
		//shaderProgramForObjects.sendBool("control.isSpecularMap", renderFlags.isSpecularMap);													// glUniform1i(glGetUniformLocation(shaderProgramForObjects.ID, "control.isSpecularMap"), renderFlags.isSpecularMap);
		//shaderProgramForObjects.sendBool("control.isPointLight", renderFlags.isPointLight);														// glUniform1i(glGetUniformLocation(shaderProgramForObjects.ID, "control.isPointLight"), renderFlags.isPointLight);
		//shaderProgramForObjects.sendBool("control.isPointLightReducingOnDistance", renderFlags.isPointLightReducingOnDistance);					// glUniform1i(glGetUniformLocation(shaderProgramForObjects.ID, "control.isPointLightReducingOnDistance"), renderFlags.isPointLightReducingOnDistance);
		//shaderProgramForObjects.sendBool("control.isDirectionalLight", renderFlags.isDirectionalLight);											// glUniform1i(glGetUniformLocation(shaderProgramForObjects.ID, "control.isDirectionalLight"), renderFlags.isDirectionalLight);
		//shaderProgramForObjects.sendBool("control.isAutomaticLuminosity", renderFlags.isAutomaticLuminosity);									// glUniform1i(glGetUniformLocation(shaderProgramForObjects.ID, "control.isAutomaticLuminosity"), renderFlags.isAutomaticLuminosity);
		//shaderProgramForObjects.sendBool("control.isManuelLuminosity", renderFlags.isManuelLuminosity);											// glUniform1i(glGetUniformLocation(shaderProgramForObjects.ID, "control.isManuelLuminosity"), renderFlags.isManuelLuminosity);
		// Export for reducing point light in propotional to distance, a constant term Kc, a linear term Kl, and a quadratic term Kq // https://learnopengl.com/Lighting/Light-casters
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "light.exponentForPointLight"), pointLight.getPointLightParams().exponentForPointLight);
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "light.linearTerm_Kl"), pointLight.getPointLightParams().linearTerm_Kl);
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "light.quadraticTerm_Kq"), pointLight.getPointLightParams().quadraticTerm_Kq);
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "light.constantTerm_Kc"), pointLight.getPointLightParams().constantTerm_Kc);

		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "light.overallLightBrightness"), pointLight.getPointLightParams().overallLightBrightness);
		// Exprort light position for dynamic light
		glUniform3f(glGetUniformLocation(shaderProgramForObjects.ID, "light.lightPos"), lampObject.m_transform->transformParams().m_objectPos.x, lampObject.m_transform->transformParams().m_objectPos.y, lampObject.m_transform->transformParams().m_objectPos.z);
		glUniform3f(glGetUniformLocation(shaderProgramForObjects.ID, "light.lightDirection"), directionalLight.getDirectionLightParams().lightDirection.x, directionalLight.getDirectionLightParams().lightDirection.y, directionalLight.getDirectionLightParams().lightDirection.z);
		glUniform4f(glGetUniformLocation(shaderProgramForObjects.ID, "light.lightColor"), lampMaterial.objectColor.r, lampMaterial.objectColor.g, lampMaterial.objectColor.b, lampMaterial.objectColor.a);
		// Export uniforms to shader for different material and component strenght
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "material.ambientStrenght"), globalMaterial.ambientStrenght);
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "material.diffuseStrenght"), globalMaterial.diffuseStrenght);
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "material.specularStrength"), globalMaterial.specularStrength);
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "material.shininessStrenght"), globalMaterial.shininessStrenght);

		shaderProgramForObjects.Deactivate();

		{ //PYRAMIDE
			// Tell OpenGL which Shader Program we want to use 
			shaderProgramForObjects.Activate();

			// Exports the camera Position to the Fragment Shader for specular lighting calculation
			glUniform3f(glGetUniformLocation(shaderProgramForObjects.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
			// Export the camMatrix to the Vertex Shader of the pyramid
			camera.sendCamMatrixToShader(shaderProgramForObjects, "camMatrix");

			// Export uniforms to shader for different material
			glUniform4f(glGetUniformLocation(shaderProgramForObjects.ID, "material.objectColor"), pyramideMaterial.objectColor.r, pyramideMaterial.objectColor.g, pyramideMaterial.objectColor.b, pyramideMaterial.objectColor.a);

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
			glDrawElements(GL_TRIANGLES, sizeof(indices_pyramide) / sizeof(int), GL_UNSIGNED_INT, 0);
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
			glUniform3f(glGetUniformLocation(shaderProgramForObjects.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
			// Export the camMatrix to the Vertex Shader of the cube
			camera.sendCamMatrixToShader(shaderProgramForObjects, "camMatrix");

			// Export uniforms to shader for different material and component strenght
			glUniform4f(glGetUniformLocation(shaderProgramForObjects.ID, "material.objectColor"), cubeMaterial.objectColor.r, cubeMaterial.objectColor.g, cubeMaterial.objectColor.b, cubeMaterial.objectColor.a);

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
			glDrawElements(GL_TRIANGLES, sizeof(indices_cube) / sizeof(int), GL_UNSIGNED_INT, 0);
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
			glUniform3f(glGetUniformLocation(shaderProgramForObjects.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
			// Passing camMatrix uniform to lightSourceCube for projection matrix
			camera.sendCamMatrixToShader(shaderProgramForObjects, "camMatrix");

			shaderProgramForObjects.sendBool("useCustomTransform", true); // If is true it will use modelRotate modelPos modelScale for gl_Position
			importedMeshObject.m_transform->setPosition(importedMeshTransform.transformParams().m_objectPos);
			importedMeshObject.m_transform->setScale(importedMeshTransform.transformParams().m_objectScale);
			importedMeshObject.m_transform->setRotateEuler(importedMeshTransform.transformParams().m_objectRotEuler);

			oak.Bind();
			oakSpec.Bind();
		    IMPORT_CUBE_SHAPE_VAO.Bind();
			glDrawElements(GL_TRIANGLES, importCubeIndex.size(), GL_UNSIGNED_INT, 0);
			IMPORT_CUBE_SHAPE_VAO.Unbind();
			shaderProgramForObjects.Deactivate();
			oak.Unbind();
			oakSpec.Unbind();
		}
		{ // LIGHT CUBE SOURCE
			// Activating shader that is used only for lightSource
			lightSourceShader.Activate();

			if (renderFlags.isDirectionalLight) {

				lampObject.m_transform->setPosition(lampTransform.transformParams().m_objectPos);
				lampObject.m_transform->setScale(lampTransform.transformParams().m_objectScale);
				lampObject.m_transform->setRotateEuler(lampTransform.transformParams().m_objectRotEuler);
			}
			else if(renderFlags.isPointLight)
			{
				lampObject.m_transform->setPosition(lampObject.m_transform->transformParams().m_objectPos);
				lampObject.m_transform->setScale(lampObject.m_transform->transformParams().m_objectScale);
				lampObject.m_transform->setRotateQuat(lampObject.m_transform->transformParams().m_objectRotQuat);
			}

			// Passing camMatrix uniform to lightSourceCube for projection matrix
			camera.sendCamMatrixToShader(lightSourceShader, "camMatrix");

			// Sending color of light-cube to light shader so when we change color this change also
			glUniform4f(glGetUniformLocation(lightSourceShader.ID, "lightColor"), lampMaterial.objectColor.r, lampMaterial.objectColor.g, lampMaterial.objectColor.b, lampMaterial.objectColor.a);

			// Binding light source vao in order to draws it
			LIGHT_SOURCE_VAO.Bind();
			// Draw light source cube using DrawArrays no-index(EBO)
			glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices_lightSource) / sizeof(float));
			// Unbind VAO that we just drawn and deactivate shader program
			LIGHT_SOURCE_VAO.Unbind();
			lightSourceShader.Deactivate();
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
	IMPORT_CUBE_SHAPE_EBO.Delete();
	CUBE_SHAPE_VAO.Delete();
	CUBE_SHAPE_VBO_VERTICES.Delete();
	CUBE_SHAPE_EBO.Delete();
	LIGHT_SOURCE_VAO.Delete();
	LIGHT_SOURCE_VBO.Delete();
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