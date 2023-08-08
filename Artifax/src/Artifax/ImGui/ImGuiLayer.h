#pragma once

#include "Artifax/Layer.h"

namespace Artifax
{
	class ARTIFAX_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Events::Event& event) override;

	private:
		float m_Time = 0.0f;
	};
}

