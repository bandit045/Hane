#ifndef GUI_CLASS
#define GUI_CLASS

// Dear ImGui biblioteka - no docking branch // TODO: docking branch
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include <glad/glad.h>

// Hane engine core 
#include "Object.h"
#include "Material.h"
#include "Light.h"
#include "Camera.h"
#include "RenderFlags.h"
#include "GLPolygoneModeAppRenderAll.h"

class GUI
{
public:
	static void initGUI(GLFWwindow* window);
	static void startGUIframe(); 
	static void showDemoWindow(bool _enabledDemo);

	static void contextOfGUI(Camera& _camera, RenderFlags& _renderFlags, Object& _lampObject, Object& _pyramideObject, Material& _lampMaterial, Material& _globalMaterial, Light& _directionalLight, Light& _pointLight, Light& _spotLight);
	static void renderGUI();
	static void clearGUI();

private:
	static void Stats(Camera& _camera, RenderFlags& _renderFlags);
	static void LightSource(Object& _lampObject, Material& _lampMaterial, Material& _globalMaterial, Light& _directionalLight, Light& _pointLight, RenderFlags& _renderFlags, Light& _spotLight);

	static void SpotLight(Light& _spotLight);
	static void GlPolygonMode();
	static void TransformCube(Object& _pyramideObject);
};

#endif // !GUI_CLASS