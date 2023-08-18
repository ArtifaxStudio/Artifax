#include "axpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Artifax
{
	//////////////////////////////////////////////////////////////////////////////
	// BUFFER LAYOUT //////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
		: m_Elements(elements)
	{
		CalculateOffsetAndStride();
	}

	void BufferLayout::CalculateOffsetAndStride()
	{
		for (auto& element : m_Elements)
		{
			uint32_t offset = 0;
			m_stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = m_stride;
				m_stride += element.Size;
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////
	// VERTEX BUFFER //////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				AX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return new OpenGLVertexBuffer(vertices, size);
			}
			default:
			{
				AX_CORE_ASSERT(false, "Unknown RenderAPI!");
				return nullptr;
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////
	// INDEX BUFFER ///////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				AX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return new OpenGLIndexBuffer(indices, count);
			}
			default:
			{
				AX_CORE_ASSERT(false, "Unknown RenderAPI!");
				return nullptr;
			}
		}
	}
}