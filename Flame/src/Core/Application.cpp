#include "flpch.h"
#include "Application.h"


#include "Events/APPEvent.h"
#include "Log.h"

namespace Flame {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}