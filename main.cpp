#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include <stdio.h>

#include "Texture.h"
#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Camera.h"

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
	// Positions          // Normals (x, y, z)

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
	glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

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
//-----------------------------------------------------------------------------------------------
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();
//-----------------------------------------------------------------------------------------------
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0,0, width, height);

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgramForObjects("default.vert", "default.frag");
	Shader lightSourceShader("lightingSourceShader.vert", "lightingSourceShader.frag");
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
//-------------------------------------------------------------------------------------------------------------------------

	glm::vec4 lightColor(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 positionOfLightSource(2.25f, 2.09f, 1.0f);
	glm::vec3 lightDirection(0.1f, 0.0f, 0.0f);
	float exponentForPointLight = 2.0f;
	float linearTerm_Kl = 0.7f;
	float quadraticTerm_Kq = 1.8f;
	float constantTerm_Kc = 1.0f;

	// Material GLOBAL
	glm::vec4 globalObjectColor(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 globalPos = glm::vec3(0.0f, 0.0f, 0.0f); // ?
	float globalAmbientStrenght = 0.5f;
	float globalDiffuseStrenght = 2.0f;
	float globalSpecularStrength = 0.5f;
	float globalShininessBlinnPhong = 16.0f;
	float globalShininessPhong = 8.0f;

	// Material CUBE
	glm::vec4 cubeColor(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 cubePos = glm::vec3(3.0f, 1.0f, 1.0f);

	// PYRAMIDE
	glm::vec4 pyramideColor(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 pyramidPos = glm::vec3(1.0f, 1.0f, 1.0f);

	// For different state insade the fragment shader
	bool isPointLightReducingOnDistance = true;
	bool isPhong = false;
	bool isBlinnPhong = true;
	bool isSpecularMap = true;

	bool isDirectionalLight = false;
	bool isPointLight = true;

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

	// Main while loop
	while(!glfwWindowShouldClose(window))
	{	
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::ShowDemoWindow(); // Show demo window! :)

		{
			ImGui::Begin("Performance:");
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			
			if (ImGui::Checkbox("Point Light", &isPointLight)) {
				if (isPointLight) {
					isDirectionalLight = false;
					isPointLightReducingOnDistance = true;
					isPhong = false;
					isBlinnPhong = true;
					globalAmbientStrenght = 0.5f;
				}
			}

			if (ImGui::Checkbox("Direction Light", &isDirectionalLight)) {
				if (isDirectionalLight) {
					isPointLight = false;
					isPointLightReducingOnDistance = false;
					isPhong = true;
					isBlinnPhong = false;
					globalAmbientStrenght = 0.2f;
				}
			}
			
			ImGui::End();
		}
		{

			ImGui::Begin("Light source");
			if (ImGui::CollapsingHeader("Color and position of light source")) {

				ImGui::SeparatorText("Color for light source:"); ImGui::Spacing();
				ImGui::SliderFloat3("Color", &lightColor.x, 0.0f, 1.0f); 
				ImGui::Separator();
				ImGui::DragFloat3("Position for point light", &positionOfLightSource.x, 0.1f); 
				ImGui::SliderFloat3("Direction vector of light", &lightDirection.x, -0.5f, 0.5f); 

				ImGui::SeparatorText("Position and color of light source:"); ImGui::Spacing();
				ImGui::Text("Color of the light source in float: R: %.2ff, G: %.2ff, B: %.2ff, A: %.2ff", lightColor.r, lightColor.g, lightColor.b, lightColor.a); 
				ImGui::Separator();
				ImGui::Text("Position of the point light source: %.2f, %.2f, %.2f", positionOfLightSource.x, positionOfLightSource.y, positionOfLightSource.z);
				ImGui::Text("Vector of the directional light source: %.2f, %.2f, %.2f", lightDirection.x, lightDirection.y, lightDirection.z);
			}
			if (ImGui::CollapsingHeader("Attenuation the light equation")) {

				ImGui::SeparatorText("State on/off:"); ImGui::Spacing();
				ImGui::Checkbox("Is Point Light Reducing On Distance", &isPointLightReducingOnDistance);

				ImGui::SeparatorText("Control of variables:"); ImGui::Spacing();
				ImGui::Text("Exponent for distance:"); ImGui::SameLine(); ImGui::SliderFloat("2", &exponentForPointLight, -64, 256);
				ImGui::Text("Linear Term Kl:"); ImGui::SameLine(); ImGui::SliderFloat("0.7f", &linearTerm_Kl, -2.683f, 256.0f);
				ImGui::Text("Quadratic Term Kq:"); ImGui::SameLine(); ImGui::SliderFloat("1.8f", &quadraticTerm_Kq, -64.0f, 64.0f);
				ImGui::Text("Constant Term Kc:"); ImGui::SameLine(); ImGui::SliderFloat("1.0f", &constantTerm_Kc, 0.0f, 64.0f);

				ImGui::SeparatorText("Bref explanation:"); ImGui::Spacing();
				ImGui::BulletText("To reduce the intensity of point light over the distance");

				ImGui::BulletText("More about it: ");
				ImGui::SameLine(0, 4);
				ImGui::TextLinkOpenURL("https://learnopengl.com/Lighting/Light-casters");
			}
			if (ImGui::CollapsingHeader("Model of light reflection")) {

				ImGui::SeparatorText("State of specular reflection on/off"); ImGui::Spacing();
				if (ImGui::Checkbox("Phong", &isPhong)) {
					if (isPhong) {
						isBlinnPhong = false;
					}
				}

				if (ImGui::Checkbox("Blinn-Phong", &isBlinnPhong)) {
					if (isBlinnPhong) {
						isPhong = false;
					}
				}
				ImGui::Separator(); ImGui::Spacing();
				ImGui::Checkbox("Specular Map", &isSpecularMap);

				ImGui::SeparatorText("Control of variables:"); ImGui::Spacing();
				ImGui::SliderFloat("Ambient Strenght: 0.5f", &globalAmbientStrenght, 0.0f, 4.0f); ImGui::Spacing();
				ImGui::SliderFloat("Diffuse Strenght: 2.0f", &globalDiffuseStrenght, 0.0f, 64.0f); ImGui::Spacing();
				ImGui::SliderFloat("Specular Strength: 0.5f", &globalSpecularStrength, 0.0f, 64.0f); ImGui::Spacing();
				ImGui::SliderFloat("Shininess Blinn-Phong: 16.0f", &globalShininessBlinnPhong, 0.0f, 256.0f); ImGui::Spacing();
				ImGui::SliderFloat("Shininess Phong: 8.0f", &globalShininessPhong, 0.0f, 256.0f); ImGui::Spacing();
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
		camera.Inputs(window, lightColor, positionOfLightSource, isBlinnPhong, isPhong, isSpecularMap);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateCameraMatrix(45.0f, 0.1f, 100.0f);

		// Tell OpenGL which Shader Program we want to use 
		shaderProgramForObjects.Activate();

		// Export state in shader in order to dynamicly change during runtime
		glUniform1i(glGetUniformLocation(shaderProgramForObjects.ID, "control.isPhong"), isPhong);
		glUniform1i(glGetUniformLocation(shaderProgramForObjects.ID, "control.isBlinnPhong"), isBlinnPhong);
		glUniform1i(glGetUniformLocation(shaderProgramForObjects.ID, "control.isSpecularMap"), isSpecularMap);
		glUniform1i(glGetUniformLocation(shaderProgramForObjects.ID, "control.isPointLight"), isPointLight);
		glUniform1i(glGetUniformLocation(shaderProgramForObjects.ID, "control.isPointLightReducingOnDistance"), isPointLightReducingOnDistance);
		glUniform1i(glGetUniformLocation(shaderProgramForObjects.ID, "control.isDirectionalLight"), isDirectionalLight);
		// Export for reducing point light in propotional to distance, a constant term Kc, a linear term Kl, and a quadratic term Kq // https://learnopengl.com/Lighting/Light-casters
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "light.exponentForPointLight"), exponentForPointLight);
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "light.linearTerm_Kl"), linearTerm_Kl);
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "light.quadraticTerm_Kq"), quadraticTerm_Kq);
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "light.constantTerm_Kc"), constantTerm_Kc);
		// Exprort light position for dynamic light
		glUniform3f(glGetUniformLocation(shaderProgramForObjects.ID, "light.lightPos"), positionOfLightSource.x, positionOfLightSource.y, positionOfLightSource.z);
		glUniform3f(glGetUniformLocation(shaderProgramForObjects.ID, "light.lightDirection"), lightDirection.x, lightDirection.y, lightDirection.z);
		glUniform4f(glGetUniformLocation(shaderProgramForObjects.ID, "light.lightColor"), lightColor.r, lightColor.g, lightColor.b, lightColor.a);
		// Export uniforms to shader for different material and component strenght
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "material.ambientStrenght"), globalAmbientStrenght);
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "material.diffuseStrenght"), globalDiffuseStrenght);
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "material.specularStrength"), globalSpecularStrength);
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "material.shininessBlinnPhong"), globalShininessBlinnPhong);
		glUniform1f(glGetUniformLocation(shaderProgramForObjects.ID, "material.shininessPhong"), globalShininessPhong);

		shaderProgramForObjects.Deactivate();

		{ //PYRAMIDE
			// Tell OpenGL which Shader Program we want to use 
			shaderProgramForObjects.Activate();

			// Exports the camera Position to the Fragment Shader for specular lighting calculation
			glUniform3f(glGetUniformLocation(shaderProgramForObjects.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
			// Export the camMatrix to the Vertex Shader of the pyramid
			camera.sendCamMatrixToShader(shaderProgramForObjects, "camMatrix");

			// Export uniforms to shader for different material
			glUniform4f(glGetUniformLocation(shaderProgramForObjects.ID, "material.objectColor"), pyramideColor.r, pyramideColor.g, pyramideColor.b, pyramideColor.a);

			// Binding texture so its appear at render
			planks.Bind();
			planksSpec.Bind();

			// Kreiraj lokalnu model matricu za piramidu
			glm::mat4 pyramidModel = glm::mat4(1.0f); // Resetovana matrica
			pyramidModel = glm::translate(pyramidModel, pyramidPos);;  // Translacija piramide
			shaderProgramForObjects.sendMat4x4ToShader("model", pyramidModel);  // Pošalji model matricu u shader

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
			glUniform4f(glGetUniformLocation(shaderProgramForObjects.ID, "material.objectColor"), cubeColor.r, cubeColor.g, cubeColor.b, cubeColor.a);

			// Binding texture so its appear at render
			planks.Bind();
			planksSpec.Bind();

			// Kreiraj lokalnu model matricu za kocku
			glm::mat4 cubeModel = glm::mat4(1.0f);  // Resetovana matrica
			cubeModel = glm::translate(cubeModel, cubePos); // Transplantacija kocke
			glUniformMatrix4fv(glGetUniformLocation(shaderProgramForObjects.ID, "model"), 1, GL_FALSE, glm::value_ptr(cubeModel)); // Pošalji model matricu u shader

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
		{ // LIGHT CUBE SOURCE
			// Activating shader that is used only for lightSource
			lightSourceShader.Activate();

			if (isDirectionalLight && !isPointLight) {
				// Kreiraj lokalnu model matricu za svetlosni izvor
				glm::mat4 lightModel = glm::mat4(1.0f); // Resetovana matrica
				lightModel = glm::translate(lightModel, lightDirection); // Translantacija svetla
				glUniformMatrix4fv(glGetUniformLocation(lightSourceShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));  // Pošalji model matricu u shader
			}
			else if(!isDirectionalLight && isPointLight)
			{
				// Kreiraj lokalnu model matricu za svetlosni izvor
				glm::mat4 lightModel = glm::mat4(1.0f); // Resetovana matrica
				lightModel = glm::translate(lightModel, positionOfLightSource); // Translantacija svetla
				glUniformMatrix4fv(glGetUniformLocation(lightSourceShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));  // Pošalji model matricu u shader
			}

			// Passing camMatrix uniform to lightSourceCube for projection matrix
			camera.sendCamMatrixToShader(lightSourceShader, "camMatrix");

			// Sending color of light-cube to light shader so when we change color this change also
			glUniform4f(glGetUniformLocation(lightSourceShader.ID, "lightColor"), lightColor.r, lightColor.g, lightColor.b, lightColor.a);

			// Binding light source vao in order to draws it
			LIGHT_SOURCE_VAO.Bind();
			// Draw light source cube using DrawArrays no-index(EBO)
			glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices_lightSource) / sizeof(float));
			// Unbind VAO that we just drawn and deactivate shader program
			LIGHT_SOURCE_VAO.Unbind();
			lightSourceShader.Deactivate();
		}

		// Render DEAR I am GUI
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	TRIANGLE_SHAPE_VAO.Delete();
	TRIANGLE_SHAPE_VBO.Delete();
	TRIANGLE_SHAPE_EBO.Delete();
	CUBE_SHAPE_VAO.Delete();
	CUBE_SHAPE_VBO.Delete();
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

	// Clean after DEAR I am GUI
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
