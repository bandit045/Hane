#include "GUI.h"
#include "Object.h"

GUI::GUI(GLFWwindow* window)
{ 
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	GUI::io = ImGui::GetIO();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();
}

void GUI::startGUIframe(bool enabledDemo)// This is executing for evry frame
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	if (enabledDemo)
		ImGui::ShowDemoWindow(); // Show demo window! :)
}

void GUI::contextOfGUI()
{
	Light();
}

void GUI::Light( )
{
	
}

void GUI::renderGUI()
{
	// Render DEAR I am GUI
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::clearGUI()
{
	// Clean after DEAR I am GUI
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}