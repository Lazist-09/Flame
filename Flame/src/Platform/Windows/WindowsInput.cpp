#include "flpch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>
#include "../../Core/Application.h"

namespace Flame {

	Input* Input::s_Instance = new WindowsInput();
	
	bool WindowsInput::IsKeyPressedImpl(int keycode) {

		GLFWwindow* window = static_cast<GLFWwindow*>(
			Application::GetApplication().GetWindow().GetNativeWindow());

		int state = glfwGetKey(window, keycode);
		return state == FL_PRESS || state == FL_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(
			Application::GetApplication().GetWindow().GetNativeWindow());

		int state = glfwGetMouseButton(window, button);
		return state == FL_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(
			Application::GetApplication().GetWindow().GetNativeWindow());

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePosition();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePosition();
		return y;
	}

}
