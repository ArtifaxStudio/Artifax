#include "axpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"


namespace Artifax
{
	//////////////////////////////////////////////////////////////////////////////
	// SHADER /////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	Ref<Shader> Shader::Create(const std::string& filepath)
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
			return std::make_shared<OpenGLShader>(filepath);
		}
		default:
		{
			AX_CORE_ASSERT(false, "Unknown RenderAPI!");
			return nullptr;
		}
		}
	}
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
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
				return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
			}
			default:
			{
				AX_CORE_ASSERT(false, "Unknown RenderAPI!");
				return nullptr;
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////
	// SHADER LIBRARY /////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		AX_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}
	Ref<Shader> ShaderLibrary::Load(const std::string filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		AX_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}
	const bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}