#include "axpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Artifax
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		AX_PROFILE_FUNCTION();

		AX_CORE_ASSERT(windowHandle, "Window Handle is null")
	}

	void OpenGLContext::Init()
	{
		AX_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);

		//Initialize GLAD
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AX_CORE_ASSERT(status, "Failed to initialize Glad!");
	}

	void OpenGLContext::SwapBuffers()
	{
		AX_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}