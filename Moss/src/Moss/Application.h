#pragma once


#include "Core.h"
#include "Event/Event.h"
#include "Window.h"


namespace Moss {

	class MOSS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window>m_Window;
		bool m_IsRunning = true;
	};

	Application* CreateApplication();


}

