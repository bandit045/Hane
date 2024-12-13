#ifndef GUI_CLASS
#define GUI_CLASS

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include <glad/glad.h>

#include "Object.h"
#include "Material.h"
#include "Light.h"
#include "Camera.h"
#include "RenderFlags.h"
#include "GLPolygoneModeAppRenderAll.h"

class GUI
{
public:
	GUI(GLFWwindow* window);
	static void startGUIframe(bool _enabledDemo);

	static void contextOfGUI(Camera& _camera, RenderFlags& _renderFlags, Object& _lampObject, Material& _lampMaterial, Material& _globalMaterial, Light& _directionalLight, Light& _pointLight, Light& _spotLight);
	static void Stats(Camera& _camera, RenderFlags& _renderFlags);
	static void LightSource(Object& _lampObject, Material& _lampMaterial, Material& _globalMaterial, Light& _directionalLight, Light& _pointLight, RenderFlags& _renderFlags, Light& _spotLight);

	static void SpotLight(Light& _spotLight);
	static void GlPolygonMode();

	static void renderGUI();
	static void clearGUI();
	ImGuiIO io;
};

#endif // !GUI_CLASS