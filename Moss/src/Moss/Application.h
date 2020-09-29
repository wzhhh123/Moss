#pragma once


#include "Core.h"

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

