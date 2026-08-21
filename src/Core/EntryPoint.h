#pragma once

#ifdef FL_PLATFORM_WINDOWS
	
extern Flame::Application* Flame::CreateApplication();//其他地方定义的函数，返回应用程序

int main(int argc, char** argv) {

	Flame::Log::Init();
	FL_CORE_WARN("Flame Engine Initialized!");
	FL_CLIENT_INFO("Hello from the client!Var={0}", 5);

	auto app = Flame::CreateApplication();
	app->Run();
	delete app;

}

#endif