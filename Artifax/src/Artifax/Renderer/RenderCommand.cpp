#include "axpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Artifax
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}