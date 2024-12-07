#include "GUI.h"

GUI::GUI(GLFWwindow* window)
{ 
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	GUI::io = ImGui::GetIO();

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Header] = ImVec4(0.52f, 0.06f, 0.63f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.73f, 0.18f, 0.86f, 1.0f);

	style.Colors[ImGuiCol_Button] = ImVec4(0.54, 0.17, 0.48, 1.0);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.76, 0.42, 0.71, 1.0);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.00, 1.00, 0.04, 1.0);
	style.Colors[ImGuiCol_Text] = ImVec4(0.88, 0.90, 0.75, 1.0);

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();
}
void GUI::startGUIframe(bool _enabledDemo)// This is executing for evry frame
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	if (_enabledDemo)
		ImGui::ShowDemoWindow(); // Show demo window! :)
}

void GUI::contextOfGUI(Camera& _camera, RenderFlags& _renderFlags, Object& _lampObject, Material& _lampMaterial, Material& _globalMaterial, Light& _directionalLight, Light& _pointLight)
{
	Stats(_camera, _renderFlags);
	LightSource(_lampObject, _lampMaterial, _globalMaterial, _directionalLight, _pointLight, _renderFlags);
}
void GUI::Stats(Camera& _camera, RenderFlags& _renderFlags)
{
	ImGui::Begin("Stats: ");
		if (ImGui::Checkbox("Point Light", &_renderFlags.getSpecificValueReference("isPointLight")))
		{
			_renderFlags.setValueToBoolRenderFlag("isPointLight",                   true);
			_renderFlags.setValueToBoolRenderFlag("isDirectionalLight",             false);
			_renderFlags.setValueToBoolRenderFlag("isPointLightReducingOnDistance", true);
			_renderFlags.setValueToBoolRenderFlag("isPhong",                        false);
			_renderFlags.setValueToBoolRenderFlag("isBlinnPhong",                   true);
			_renderFlags.setValueToBoolRenderFlag("isLightTurnOff",                 false);
		}

		if (ImGui::Checkbox("Direction Light", &_renderFlags.getSpecificValueReference("isDirectionalLight")))
		{
			_renderFlags.setValueToBoolRenderFlag("isDirectionalLight",             true);
			_renderFlags.setValueToBoolRenderFlag("isPointLight",                   false);
			_renderFlags.setValueToBoolRenderFlag("isPointLightReducingOnDistance", false);
			_renderFlags.setValueToBoolRenderFlag("isPhong",                        false);
			_renderFlags.setValueToBoolRenderFlag("isBlinnPhong",                   false);
			_renderFlags.setValueToBoolRenderFlag("isLightTurnOff",                 false);
		}

		if (ImGui::Checkbox("Turn off light", &_renderFlags.getSpecificValueReference("isLightTurnOff")))
		{
			_renderFlags.setValueToBoolRenderFlag("isDirectionalLight",             false);
			_renderFlags.setValueToBoolRenderFlag("isPointLight",                   false);
			_renderFlags.setValueToBoolRenderFlag("isPointLightReducingOnDistance", false);
			_renderFlags.setValueToBoolRenderFlag("isPhong",                        false);
			_renderFlags.setValueToBoolRenderFlag("isBlinnPhong",                   false);
			_renderFlags.setValueToBoolRenderFlag("isLightTurnOff",                 true);
		}

		// Different stats: 
		ImGui::Text("Position of camera: %.2f, %.2f, %.2f",     _camera.Position.x,    _camera.Position.y,    _camera.Position.z);
		ImGui::Text("Orientation of camera: %.2f, %.2f, %.2f",  _camera.Orientation.x, _camera.Orientation.y, _camera.Orientation.z);
		ImGui::Text("Up of camera: %.2f, %.2f, %.2f",           _camera.Up.x,          _camera.Up.y,          _camera.Up.z);
	ImGui::End();
}
void GUI::LightSource(Object& _lampObject, Material& _lampMaterial, Material& _globalMaterial, Light& _directionalLight, Light& _pointLight, RenderFlags& _renderFlags)
{
	ImGui::Begin("Light source", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);

	if (ImGui::CollapsingHeader("Color and position of light source", ImGuiTreeNodeFlags_DefaultOpen)) {

		/*------------------------------------*/ImGui::SeparatorText("Color for light source:");/*--------------------------------------------*/
		ImGui::SliderFloat3("Color", &_lampMaterial.getObjectColor().x, 0.0f, 1.0f);
		ImGui::Separator(); //-----------------------------------------------------------------------------------------------------------------

		ImGui::DragFloat3("  Position for point light",       &_lampObject.m_transform->transformParams().m_objectPos.x,       0.1f          );
		ImGui::SliderFloat3("Rotation vector of point light", &_lampObject.m_transform->transformParams().m_objectRotEuler.x, -180.0f, 180.0f);
		ImGui::DragFloat4("  Quaternion orbit of lightource", &_lampObject.m_transform->transformParams().m_objectRotQuat.x,   64.0f         );
		ImGui::DragFloat3("  Scale factor of light",          &_lampObject.m_transform->transformParams().m_objectScale.x,     64.0f         );

		ImGui::Separator(); //-----------------------------------------------------------------------------------------------------------------
		ImGui::SliderFloat3("Direction vector of light", &_directionalLight.setDirectionLightParams().lightDirection.x, -0.5f, 0.5f);

		/*----------------------*/ImGui::SeparatorText("Position and color of light source:");/*----------------------------------------------*/
		ImGui::TextWrapped("Color of the light source in float: R: %.2ff, G: %.2ff, B: %.2ff", _lampMaterial.getObjectColor().r, _lampMaterial.getObjectColor().g, _lampMaterial.getObjectColor().b);
		ImGui::TextWrapped("Position of the point light source: %.2f, %.2f, %.2f",             _lampObject.m_transform->transformParams().m_objectPos.x,      _lampObject.m_transform->transformParams().m_objectPos.y,      _lampObject.m_transform->transformParams().m_objectPos.z);
		ImGui::TextWrapped("Rotation of the point light source: %.2f, %.2f, %.2f",             _lampObject.m_transform->transformParams().m_objectRotEuler.x, _lampObject.m_transform->transformParams().m_objectRotEuler.y, _lampObject.m_transform->transformParams().m_objectRotEuler.z);
		ImGui::TextWrapped("Quaternion orbite light source: %.2f, %.2f, %.2f, %.2f",           _lampObject.m_transform->transformParams().m_objectRotQuat.x,  _lampObject.m_transform->transformParams().m_objectRotQuat.y,  _lampObject.m_transform->transformParams().m_objectRotQuat.z, _lampObject.m_transform->transformParams().m_objectRotQuat.w);
		ImGui::TextWrapped("Vector of the directional light source: %.2f, %.2f, %.2f",         _directionalLight.getDirectionLightParams().lightDirection.x,  _directionalLight.getDirectionLightParams().lightDirection.y,  _directionalLight.getDirectionLightParams().lightDirection.z);
	}
	if (ImGui::CollapsingHeader("Attenuation the light equation",     ImGuiTreeNodeFlags_DefaultOpen)) {

		/*---------------------------------------------------*/ImGui::SeparatorText("State on/off:");/*----------------------------------------------------------------*/
		
		if (ImGui::Checkbox("Is Point Light Reducing On Distance", &_renderFlags.getSpecificValueReference("isPointLightReducingOnDistance")) && (_renderFlags.getSpecificValueReference("isDirectionalLight") || _renderFlags.getSpecificValueReference("isLightTurnOff")))
		{
			_renderFlags.setValueToBoolRenderFlag("isPointLightReducingOnDistance", false);
		};

		/*---------------------------------------------------*/ImGui::SeparatorText("Control of variables MANUEL:");/*-------------------------------------------------*/

		ImGui::SliderFloat("Exponent for distance: ", &_pointLight.setPointLightParams().exponentForPointLight, -64, 256);        ImGui::SameLine(0, 0); if (ImGui::SmallButton("2.0f")) { _pointLight.setPointLightParams().exponentForPointLight = 2.0f; };
		ImGui::SliderFloat("Linear Term Kl:        ", &_pointLight.setPointLightParams().linearTerm_Kl,         -2.683f, 256.0f); ImGui::SameLine(0, 0); if (ImGui::SmallButton("0.7f")) { _pointLight.setPointLightParams().linearTerm_Kl = 0.7f; };
		ImGui::SliderFloat("Quadratic Term Kq:     ", &_pointLight.setPointLightParams().quadraticTerm_Kq,      -64.0f, 64.0f);   ImGui::SameLine(0, 0); if (ImGui::SmallButton("1.8f")) { _pointLight.setPointLightParams().quadraticTerm_Kq = 1.8f; };
		ImGui::SliderFloat("Constant Term Kc:      ", &_pointLight.setPointLightParams().constantTerm_Kc,        0.0f, 64.0f);    ImGui::SameLine(0, 0); if (ImGui::SmallButton("1.0f")) { _pointLight.setPointLightParams().constantTerm_Kc = 1.0f; };

		if (ImGui::Button("RESET EQUATION", ImVec2(120, 40)))
		{
			_pointLight.setPointLightParams().exponentForPointLight = 2.0f;
			_pointLight.setPointLightParams().linearTerm_Kl = 0.7f;
			_pointLight.setPointLightParams().quadraticTerm_Kq = 1.8f;
			_pointLight.setPointLightParams().constantTerm_Kc = 1.0f;
		};  ImGui::SameLine(0, 0); if (ImGui::SmallButton("Set manuel active")) { _renderFlags.setValueToBoolRenderFlag("isManuelLuminosity", true); _renderFlags.setValueToBoolRenderFlag("isAutomaticLuminosity", false); };

		ImGui::SeparatorText("Control of variables AUTOMATIC:"); ImGui::Spacing();
		ImGui::SliderFloat("Overall Light Brightness:", &_pointLight.setPointLightParams().overallLightBrightness, 0, 1); ImGui::SameLine(0, 0); if (ImGui::SmallButton("1.0")) { _pointLight.setPointLightParams().overallLightBrightness = 1.0f; }; ImGui::Spacing();
		ImGui::SameLine(0, 0); if (ImGui::SmallButton("Set automatic active")) { _renderFlags.setValueToBoolRenderFlag("isManuelLuminosity", false); _renderFlags.setValueToBoolRenderFlag("isAutomaticLuminosity", true); };

		/*---------------------------------------------------*/ImGui::SeparatorText("Bref explanation:");/*------------------------------------------------------------*/
		ImGui::BulletText("To reduce the intensity of point light over the distance by doing algoritam.");
		ImGui::BulletText("More about it: "); ImGui::SameLine(0, 4); ImGui::TextLinkOpenURL("https://learnopengl.com/Lighting/Light-casters");
	}
	if (ImGui::CollapsingHeader("Model of light reflection",          ImGuiTreeNodeFlags_DefaultOpen)) {

		ImGui::SeparatorText("State of specular reflection on/off");

		if (ImGui::Checkbox("Phong", &_renderFlags.getSpecificValueReference("isPhong")) || (_renderFlags.getSpecificValueReference("isDirectionalLight") || _renderFlags.getSpecificValueReference("isLightTurnOff")))
		{
			_renderFlags.setValueToBoolRenderFlag("isPhong", true);
			_renderFlags.setValueToBoolRenderFlag("isBlinnPhong", false);
		}

		if (ImGui::Checkbox("Blinn-Phong", &_renderFlags.getSpecificValueReference("isBlinnPhong")) || (_renderFlags.getSpecificValueReference("isDirectionalLight") || _renderFlags.getSpecificValueReference("isLightTurnOff")))
		{
			_renderFlags.setValueToBoolRenderFlag("isPhong", false);
			_renderFlags.setValueToBoolRenderFlag("isBlinnPhong", true);
		}
		ImGui::Separator();//----------------------------------------------------------------------------------- 

		ImGui::Checkbox("Specular Map", &_renderFlags.getSpecificValueReference("isSpecularMap"));

		/*-------------------------*/ImGui::SeparatorText("Control of variables:");/*-----------------------------------------*/
		ImGui::SliderFloat("Ambient Strenght:   ", &_globalMaterial.getAmbientStrenght(),   0.0f, 32.0f);  ImGui::SameLine(0, 0); if (ImGui::SmallButton("0.6f"))  { _globalMaterial.setAmbientStrenght(0.6f); };    
		ImGui::SliderFloat("Diffuse Strenght:   ", &_globalMaterial.getDiffuseStrenght(),   0.0f, 64.0f);  ImGui::SameLine(0, 0); if (ImGui::SmallButton("1.9f"))  { _globalMaterial.setDiffuseStrenght(1.9f); };     
		ImGui::SliderFloat("Specular Strength:  ", &_globalMaterial.getSpecularStrenght(),  0.0f, 64.0f);  ImGui::SameLine(0, 0); if (ImGui::SmallButton("0.5f"))  { _globalMaterial.setSpecularStrenght(0.5f); };  
		ImGui::SliderFloat("Shininess Strength: ", &_globalMaterial.getShininessStrenght(), 0.0f, 256.0f); ImGui::SameLine(0, 0); if (ImGui::SmallButton("16.0f")) { _globalMaterial.setShininessStrenght(16.0f); }; 

		if (ImGui::Button("RESET STRENGHT", ImVec2(160, 30)))
		{
			_globalMaterial.setAmbientStrenght(0.6f);
			_globalMaterial.setDiffuseStrenght(1.9f);
			_globalMaterial.setSpecularStrenght(0.5f);
			_globalMaterial.setShininessStrenght(16.0f);
		};
		ImGui::Separator();//----------------------------------------------------------------------------
	}

	ImGui::End();
}

void GUI::TransformComponent()
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