#pragma once

#include "Core.h"

#include "Window.h"
#include "../LayerStack.h"
#include "Events/Event.h"
#include "Events/APPEvent.h"

#include "ImGui/ImGuiLayer.h"


namespace Flame {

	class FL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& GetApplication() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:

		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer = nullptr;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};

	//要在客户端定义
	Application* CreateApplication();

}


