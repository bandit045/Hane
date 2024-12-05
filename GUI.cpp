#include "GUI.h"

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
void GUI::contextOfGUI(Camera& _camera, RenderFlags& _renderFlags)
{
	Stats(_camera, _renderFlags);
}

void GUI::Stats(Camera& _camera, RenderFlags& _renderFlags)
{
	ImGui::Begin("Stats: ");
		if (ImGui::Checkbox("Point Light", &_renderFlags.getSpecificValueReference("isPointLight")))
		{
			_renderFlags.setValueToBoolRenderFlag("isDirectionalLight",             false);
			_renderFlags.setValueToBoolRenderFlag("isPointLightReducingOnDistance", true);
			_renderFlags.setValueToBoolRenderFlag("isPhong",                        false);
			_renderFlags.setValueToBoolRenderFlag("isBlinnPhong",                   true);
		}

		if (ImGui::Checkbox("Direction Light", &_renderFlags.getSpecificValueReference("isDirectionalLight")))
		{
			_renderFlags.setValueToBoolRenderFlag("isPointLight",                   false);
			_renderFlags.setValueToBoolRenderFlag("isPointLightReducingOnDistance", false);
			_renderFlags.setValueToBoolRenderFlag("isPhong",                        false);
			_renderFlags.setValueToBoolRenderFlag("isBlinnPhong",                   false);
		}

		// Different stats: 
		ImGui::Text("Position of camera: %.2f, %.2f, %.2f",     _camera.Position.x,    _camera.Position.y,    _camera.Position.z);
		ImGui::Text("Orientation of camera: %.2f, %.2f, %.2f",  _camera.Orientation.x, _camera.Orientation.y, _camera.Orientation.z);
		ImGui::Text("Up of camera: %.2f, %.2f, %.2f",           _camera.Up.x,          _camera.Up.y,          _camera.Up.z);
	ImGui::End();
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