#include "flpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Core/Application.h"
#include "Platform/OpenGL/Framebuffer.h"

//TEMPORARY
#include <GLFW/glfw3.h>
#include <glad/glad.h>



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

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

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

	void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	void ImGuiLayer::Begin() {

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// DockSpace 必须在各个 Layer 的窗口之前提交，窗口才能正常停靠。
		SetupDockLayout();
		ImGui::DockSpaceOverViewport(ImGui::GetID("FlameDockSpace"), ImGui::GetMainViewport());

	}

	void ImGuiLayer::End() {

		// 设置显示区域和 DeltaTime
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::GetApplication();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(),
			(float)app.GetWindow().GetHeight());

		// 渲染
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupCurrentContext);
		}

	
	}

	

	void ImGuiLayer::SetupDockLayout()
	{
		const ImGuiID dockspaceID = ImGui::GetID("FlameDockSpace");
		if (ImGui::DockBuilderGetNode(dockspaceID) != nullptr)
			return;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_DockSpace);
		ImGui::DockBuilderSetNodeSize(dockspaceID, viewport->WorkSize);

		ImGuiID leftID = 0;
		ImGuiID centerID = 0;
		ImGui::DockBuilderSplitNode(dockspaceID, ImGuiDir_Left, 0.20f, &leftID, &centerID);

		ImGuiID hierarchyID = 0;
		ImGuiID propertiesID = 0;
		ImGui::DockBuilderSplitNode(leftID, ImGuiDir_Up, 0.50f, &hierarchyID, &propertiesID);

		ImGuiID consoleID = 0;
		ImGuiID viewportID = 0;
		ImGui::DockBuilderSplitNode(centerID, ImGuiDir_Down, 0.25f, &consoleID, &viewportID);

		ImGui::DockBuilderDockWindow("Scene Hierarchy", hierarchyID);
		ImGui::DockBuilderDockWindow("Properties", propertiesID);
		ImGui::DockBuilderDockWindow("Console", consoleID);
		ImGui::DockBuilderDockWindow("Viewport", viewportID);

		ImGui::DockBuilderFinish(dockspaceID);
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
