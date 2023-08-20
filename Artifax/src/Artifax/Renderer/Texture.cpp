#include "axpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform//OpenGL/OpenGLTexture.h"

namespace Artifax
{
	Ref<Texture2D> Artifax::Texture2D::Create(const std::string& path)
	{
		AX_PROFILE_FUNCTION();

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
		{
			AX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		}
		case RendererAPI::API::OpenGL:
		{
			return std::make_shared<OpenGLTexture2D>(path);
		}
		default:
		{
			AX_CORE_ASSERT(false, "Unknown RenderAPI!");
			return nullptr;
		}
		}
	}
}
