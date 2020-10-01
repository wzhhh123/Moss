#pragma once


#include "Core.h"
#include "Event/Event.h"
#include "Window.h"
#include "Event/ApplicationEvent.h"

namespace Moss {

	class MOSS_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();

		void OnEvent(Event& e);
	private:

		std::unique_ptr<Window>m_Window;
		bool m_IsRunning = true;
		bool OnWindowClose(WindowCloseEvent& e);
	};

	Application* CreateApplication();


}

