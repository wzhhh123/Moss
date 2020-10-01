#include "Application.h"

#include "Event/ApplicationEvent.h"
#include "Log.h"


namespace Moss {

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		WindowResizeEvent e(1280, 720);
		MS_TRACE(e);

		while (true) {

		}
	}
}