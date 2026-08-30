#include "flpch.h"
#include "ImGuiLayer.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "Core/Application.h"
#include "Platform/OpenGL/Framebuffer.h"

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
		io.IniFilename = "editor_layout.ini";

		// 允许用 Tab/方向键导航 UI,flag在glfw的init自动处理
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.ConfigDpiScaleFonts = true;
		io.ConfigDpiScaleViewports = true;

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;

		Application& app = Application::GetApplication();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
		m_Framebuffer = std::make_unique<Framebuffer>(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");

		const ImGuiPlatformIO& platformIO = ImGui::GetPlatformIO();
		FL_CORE_INFO(
			"ImGui diagnostics: Viewports={0}, PlatformHasViewports={1}, RendererHasViewports={2}, CreateWindow={3}, RenderWindow={4}",
			(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) != 0,
			(io.BackendFlags & ImGuiBackendFlags_PlatformHasViewports) != 0,
			(io.BackendFlags & ImGuiBackendFlags_RendererHasViewports) != 0,
			platformIO.Platform_CreateWindow != nullptr,
			platformIO.Platform_RenderWindow != nullptr
		);
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

		const ImGuiID dockspaceID = ImGui::GetID("FlameDockSpace");
		SetupDockLayout();
		ImGui::DockSpaceOverViewport(dockspaceID, ImGui::GetMainViewport());

		ImGui::Begin("Viewport");
		const ImVec2 viewportSize = ImGui::GetContentRegionAvail();
		const float viewportDpiScale = ImGui::GetWindowDpiScale();
		if (viewportSize.x > 0.0f && viewportSize.y > 0.0f &&
			(viewportSize.x != m_ViewportWidth || viewportSize.y != m_ViewportHeight ||
				viewportDpiScale != m_ViewportDpiScale))
		{
			m_ViewportWidth = viewportSize.x;
			m_ViewportHeight = viewportSize.y;
			m_ViewportDpiScale = viewportDpiScale;
			m_Framebuffer->Resize(
				static_cast<uint32_t>(viewportSize.x * viewportDpiScale),
				static_cast<uint32_t>(viewportSize.y * viewportDpiScale));
		}

		m_Framebuffer->Bind();
		glClearColor(0.08f, 0.10f, 0.14f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		m_Framebuffer->Unbind();

		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
		int framebufferWidth = 0;
		int framebufferHeight = 0;
		glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
		glViewport(0, 0, framebufferWidth, framebufferHeight);

		ImGui::Image(ImTextureRef(static_cast<ImTextureID>(m_Framebuffer->GetColorAttachmentRendererID())), viewportSize, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();

		ImGui::Begin("Scene Hierarchy");
		ImGui::Text("Scene");
		ImGui::BulletText("Camera");
		ImGui::BulletText("ExampleLayer");
		ImGui::End();

		ImGui::Begin("Properties");
		ImGui::Text("Select an entity to inspect its properties.");
		ImGui::End();

		ImGui::Begin("Console");
		ImGui::Text("Flame console");
		ImGui::End();

		// 测试用 DemoWindow
		static bool show = true;
		ImGui::ShowDemoWindow(&show);

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

		static int lastViewportCount = 0;
		const int viewportCount = ImGui::GetPlatformIO().Viewports.Size;
		if (viewportCount != lastViewportCount)
		{
			FL_CORE_INFO("ImGui platform viewport count: {0}", viewportCount);
			lastViewportCount = viewportCount;
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
