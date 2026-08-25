#include "flpch.h"
#include "Application.h"


#include "Events/APPEvent.h"
#include "Log.h"

namespace Flame {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280,700);
		std::cout << e << std::endl;
		FL_CLIENT_TRACE(e);

		while (true)
		{
			// Update and render the application
		}
	}
}