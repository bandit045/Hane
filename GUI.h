#ifndef GUI_CLASS
#define GUI_CLASS

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

class GUI
{
public:
	GUI(GLFWwindow* window);
	static void startGUIframe(bool enabledDemo);
	static void contextOfGUI();
	static void renderGUI();
	static void clearGUI();
	ImGuiIO io;
};

#endif // !GUI_CLASS