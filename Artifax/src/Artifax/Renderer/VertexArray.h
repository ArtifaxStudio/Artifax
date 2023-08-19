#pragma once

#include <memory>

#include "Artifax/Renderer/Buffer.h"

namespace Artifax
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {};

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(Ref<IndexBuffer>& indexBuffer) = 0;

		static VertexArray * Create();
	};
}
