#include "flpch.h"
#include "ImGuiLayer.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "imgui.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "Core/Application.h"

namespace Flame {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		// 允许用 Tab/方向键导航 UI,flag在glfw的init自动处理
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui::StyleColorsDark();

		Application& app = Application::GetApplication();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdate()
	{

		// 设置显示区域和 DeltaTime
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::GetApplication();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(),
			(float)app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		// 新版需要三行 NewFrame（顺序不能变）
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// 测试用 DemoWindow
		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		// 渲染
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		if (io.WantCaptureMouse && event.IsInCategory(EventCategoryMouse))
			event.Handled = true;

		if (io.WantCaptureKeyboard && event.IsInCategory(EventCategoryKeyboard))
			event.Handled = true;

	}

	//void ImGuiLayer::Begin()
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	Application& app = Application::GetApplication();
	//	io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(),(float)app.GetWindow().GetHeight());
	//
	//	float time = (float)glfwGetTime();
	//	io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
	//	m_Time = time;
	//
	//	// 新版需要三行 NewFrame（顺序不能变）：
	//	ImGui_ImplOpenGL3_NewFrame();
	//	ImGui_ImplGlfw_NewFrame();   
	//	ImGui::NewFrame();
	//}

	//void ImGuiLayer::End()
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//
	//	// 渲染
	//	ImGui::Render();
	//	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//}
	//
	//}

}
