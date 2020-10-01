
#include "mspch.h"
#include "Application.h"
#include "Event/ApplicationEvent.h"
#include <GLFW/glfw3.h>

namespace Moss {

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {

	}

	void Application::Run() {

		while (m_IsRunning) 
		{
			glClearColor(0.2, 0.2, 0, 0.2);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}