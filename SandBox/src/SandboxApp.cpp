#include <../../Flame/src/Flame.h>

class ExampleLayer : public Flame::Layer
{
public:

	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		FL_CORE_INFO("ExampleLayer::Update");
	}

	void OnEvent(Flame::Event& event) override
	{
		if (event.GetEventType() == Flame::EventType::KeyPressed) {
			Flame::KeyPressedEvent& e = (Flame::KeyPressedEvent&) event;
			FL_CORE_INFO("Key pressed: {0}", e.GetKeyCode());
		}
		
		FL_CORE_INFO("{0}", event);
	}
};

class Sandbox : public Flame::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Flame::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Flame::Application* Flame::CreateApplication()
{
	return new Sandbox();
}