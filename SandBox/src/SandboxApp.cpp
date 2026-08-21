#include <Flame.h>

class Sandbox : public Flame::Application
{
public:
	Sandbox()
	{
	}

	~Sandbox()
	{

	}
};

Flame::Application* Flame::CreateApplication()
{
	return new Sandbox();
}