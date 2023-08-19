#include "axpch.h"
#include "WindowsInput.h"

#include "Artifax/Application.h"
#include <GLFW/glfw3.h>

namespace Artifax
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		AX_PROFILE_FUNCTION();

		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		AX_PROFILE_FUNCTION();

		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		AX_PROFILE_FUNCTION();

		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		AX_PROFILE_FUNCTION();

		auto [x, y] = GetMousePosition();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		AX_PROFILE_FUNCTION();

		auto [x, y] = GetMousePosition();
		return y;
	}
}
