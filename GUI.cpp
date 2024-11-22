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

void GUI::contextOfGUI()
{
/* {
		ImGui::Begin("Performance:");
		//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

		if (ImGui::Checkbox("Point Light", &renderFlags.isPointLight)) {
			if (renderFlags.isPointLight) {
				renderFlags.isDirectionalLight = false;
				renderFlags.isPointLightReducingOnDistance = true;
				renderFlags.isPhong = false;
				renderFlags.isBlinnPhong = true;
				globalAmbientStrenght = 0.5f;
			}
		}

		if (ImGui::Checkbox("Direction Light", &renderFlags.isDirectionalLight)) {
			if (renderFlags.isDirectionalLight) {
				renderFlags.isPointLight = false;
				renderFlags.isPointLightReducingOnDistance = false;
				renderFlags.isPhong = true;
				renderFlags.isBlinnPhong = false;
				globalAmbientStrenght = 0.2f;
			}
		}

		ImGui::Text("Position of camera: %.2f, %.2f, %.2f", camera.Position.x, camera.Position.y, camera.Position.z);
		ImGui::Text("Orientation of camera: %.2f, %.2f, %.2f", camera.Orientation.x, camera.Orientation.y, camera.Orientation.z);
		ImGui::Text("Up of camera: %.2f, %.2f, %.2f", camera.Up.x, camera.Up.y, camera.Up.z);
		ImGui::Text("Quat-stat: %.2f", lamp.m_orientationQuat.w);
		ImGui::End();
	}
	{

		ImGui::Begin("Light source");
		if (ImGui::CollapsingHeader("Color and position of light source", ImGuiTreeNodeFlags_DefaultOpen)) {

			ImGui::SeparatorText("Color for light source:"); ImGui::Spacing();
			ImGui::SliderFloat3("Color", &lampMaterial.objectColor.x, 0.0f, 1.0f);
			ImGui::Separator();
			ImGui::DragFloat3("Position for point light", &lampTransform.objectPos.x, 0.1f);
			ImGui::SliderFloat3("Rotation vector of point light", &lampTransform.objectRotEuler.x, -180.0f, 180.0f);
			ImGui::DragFloat4("Quaternion orbit of lightource", &lampTransform.objectRotQuat.x, 64.0f, 720.0f);
			ImGui::SliderFloat3("Scale factor of light", &lampTransform.objectScale.x, 0.0f, 64.0f);
			ImGui::Separator();
			ImGui::SliderFloat3("Direction vector of light", &directionalLightParams.lightDirection.x, -0.5f, 0.5f);

			ImGui::SeparatorText("Position and color of light source:"); ImGui::Spacing();
			ImGui::Text("Color of the light source in float: R: %.2ff, G: %.2ff, B: %.2ff, A: %.2ff", lampMaterial.objectColor.r, lampMaterial.objectColor.g, lampMaterial.objectColor.b, lampMaterial.objectColor.a);
			ImGui::Separator();
			ImGui::Text("Position of the point light source: %.2f, %.2f, %.2f", lamp.Position.x, lamp.Position.y, lamp.Position.z);
			ImGui::TextWrapped("Rotation of the point light source: %.2f, %.2f, %.2f", lamp.getOritationEuler(Object::Rotation::X), lamp.getOritationEuler(Object::Rotation::Y), lamp.getOritationEuler(Object::Rotation::Z));
			ImGui::TextWrapped("Quaternion orbite light source: %.2f, %.2f, %.2f, %.2f", lamp.m_orientationQuat.w, lamp.m_orientationQuat.x, lamp.m_orientationQuat.y, lamp.m_orientationQuat.z);
			ImGui::Text("Vector of the directional light source: %.2f, %.2f, %.2f", directionalLightParams.lightDirection.x, directionalLightParams.lightDirection.y, directionalLightParams.lightDirection.z);
		}
		if (ImGui::CollapsingHeader("Attenuation the light equation", ImGuiTreeNodeFlags_DefaultOpen)) {

			ImGui::SeparatorText("State on/off:"); ImGui::Spacing();
			ImGui::Checkbox("Is Point Light Reducing On Distance", &renderFlags.isPointLightReducingOnDistance);

			ImGui::SeparatorText("Control of variables:");
			ImGui::SliderFloat("Exponent for distance:", &pointLightParams.exponentForPointLight, -64, 256); ImGui::SameLine(0, 0); if (ImGui::SmallButton("2.0f")) { pointLightParams.exponentForPointLight = 2.0f; }; ImGui::Spacing();
			ImGui::SliderFloat("Linear Term Kl:", &pointLightParams.linearTerm_Kl, -2.683f, 256.0f); ImGui::SameLine(0, 0); if (ImGui::SmallButton("0.7f")) { pointLightParams.linearTerm_Kl = 2.0f; }; ImGui::Spacing();
			ImGui::SliderFloat("Quadratic Term Kq:", &pointLightParams.quadraticTerm_Kq, -64.0f, 64.0f); ImGui::SameLine(0, 0); if (ImGui::SmallButton("1.8f")) { pointLightParams.quadraticTerm_Kq = 1.8f; }; ImGui::Spacing();
			ImGui::SliderFloat("Constant Term Kc:", &pointLightParams.constantTerm_Kc, 0.0f, 64.0f); ImGui::SameLine(0, 0); if (ImGui::SmallButton("1.0f")) { pointLightParams.constantTerm_Kc = 1.0f; }; ImGui::Spacing();

			if (ImGui::Button("RESET EQUATION", ImVec2(120, 40))) {
				pointLightParams.exponentForPointLight = 2.0f;
				pointLightParams.linearTerm_Kl = 0.7f;
				pointLightParams.quadraticTerm_Kq = 1.8f;
				pointLightParams.constantTerm_Kc = 1.0f;
			};

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
			ImGui::SliderFloat("Ambient Strenght:", &globalAmbientStrenght, 0.0f, 32.0f); ImGui::SameLine(0, 0); if (ImGui::SmallButton("0.6f")) { globalAmbientStrenght = 0.6f; }; ImGui::Spacing();
			ImGui::SliderFloat("Diffuse Strenght:", &globalDiffuseStrenght, 0.0f, 64.0f); ImGui::SameLine(0, 0); if (ImGui::SmallButton("1.9f")) { globalDiffuseStrenght = 1.9f; };  ImGui::Spacing();
			ImGui::SliderFloat("Specular Strength:", &globalSpecularStrength, 0.0f, 64.0f); ImGui::SameLine(0, 0); if (ImGui::SmallButton("0.5f")) { globalSpecularStrength = 0.5f; };  ImGui::Spacing();
			ImGui::SliderFloat("Shininess Strength:", &globalShininessStrenght, 0.0f, 256.0f); ImGui::SameLine(0, 0); if (ImGui::SmallButton("16.0f")) { globalShininessStrenght = 16.0f; };  ImGui::Spacing();

			if (ImGui::Button("RESET STRENGHT", ImVec2(120, 40))) {
				globalAmbientStrenght = 0.6f;
				globalDiffuseStrenght = 1.9f;
				globalSpecularStrength = 0.5f;
				globalShininessStrenght = 16.0f;
			};
			//ImGui::ArrowButton("Up", ImGuiDir_Up);
			ImGui::Separator();
		}
		ImGui::End();
	}
	*/
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