#include "axpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"


namespace Artifax
{
	Shader* Shader::Create(const std::string& filepath)
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
			return new OpenGLShader(filepath);
		}
		default:
		{
			AX_CORE_ASSERT(false, "Unknown RenderAPI!");
			return nullptr;
		}
		}
	}
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
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
				return new OpenGLShader(vertexSrc, fragmentSrc);
			}
			default:
			{
				AX_CORE_ASSERT(false, "Unknown RenderAPI!");
				return nullptr;
			}
		}
	}
}