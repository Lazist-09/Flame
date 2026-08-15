#pragma once

#ifdef FL_PLATFORM_WINDOWS
	
extern Flame::Application* Flame::CreateApplication();//其他地方定义的函数，返回应用程序

int main(int argc, char** argv) {

	auto app = Flame::CreateApplication();
	app->Run();
	delete app;

}

#endif