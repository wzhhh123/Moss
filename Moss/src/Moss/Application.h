#pragma once


#include "Core.h"
#include "Event/Event.h"


namespace Moss {

	class MOSS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}

