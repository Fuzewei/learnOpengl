#pragma once
#include <Gl/glew.h>
#include <GLFW/glfw3.h>
#include "panel.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

class Editor
{
public:
	Editor(GLFWwindow* window);
	~Editor();
	void Render();
private:
	GLFWwindow* window;
	ImGuiIO io;
};

