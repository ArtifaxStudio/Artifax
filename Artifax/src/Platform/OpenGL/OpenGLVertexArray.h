#pragma once

#include "Artifax/Renderer/VertexArray.h"

namespace Artifax
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray() override {};

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer>& indexBuffer) override;
	private:
		uint32_t m_RendererID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}

