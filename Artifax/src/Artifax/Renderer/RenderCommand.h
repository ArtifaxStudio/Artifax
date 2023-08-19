#pragma once

#include "RendererAPI.h"

namespace Artifax
{
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			AX_PROFILE_FUNCTION();

			s_RendererAPI->SetClearColor(color);
		}
		inline static void Clear()
		{
			AX_PROFILE_FUNCTION();

			s_RendererAPI->Clear();
		}
		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			AX_PROFILE_FUNCTION();

			s_RendererAPI->DrawIndexed(vertexArray);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}
