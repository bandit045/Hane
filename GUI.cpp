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

void GUI::contextOfGUI(Camera& _camera, RenderFlags& _renderFlags, Object& _lampObject, Material& _lampMaterial, Material& _globalMaterial, Light& _directionalLight, Light& _pointLight, Light& _spotLight)
{
	Stats(_camera, _renderFlags);
	LightSource(_lampObject, _lampMaterial, _globalMaterial, _directionalLight, _pointLight, _renderFlags, _pointLight);
	SpotLight(_spotLight);
	GlPolygonMode();
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
			_renderFlags.setValueToBoolRenderFlag("isSpotLight",					false);
			_renderFlags.setValueToBoolRenderFlag("isVisualiseNormal",              false);
			_renderFlags.setValueToBoolRenderFlag("isVisualiseUVCordinate",         false);
		}

		if (ImGui::Checkbox("Direction Light", &_renderFlags.getSpecificValueReference("isDirectionalLight")))
		{
			_renderFlags.setValueToBoolRenderFlag("isDirectionalLight",             true);
			_renderFlags.setValueToBoolRenderFlag("isPointLight",                   false);
			_renderFlags.setValueToBoolRenderFlag("isPointLightReducingOnDistance", false);
			_renderFlags.setValueToBoolRenderFlag("isPhong",                        false);
			_renderFlags.setValueToBoolRenderFlag("isBlinnPhong",                   false);
			_renderFlags.setValueToBoolRenderFlag("isSpotLight",					false);
			_renderFlags.setValueToBoolRenderFlag("isLightTurnOff",                 false);
			_renderFlags.setValueToBoolRenderFlag("isVisualiseNormal",              false);
			_renderFlags.setValueToBoolRenderFlag("isVisualiseUVCordinate",         false);

		}

		if (ImGui::Checkbox("Spot Light", &_renderFlags.getSpecificValueReference("isSpotLight")))
		{
			_renderFlags.setValueToBoolRenderFlag("isDirectionalLight",             false);
			_renderFlags.setValueToBoolRenderFlag("isPointLight",                   false);
			_renderFlags.setValueToBoolRenderFlag("isPointLightReducingOnDistance", false);
			_renderFlags.setValueToBoolRenderFlag("isPhong",                        false);
			_renderFlags.setValueToBoolRenderFlag("isBlinnPhong",                   false);
			_renderFlags.setValueToBoolRenderFlag("isLightTurnOff",                 false);
			_renderFlags.setValueToBoolRenderFlag("isVisualiseNormal",              false);
			_renderFlags.setValueToBoolRenderFlag("isVisualiseUVCordinate",         false);
			_renderFlags.setValueToBoolRenderFlag("isSpotLight",                    true);
		}

		if (ImGui::Checkbox("Visualise normal: ", &_renderFlags.getSpecificValueReference("isVisualiseNormal")))
		{
			_renderFlags.setValueToBoolRenderFlag("isDirectionalLight",             false);
			_renderFlags.setValueToBoolRenderFlag("isPointLight",                   false);
			_renderFlags.setValueToBoolRenderFlag("isPointLightReducingOnDistance", false);
			_renderFlags.setValueToBoolRenderFlag("isPhong",                        false);
			_renderFlags.setValueToBoolRenderFlag("isBlinnPhong",                   false);
			_renderFlags.setValueToBoolRenderFlag("isSpotLight",					false);
			_renderFlags.setValueToBoolRenderFlag("isSpecularMap",					false);
			_renderFlags.setValueToBoolRenderFlag("isSpotLight",			        false);
			_renderFlags.setValueToBoolRenderFlag("isLightTurnOff",                 false);
			_renderFlags.setValueToBoolRenderFlag("isVisualiseUVCordinate",         false);
			_renderFlags.setValueToBoolRenderFlag("isVisualiseNormal",              true);
		}

		if (ImGui::Checkbox("Visualise UV cordinates: ", &_renderFlags.getSpecificValueReference("isVisualiseUVCordinate")))
		{
			_renderFlags.setValueToBoolRenderFlag("isDirectionalLight",             false);
			_renderFlags.setValueToBoolRenderFlag("isPointLight",                   false);
			_renderFlags.setValueToBoolRenderFlag("isPointLightReducingOnDistance", false);
			_renderFlags.setValueToBoolRenderFlag("isPhong",                        false);
			_renderFlags.setValueToBoolRenderFlag("isBlinnPhong",                   false);
			_renderFlags.setValueToBoolRenderFlag("isSpotLight",					false);
			_renderFlags.setValueToBoolRenderFlag("isSpecularMap",					false);
			_renderFlags.setValueToBoolRenderFlag("isSpotLight",			        false);
			_renderFlags.setValueToBoolRenderFlag("isLightTurnOff",                 false);
			_renderFlags.setValueToBoolRenderFlag("isVisualiseUVCordinate",         true);
			_renderFlags.setValueToBoolRenderFlag("isVisualiseNormal",              false);
		}

		if (ImGui::Checkbox("Turn off light", &_renderFlags.getSpecificValueReference("isLightTurnOff")))
		{
			_renderFlags.setValueToBoolRenderFlag("isDirectionalLight",             false);
			_renderFlags.setValueToBoolRenderFlag("isPointLight",                   false);
			_renderFlags.setValueToBoolRenderFlag("isPointLightReducingOnDistance", false);
			_renderFlags.setValueToBoolRenderFlag("isPhong",                        false);
			_renderFlags.setValueToBoolRenderFlag("isBlinnPhong",                   false);
			_renderFlags.setValueToBoolRenderFlag("isSpotLight",                    false);
			_renderFlags.setValueToBoolRenderFlag("isSpecularMap",                  false);
			_renderFlags.setValueToBoolRenderFlag("isSpotLight",                    false);
			_renderFlags.setValueToBoolRenderFlag("isVisualiseNormal",              false);
			_renderFlags.setValueToBoolRenderFlag("isVisualiseUVCordinate",         false);
			_renderFlags.setValueToBoolRenderFlag("isLightTurnOff",                  true);
		}

		// Different stats: 
		ImGui::Text("Position of camera: %.2f, %.2f, %.2f",     _camera.Position.x,    _camera.Position.y,    _camera.Position.z);
		ImGui::Text("Orientation of camera: %.2f, %.2f, %.2f",  _camera.Orientation.x, _camera.Orientation.y, _camera.Orientation.z);
		ImGui::Text("Up of camera: %.2f, %.2f, %.2f",           _camera.Up.x,          _camera.Up.y,          _camera.Up.z);
	ImGui::End();
}
void GUI::LightSource(Object& _lampObject, Material& _lampMaterial, Material& _globalMaterial, Light& _directionalLight, Light& _pointLight, RenderFlags& _renderFlags, Light& _spotLight)
{
	ImGui::Begin("Light source", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);

	if (ImGui::CollapsingHeader("Color and position of light source", ImGuiTreeNodeFlags_DefaultOpen)) {

		/*------------------------------------*/ImGui::SeparatorText("Color for light source:");/*--------------------------------------------*/
		ImGui::SliderFloat3("Color", &_lampMaterial.getObjectColor().x, 0.0f, 1.0f);
		ImGui::Separator(); //-----------------------------------------------------------------------------------------------------------------

		ImGui::DragFloat3("  Position for point light",       &_lampObject.m_transform->transformParams().m_objectPos.x,       0.1f          );
		ImGui::SliderFloat3("Rotation vector of point light", &_lampObject.m_transform->transformParams().m_objectRotEuler.x, -180.0f, 180.0f);
		ImGui::DragFloat4("  Quaternion orbit of lightource", &_lampObject.m_transform->transformParams().m_objectRotQuat.x,   0.1f         );
		ImGui::DragFloat3("  Scale factor of light",          &_lampObject.m_transform->transformParams().m_objectScale.x,     0.1f         );

		ImGui::Separator(); //-----------------------------------------------------------------------------------------------------------------

		if (!_renderFlags.getSpecificValueReference("isDirectionalLight")) ImGui::BeginDisabled();
		ImGui::SliderFloat3("Direction vector of light", &_directionalLight.setDirectionLightParams().lightDirection.x, -0.5f, 0.5f);
		if (!_renderFlags.getSpecificValueReference("isDirectionalLight")) ImGui::EndDisabled();

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

void GUI::SpotLight(Light& _spotLight)
{
	ImGui::Begin("Spot Light", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove);

	ImGui::SliderFloat3("Spot Direction", &_spotLight.setSpotLightParams().spotLightDirection.x,     -8.5f, 8.5f); ImGui::SameLine(); if (ImGui::SmallButton("R")) { _spotLight.setSpotLightParams().spotLightDirection.x = 0.0f; _spotLight.setSpotLightParams().spotLightDirection.y = -1.0f; _spotLight.setSpotLightParams().spotLightDirection.z = 0.0f; };
	ImGui::SliderFloat("Inner Cutoff",    &_spotLight.setSpotLightParams(true).innerCutOff,           0.0f, 90.0f); 
	ImGui::SliderFloat("Outer Cutoff",    &_spotLight.setSpotLightParams(true).outerCutOff,           0.0f, 90.0f);
	ImGui::SliderFloat("Intesity",        &_spotLight.setSpotLightParams().intensityMultiplayer,     -10.0f, 10.0f); ImGui::SameLine(); if (ImGui::SmallButton("RR")) {_spotLight.setSpotLightParams().intensityMultiplayer = 1.0f; };
	ImGui::SliderFloat("Tetha",           &_spotLight.setSpotLightParams().thetaMultiplayer,         -10.0f, 10.0f); ImGui::SameLine(); if (ImGui::SmallButton("RRR")) {_spotLight.setSpotLightParams().thetaMultiplayer = 1.0f; };

	ImGui::End();
}

void GUI::GlPolygonMode()
{
	ImGui::Begin("Mode render: ");

	bool fillFrontSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillFront;
	bool pointFrontSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointFront;
	bool lineFrontSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineFront;

	bool fillBackSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillBack;
	bool pointBackSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointBack;
	bool lineBackSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineBack;

	bool fillBothSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillBoth;
	bool pointBothSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointBoth;
	bool lineBothSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineBoth;

	
	if (ImGui::SliderFloat("Size of Point: ", &GLPolygoneModeAppRenderAll::IgetIsOnOrOff().sizeOfPoint, 0, 64.0f))
	{
		glPointSize(GLPolygoneModeAppRenderAll::IgetIsOnOrOff().sizeOfPoint);
	};

	if (ImGui::SliderFloat("Line width: ", &GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineWidth, 0, 64.0f))
	{
		glLineWidth(GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineWidth);
	};


	if (ImGui::RadioButton("Back GL_LINE - Front GL_FILL", lineBackSelected)) {
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineBack = true;

		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointFront = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineFront = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillFront = false;

		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointBack = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillBack = false;

		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillBoth = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointBoth = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineBoth = false;
	}
	// OpenGL State Change Logic (outside of ImGui)
	if (GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineBack) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE); // Adjust other states if necessary
	}

//----------------------------------------------------------------------------------------------------------

	if (ImGui::RadioButton("Back GL_POINT - Front GL_FILL", pointBackSelected)) {
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointBack = true;

		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointFront = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineFront = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillFront = false;

		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillBack = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineBack = false;

		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillBoth = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointBoth = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineBoth = false;
	}
	// OpenGL State Change Logic (outside of ImGui)
	if (GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointBack) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPolygonMode(GL_BACK, GL_POINT);
	}
//----------------------------------------------------------------------------------------------------

	if (ImGui::RadioButton("Back GL_FILL - Front GL_LINE", fillBackSelected)) {
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillBack = true;

		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointFront = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineFront = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillFront = false;

		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointBack = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineBack = false;

		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillBoth = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointBoth = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineBoth = false;
	}
	// OpenGL State Change Logic (outside of ImGui)
	if (GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillBack) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_BACK, GL_FILL);
	}
//-------------------------------------------------------------------------------------------------------

	if (ImGui::RadioButton("Front GL_POINT - Back GL_FILL", pointFrontSelected)) {
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointFront = true;

		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineFront = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillFront = false;

		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointBack = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineBack = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillBack = false;

		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillBoth = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointBoth = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineBoth = false;
	}
	// OpenGL State Change Logic (outside of ImGui)
	if (GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointFront) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glPolygonMode(GL_BACK, GL_FILL);
	}
//---------------------------------------------------------------------------------------------------------

	if (ImGui::RadioButton("Front GL_LINE - Back GL_POINT", lineFrontSelected)) {
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineFront = true;

		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointFront = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillFront = false;

		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointBack = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineBack = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillBack = false;

		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillBoth = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointBoth = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineBoth = false;
	}
	// OpenGL State Change Logic (outside of ImGui)
	if (GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineFront) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_BACK, GL_POINT);
	}
//----------------------------------------------------------------------------------------------------------
	if (ImGui::RadioButton("Front GL_FILL - Back GL_POINT", fillFrontSelected)) {
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillFront = true;

		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointFront = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineFront = false;

		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointBack = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineBack = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillBack = false;

		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillBoth = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointBoth = false;
		GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineBoth = false;
	}
	// OpenGL State Change Logic (outside of ImGui)
	if (GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillFront) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPolygonMode(GL_BACK, GL_POINT);
	}
//---------------------------------------------------------------------------------------------------------

	if (ImGui::RadioButton("Both: Front GL_POINT - Back GL_POINT", pointBothSelected)) {
		pointBothSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointBoth = true;

		fillFrontSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillFront = false;
		pointFrontSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointFront = false;
		lineFrontSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineFront = false;

		pointBackSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointBack = false;
		lineBackSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineBack = false;
		fillBackSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillBack = false;

		fillBothSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillBoth = false;
		lineBothSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineBoth = false;
	}
	// OpenGL State Change Logic (outside of ImGui)
	if (GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointBoth) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glPolygonMode(GL_BACK, GL_POINT);
	}
//----------------------------------------------------------------------------------------------------------
	if (ImGui::RadioButton("Both: Front GL_LINE - Back GL_LINE", lineBothSelected)) {
		lineBothSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineBoth = true;

		lineFrontSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineFront = false;
		fillFrontSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillFront = false;
		pointFrontSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointFront = false;

		pointBackSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointBack = false;
		lineBackSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineBack = false;
		fillBackSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillBack = false;

		fillBothSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillBoth = false;
		pointBothSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointBoth = false;
	}
	// OpenGL State Change Logic (outside of ImGui)
	if (GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineBoth) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	}
//---------------------------------------------------------------------------------------------------------
	if (ImGui::RadioButton("Both: Front GL_FILL - Back GL_FILL", fillBothSelected)) {
		fillBothSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillBoth = true;

		fillFrontSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillFront = false;
		pointFrontSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointFront = false;
		lineFrontSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineFront = false;

		pointBackSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointBack = false;
		lineBackSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineBack = false;
		fillBackSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillBack = false;

		pointBothSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().pointBoth = false;
		lineBothSelected = GLPolygoneModeAppRenderAll::IgetIsOnOrOff().lineBoth = false;
	}
	// OpenGL State Change Logic (outside of ImGui)
	if (GLPolygoneModeAppRenderAll::IgetIsOnOrOff().fillBoth) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
	}
	

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