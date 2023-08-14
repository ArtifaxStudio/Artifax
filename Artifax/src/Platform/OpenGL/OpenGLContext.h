#pragma once

#include "Artifax/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Artifax
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}
