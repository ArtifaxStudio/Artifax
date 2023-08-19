#include "axpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Artifax
{
	//////////////////////////////////////////////////////////////////////////////
	// VERTEX BUFFER //////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		AX_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		AX_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void Artifax::OpenGLVertexBuffer::Bind() const
	{
		AX_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void Artifax::OpenGLVertexBuffer::Unbind() const
	{
		AX_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//////////////////////////////////////////////////////////////////////////////
	// INDEX BUFFER ///////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		AX_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		AX_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void Artifax::OpenGLIndexBuffer::Bind() const
	{
		AX_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void Artifax::OpenGLIndexBuffer::Unbind() const
	{
		AX_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
