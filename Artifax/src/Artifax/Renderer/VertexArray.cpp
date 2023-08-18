#include "axpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Artifax
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:
			{
				AX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			}
			case RendererAPI::OpenGL:
			{
				return new OpenGLVertexArray();
			}
			default:
			{
				AX_CORE_ASSERT(false, "Unknown RenderAPI!");
				return nullptr;
		}
		}
	}
}