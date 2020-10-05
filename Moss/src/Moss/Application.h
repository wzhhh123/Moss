#pragma once


#include "Core.h"
#include "Event/Event.h"
#include "Window.h"
#include "Event/ApplicationEvent.h"
#include "Moss/LayerStack.h"

namespace Moss {

	class MOSS_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:	
		static Application* s_Instance;
		std::unique_ptr<Window>m_Window;
		bool m_IsRunning = true;
		LayerStack m_LayerStack;
		bool OnWindowClose(WindowCloseEvent& e);
	};

	Application* CreateApplication();


}

