#pragma once

#include "Artifax/Input.h"

namespace Artifax
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl();
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}

