#include "axpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Artifax
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Artifax::ShaderDataType::Float:	return	GL_FLOAT;
			case Artifax::ShaderDataType::Float2:	return GL_FLOAT;
			case Artifax::ShaderDataType::Float3:	return GL_FLOAT;
			case Artifax::ShaderDataType::Float4:	return GL_FLOAT;
			case Artifax::ShaderDataType::Int:		return GL_INT;
			case Artifax::ShaderDataType::Int2:		return GL_INT;
			case Artifax::ShaderDataType::Int3:		return GL_INT;
			case Artifax::ShaderDataType::Int4:		return GL_INT;
			case Artifax::ShaderDataType::Mat3:		return GL_FLOAT;
			case Artifax::ShaderDataType::Mat4:		return GL_FLOAT;
			case Artifax::ShaderDataType::Bool:		return GL_BOOL;
		}

		AX_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(Ref<VertexBuffer>& vertexBuffer)
	{
		AX_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();


		uint32_t index = 0;
		const BufferLayout& layout = vertexBuffer->GetLayout();
		for each (const auto & element in layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}
