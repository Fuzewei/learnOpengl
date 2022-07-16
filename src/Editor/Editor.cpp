#include "Editor.h"


Editor::Editor(GLFWwindow* window):
	window(window)
{
	ImGui::CreateContext();
	io = ImGui::GetIO();
	ImGui_ImplGlfwGL3_Init(window, true);
	// Setup style
	ImGui::StyleColorsDark();
}

Editor::~Editor()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
}

void Editor::Render()
{
	ImGui_ImplGlfwGL3_NewFrame();
	//todo: ‘⁄‘⁄‰÷»æui
	
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}
