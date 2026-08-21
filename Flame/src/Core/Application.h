#pragma once

#include "Core.h"

namespace Flame {

	class FL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//要在客户端定义
	Application* CreateApplication();

}


