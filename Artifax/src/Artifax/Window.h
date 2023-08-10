#pragma once

#include "axpch.h"

#include "Artifax/Core.h"
#include "Artifax/Events/Event.h"
#include "Artifax/Events/WindowEvent.h"
#include "Artifax/Events/KeyEvent.h"
#include "Artifax/Events/MouseEvent.h"

namespace Artifax {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Artifax Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height) 
		{
		}
	};

	// Interface representing a Desktop system based Window
	class ARTIFAX_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Events::Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};



}
