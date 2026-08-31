#include <../../Flame/src/Flame.h>
#include <imgui.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

static glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 projection = glm::perspective(
		glm::radians(45.0f),
		4.0f / 3.0f,
		0.1f,
		100.0f
	);

	glm::mat4 view = glm::translate(
		glm::mat4(1.0f),
		glm::vec3(0.0f, 0.0f, -Translate)
	);
	view = glm::rotate(view, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 model = glm::scale(
		glm::mat4(1.0f),
		glm::vec3(0.5f)
	);

	return projection * view * model;
}

class ExampleLayer : public Flame::Layer
{
public:

	ExampleLayer()
		: Layer("Example")
	{
		const auto cam = camera(5.0f, { 0.5f, 0.5f });
		FL_CORE_INFO("GLM camera test: cam[0][0] = {0}, cam[3][3] = {1}", cam[0][0], cam[3][3]);
	}

	void OnUpdate() override
	{
		//FL_CORE_INFO("ExampleLayer::Update");
	}

	void OnImGuiRender() override
	{
		if (ImGui::Begin("Scene Hierarchy"))
			ImGui::Text("Scene Hierarchy");
		ImGui::End();

		if (ImGui::Begin("Properties"))
			ImGui::Text("Properties");
		ImGui::End();

		if (ImGui::Begin("Console"))
			ImGui::Text("Console");
		ImGui::End();

		if (ImGui::Begin("Viewport"))
			ImGui::Text("Viewport");
		ImGui::End();
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