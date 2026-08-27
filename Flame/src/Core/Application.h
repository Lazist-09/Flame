#pragma once

#include "Core.h"

#include "Window.h"
#include "../LayerStack.h"
#include "Events/Event.h"
#include "Events/APPEvent.h"


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

	private:

		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	//要在客户端定义
	Application* CreateApplication();

}


